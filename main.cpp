#include <charconv>
#include <iostream>
#include <map>
#include <regex>
#include <variant>

#include "file_helper.h"
#include "test_string.h"

struct USDLObject {
    std::variant<
        std::nullptr_t,                   // null
        bool,                             // false
        int,                              // 111
        double,                           // 1.234
        std::string,                      // "usdl"
        std::vector<USDLObject>,          // ["what", "is", "usdl?", 1, 2, 3.456]
        std::map<std::string, USDLObject> // {"what": "usdl", "is": "awesome"}
        > internal;
};

class USDLParser {
public:
    static USDLObject parse(std::string_view usdl) {
        unsigned int index{};
        return parse(usdl, index);
    }
private:
    static USDLObject parse(std::string_view usdl, unsigned int& index) {
        if (index >= usdl.size()) {
            return USDLObject{std::nullptr_t{}};
        }
        auto c = usdl[index];
        switch (c) {
            case 'n': return parse_null(usdl, index);
            case 't':
            case 'f': return parse_boolean(usdl, index);
            case '0' ... '9':
            case '-':
            case '+': return parse_number(usdl, index);
            case '"': return parse_string(usdl, index);

            case '<': return parse_key(usdl, index);
            case '[': return parse_array(usdl, index);
            case '{': return parse_object(usdl, index);
            case ' ':
            case '\n':
            case '\r':
            case '\f':
            case '\v':
            case '\0': return parse_whitespace(usdl, index);
            default: {
                    std::cerr << "maybe something error" << std::endl;
                    return USDLObject{std::nullptr_t{}};
                }
        }
        return USDLObject{std::nullptr_t{}};
    }
    template <class T>
    static std::optional<T> try_parse_number(std::string_view str) {
        std::size_t pos{};
        if constexpr (std::is_same_v<T, double>) {
            T result = std::stod(str.data(), &pos);
            if (pos == str.length()) {
                return result;
            }
            return std::nullopt;
        }
        if constexpr (std::is_same_v<T, int>) {
            T result = std::stoi(str.data(), &pos);
            if (pos == str.length()) {
                return result;
            }
            return std::nullopt;
        }
        return std::nullopt;
    }
    static USDLObject parse_whitespace(std::string_view usdl, unsigned int& index) {
        if (size_t pos = usdl.find_first_not_of(" \t\n\r\f\v\0", index); pos != std::string::npos) {
            index = pos;
        } else {
            index = usdl.size();
        }
        return parse(usdl, index);
    }
    static USDLObject parse_null(std::string_view usdl, unsigned int& index) {
        index += 4;
        return USDLObject{std::nullptr_t{}};
    }
    static USDLObject parse_boolean(std::string_view usdl, unsigned int& index) {
        if (usdl[index] == 't') {
            index += 4;
            return USDLObject{true};
        } else {
            index += 5;
            return USDLObject{false};
        }
    }
    static USDLObject parse_number(std::string_view usdl, unsigned int& index) {
        std::regex num_regex{"[+-]?[0-9]+(\\.[0-9]*)?([eE][+-]?[0-9]+)?"};
        std::cmatch match;
        if (std::regex_search(usdl.data() + index, usdl.data() + usdl.size(), match, num_regex)) {
            std::string str = match.str();
            index += str.size();
            if (auto result = try_parse_number<int>(str)) {
                return USDLObject{*result};
            }
            if (auto result = try_parse_number<double>(str)) {
                return USDLObject{*result};
            }
        }
        std::cerr << "No, it's not possible!" << std::endl;
        return USDLObject{std::nullptr_t{}};
    }
    static USDLObject parse_string(std::string_view usdl, unsigned int& index) {
        // TODO: escape
        std::string str;
        ++index;
        while (usdl[index] != '"') {
            str += usdl[index++];
        }
        ++index;
        return USDLObject{std::move(str)};
    }
    static USDLObject parse_key(std::string_view usdl, unsigned int& index) {
        // TODO: escape
        std::string str;
        ++index;
        while (usdl[index] != '>') {
            str += usdl[index++];
        }
        ++index;
        return USDLObject{std::move(str)};
    }
    static USDLObject parse_array(std::string_view usdl, unsigned int& index) {
        std::vector<USDLObject> array;
        for (++index; index < usdl.length();) {
            if (usdl[index] == ']') {
                ++index;
                break;
            }
            auto object = parse(usdl, index);
            array.push_back(std::move(object));
            while (index < usdl.length() && usdl[index] != ',' && usdl[index] != ']') {
                ++index;
            }
            if (usdl[index] == ',') {
                ++index;
            }
        }
        return USDLObject{array};
    }
    static USDLObject parse_object(std::string_view usdl, unsigned int& index) {
        std::map<std::string, USDLObject> object;
        for (++index; index < usdl.length();) {
            if (usdl[index] == '}') {
                ++index;
                break;
            }
            auto key = parse(usdl, index);
            if (std::holds_alternative<std::nullptr_t>(key.internal)) {
                std::cerr << "error: key is null" << std::endl;
                index = usdl.size();
                break;
            } else {
                while (index < usdl.length() && usdl[index] != '=') {
                    ++index;
                }
            }
            if (usdl[index] == '=') {
                ++index;
            }
            auto value = parse(usdl, index);
            object.insert_or_assign(std::move(std::get<std::string>(key.internal)), std::move(value));
            while (index < usdl.length() && usdl[index] != ';' && usdl[index] != '}') {
                ++index;
            }
            if (usdl[index] == ';') {
                ++index;
            }
        }
        return USDLObject{object};
    }
};

int main() {
    // write and read from file
    FileHelper::writeFile("usdl_test.usdl", g_test_string);
    std::string usdl(FileHelper::readFile("usdl_test.usdl"));
    std::cout << usdl << std::endl;

    // temporary string
    usdl = R"(
        {
            <what> = "usdl";
            <is> = "awesome";
            <version> = 1.0;
            <features> = [
                "easy-to-use",
                "fast",
                "powerful",
                {
                    <usdl> = "is awesome";
                    <sub-dict> = {
                        <usdl> = "is cool";
                        <sub-list> = [
                            "usdl",
                            "is",
                            "cool"
                        ]
                    }
                }
            ]
        }
    )";

    // test string
    usdl = R"([{
<aaa> =     false
}, [
  ]
, 1, 2, 3, 4, 5, null, [null, 123.456], "asdasd", 1e7, false, null])";

    // parse usdl
    auto usdl_object = USDLParser::parse(usdl);

    // traverse usdl object
    // TODO: add visit
    return 0;
}
#include <iostream>
#include <regex>

#include "parser/usdl_parser.h"

#include "utils/file_helper.h"
#include "utils/test_string.h"

#include "3rd/boost/asio.hpp"

int test_parser() {
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


int main() {
    test_parser();
    boost::asio::io_service io_service;
    return io_service.run();
}
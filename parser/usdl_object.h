//
// Created by Mouse Zhang on 2024/1/18.
//

#ifndef USDL_OBJECT_H
#define USDL_OBJECT_H

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

#endif //USDL_OBJECT_H

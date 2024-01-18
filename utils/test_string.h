//
// Created by Mouse Zhang on 2024/1/6.
//

#ifndef TEST_STRING_H
#define TEST_STRING_H

std::string g_test_string = R"TEST(
{
    <name> =
    {
        <key> = "aa\\bb\\cc.so" ;
        <steps> = list
        {
            <index> = 1 ;
            <name> = "step1" ;
            <function> = "func1" ;
            <error_code> = "10001" ;
            <error_message> = "error message 1" ;
            <value> = false;
        },
        {
            <index> = 2 ;
            <name> = "step2" ;
            <function> = "func2" ;
            <error_code> = "10002" ;
            <error_message> = "error message 2" ;
            <value> = 1.234;
        },
        {
            <index> = 2 ;
            <name> = "step2" ;
            <function> = "func2" ;
            <error_code> = "10002" ;
            <error_message> = "error message 2" ;
            <value> = list
            {
                <index> = 1 ;
                <name> = "step1" ;
                <function> = "func1" ;
                <error_code> = "10001" ;
                <error_message> = "error message 1" ;
                <value> = false;
            },
            {
                <index> = 2 ;
                <name> = "step2" ;
                <function> = "func2" ;
                <error_code> = "10002" ;
                <error_message> = "error message 2" ;
                <value> = 1.234;
            },
            {
                <index> = 3 ;
                <name> = "step3" ;
                <function> = "func3" ;
                <error_code> = "10003" ;
                <error_message> = "error message 3" ;
                <value> = true;
            };
            }
        },
        {
            <index> = 3 ;
            <name> = "step3" ;
            <function> = "func3" ;
            <error_code> = "10003" ;
            <error_message> = "error message 3" ;
            <value> = false;
        };
    }
}
)TEST";

#endif //TEST_STRING_H

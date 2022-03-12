#pragma once

#include "std.hpp"

namespace std
{
    /**
     * @brief stanard string class
     * 
     */
    class string
    {
        char* theString;
    public:
        int stringLength;
        string(const char *cStr);
        string();

        void append(const char *cStr);
        void append(char inChar);
        void append(string str);
        char* pop(int amount);

        void operator+=(const char *cStr);
        void operator+=(char inChar);
        void operator+=(string str);

        bool operator==(const char *cStr);

        string operator+(const char *cStr);
        string operator+(string str);

        char* cStr();
    };

};
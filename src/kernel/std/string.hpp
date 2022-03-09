#pragma once

#include "std.hpp"

namespace std
{
    class string
    {
        char* theString;
        int stringLength;
    public:
        string(const char *cStr);
        string();

        void append(const char *cStr);
        void append(string str);

        void operator+=(const char *cStr);
        void operator+=(string str);

        string operator+(const char *cStr);
        string operator+(string str);

        char* cStr();
    };

};
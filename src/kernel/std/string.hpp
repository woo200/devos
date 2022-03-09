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

        char* cStr();
    };

};
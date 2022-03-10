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
        void append(string str);

        void operator+=(const char *cStr);
        void operator+=(string str);

        string operator+(const char *cStr);
        string operator+(string str);

        char* cStr();
    };

};
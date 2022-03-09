#include "string.hpp"

namespace std
{
    string::string(const char *cStr)
    {
        this->stringLength = strlen(cStr);
        this->theString = (char*) calloc(sizeof(char) * this->stringLength);
        strcpy(cStr, this->theString);
    }

    string::string()
    {
        this->stringLength = 0;
        this->theString = (char*) malloc(sizeof(char));
    }

    void string::append(const char *inStr)
    {
        int inStrLen = strlen(inStr);
        char* newStr = (char*) realloc(this->theString, sizeof(char) * (this->stringLength + inStrLen));
        free(this->theString);
        this->theString = newStr;
        strcat(this->theString, inStr);
        this->stringLength += inStrLen;
    }

    char* string::cStr()
    {
        char* str = (char*) malloc(sizeof(char) * (stringLength + 1));
        strcpy(this->theString, str);
        str[stringLength] = '\0';
        return str;
    }

    void string::append(string str)
    {
        char* theStrToAppend = str.cStr();
        this->append(theStrToAppend);
        free(theStrToAppend);
    }

    void string::operator+=(const char *cStr)
    {
        this->append(cStr);
    }

    void string::operator+=(string str)
    {
        this->append(str);
    }

    string string::operator+(const char *cStr)
    {
        string strToReturn(this->cStr());
        strToReturn.append(cStr);
        return strToReturn;
    }

    string string::operator+(string str)
    {
        string strToReturn(this->cStr());
        strToReturn.append(str);
        return strToReturn;
    }
} 


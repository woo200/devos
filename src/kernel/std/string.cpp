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

    void string::append(const char *cStr)
    {
        int inStrLength = strlen(cStr);
        char* originalStr = (char*) calloc(sizeof(char) * this->stringLength);
        strcpy(this->theString, originalStr);
        free(this->theString);
        
        this->theString = (char*) calloc(sizeof(char) * (this->stringLength + inStrLength));
        strcpy(originalStr, this->theString);
        strcat(this->theString, cStr);
        free(originalStr);
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
} 

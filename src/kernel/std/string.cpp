#include "string.hpp"

namespace std
{
    string::string(const char *cStr)
    {
        this->stringLength = strlen(cStr);
        this->theString = (char*) malloc(sizeof(char) * stringLength);
        for (int i = 0; i < this->stringLength; i++)
        {
            this->theString[i] = cStr[i];
        }
    }

    string::string()
    {
        this->stringLength = 0;
        this->theString = (char*) malloc(sizeof(char));
    }

    void string::append(const char *cStr)
    {
        int len = strlen(cStr);

        char* oldStr = (char*) malloc(sizeof(char) * this->stringLength);
        strcpy(this->theString, oldStr);
        free(this->theString);
        this->theString = (char*) malloc(sizeof(char) * (stringLength + len));

        for (int i = 0; i < this->stringLength; i++)
        {
            this->theString[i] = oldStr[i];
        }
        free(oldStr);

        for (int i = this->stringLength, total = this->stringLength + len; i < total; i++)
        {
            this->theString[i] = cStr[i];
        }
        this->stringLength += len;
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

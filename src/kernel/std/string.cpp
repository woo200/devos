#include "string.hpp"

namespace std
{
    /**
     * @brief Construct a new string::string object
     * 
     * @param cStr Initial String
     */
    string::string(const char *cStr)
    {
        this->stringLength = strlen(cStr);
        this->theString = (char*) calloc(sizeof(char) * this->stringLength);
        strcpy(cStr, this->theString);
    }

    /**
     * @brief Construct a new string::string object
     * 
     */
    string::string()
    {
        this->stringLength = 0;
        this->theString = (char*) malloc(sizeof(char));
    }

    /**
     * @brief Append a C string
     * 
     * @param inStr String to append
     */
    void string::append(const char *inStr)
    {
        int inStrLen = strlen(inStr);
        char* newStr = (char*) realloc(this->theString, sizeof(char) * (this->stringLength + inStrLen));
        free(this->theString);
        this->theString = newStr;
        strcat(this->theString, inStr);
        this->stringLength += inStrLen;
    }

    /**
     * @brief Get C str
     * 
     * @return char* C str
     */
    char* string::cStr()
    {
        char* str = (char*) malloc(sizeof(char) * (stringLength + 1));
        strcpy(this->theString, str);
        str[stringLength] = '\0';
        return str;
    }

    /**
     * @brief Append a string 
     * 
     * @param str String to append
     */
    void string::append(string str)
    {
        char* theStrToAppend = str.cStr();
        this->append(theStrToAppend);
        free(theStrToAppend);
    }

    /**
     * @brief Append a single char to string
     * 
     * @param inChar Char to append
     */
    void string::append(char inChar)
    {
        char* newStr = (char*) realloc(this->theString, sizeof(char) * (this->stringLength + 1));
        free(this->theString);
        this->theString = newStr;
        this->theString[this->stringLength] = inChar;
        this->stringLength += 1;
    }

    /**
     * @brief Append a C string
     * 
     * @param cStr string to append
     */
    void string::operator+=(const char *cStr)
    {
        this->append(cStr);
    }

    /**
     * @brief Append a string
     * 
     * @param str string to append
     */
    void string::operator+=(string str)
    {
        this->append(str);
    }

    /**
     * @brief Append a single char to a string
     * 
     * @param inChar Char to append
     */
    void string::operator+=(char inChar)
    {
        this->append(inChar);
    }

    /**
     * @brief Check if string is equal to {@code cStr}
     * 
     * @param cStr str to check against
     */
    bool string::operator==(const char *cStr)
    {
        return strcmp(this->cStr(), cStr) == 0;
    }

    /**
     * @brief Pop {@code amount} of characters from string
     * 
     * @param amount Number of chars to pop
     * @return char* Popped characters
     */
    char* string::pop(int amount)
    {
        if (this->stringLength < amount)
            return nullptr;
        char* newStr = (char*) calloc(sizeof(char) * (this->stringLength - amount));
        char* popped = (char*) calloc(sizeof(char) * amount);

        memcpy(this->theString, newStr, this->stringLength - amount);
        memcpy(this->theString + this->stringLength - amount, popped, amount);

        free(this->theString);
        this->theString = newStr;
        this->stringLength -= amount;

        return popped;
    }

    /**
     * @brief Append C string and return appended value
     * 
     * @param cStr C str to append
     * @return string Final appended value
     */
    string string::operator+(const char *cStr)
    {
        string strToReturn(this->cStr());
        strToReturn.append(cStr);
        return strToReturn;
    }

    /**
     * @brief Append string and return appended value
     * 
     * @param cStr str to append
     * @return string Final appended value
     */
    string string::operator+(string str)
    {
        string strToReturn(this->cStr());
        strToReturn.append(str);
        return strToReturn;
    }
} 


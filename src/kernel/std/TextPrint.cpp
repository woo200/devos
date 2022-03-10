#include "TextPrint.hpp"

uint16_t cursorPosition;

namespace kstd
{
  void setCursorPosition(uint16_t position)
  {
    outbyte(0x3D4, 0x0F);
    outbyte(0x3D5, (uint8_t)(position & 0xFF));
    outbyte(0x3D4, 0x0E);
    outbyte(0x3D5, (uint8_t)((position >> 8) & 0xFF));

    cursorPosition = position;
  }

  void ClearScreen(uint64_t ClearColor)
  {
    uint64_t value = 0;

    value += ClearColor << 8;
    value += ClearColor << 24;
    value += ClearColor << 40;
    value += ClearColor << 56;

    for (uint64_t* i = (uint64_t*)VGA_MEMORY; i < (uint64_t*)(VGA_MEMORY + 4000); ++i)
    {
      *i = value;
    }

    setCursorPosition(0);
  }

  uint16_t positionFromCoords(uint8_t x, uint8_t y)
  {
    return y * VGA_WIDTH + x;
  }

  void PrintString(const char* str, uint8_t color)
  {
    uint8_t* charPtr = (uint8_t*)str;
    uint16_t index = cursorPosition;

    while (*charPtr != 0)
    {
      switch (*charPtr)
      {
        case 10:
          index += VGA_WIDTH;
        case 13:
          index -= index % VGA_WIDTH;
          break;
        default:
          *(VGA_MEMORY + index * 2) = *charPtr;
          *(VGA_MEMORY + index * 2 + 1) = color;
          ++index;
      }
      ++charPtr;
    }

    setCursorPosition(index);
  }

  void PrintStringCenter(const char* str, uint8_t color)
  {
    int y = (cursorPosition - cursorPosition % VGA_WIDTH) /  VGA_WIDTH;
    setCursorPosition(positionFromCoords(VGA_WIDTH / 2 - strlen(str) / 2, y + 1));
    PrintString(str, color);
  }

  void PrintStringwNLCenter(const char* str, uint8_t color)
  {
    uint8_t* charPtr = (uint8_t*)str;
    char lineBuffer[128];
    int idx = 0;

    while (*charPtr != 0)
    {
      switch (*charPtr) {
        case 10:
          lineBuffer[idx] = 0;
          PrintStringCenter(lineBuffer, color);
          idx = 0;
          ++charPtr;
          continue;
        default:
          lineBuffer[idx] = *charPtr;
          break;
      }
      ++charPtr;
      ++idx;
    }

    lineBuffer[idx + 1] = 0;
    PrintStringCenter(lineBuffer, color);
  }

  void PrintChar(char chr, uint8_t color)
  {
    setCursorPosition(cursorPosition + 1);
    *(VGA_MEMORY + cursorPosition * 2) = chr;
    *(VGA_MEMORY + cursorPosition * 2 + 1) = color;
  }

  char hexToStringOutput[128];
  template<typename T>
  const char* hexToString(T value) {
    T* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = (sizeof(T)) * 2 - 1;
    uint8_t i;

    for (i = 0; i < size; ++i)
    {
        ptr = ((uint8_t*) valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToStringOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : 48);
        tmp = (*ptr & 0x0F);
        hexToStringOutput[size - (i * 2)] = tmp + (tmp > 9 ? 55 : 48);
    }
    hexToStringOutput[size + 3] = 0;
    return hexToStringOutput;
  }

  const char* hexToString(uint8_t value) { return hexToString<uint8_t>(value); }
  const char* hexToString(uint16_t value) { return hexToString<uint16_t>(value); }
  const char* hexToString(uint32_t value) { return hexToString<uint32_t>(value); }
  const char* hexToString(uint64_t value) { return hexToString<uint64_t>(value); }

  const char* hexToString(char value) { return hexToString<char>(value); }
  const char* hexToString(short value) { return hexToString<short>(value); }
  const char* hexToString(int value) { return hexToString<int>(value); }
  const char* hexToString(long long value) { return hexToString<long long>(value); }

  char integerToStringOutput[128];
  template<typename T>
  const char* IntegerToString(T value) {
    uint8_t isNegative = 0;
    if (value < 0) {
      isNegative = 1;
      value *= -1;
      integerToStringOutput[0] = '-';
    }
    uint8_t size = 0;
    uint64_t sizeTester = (uint64_t) value;

    while (sizeTester / 10 > 0) {
      sizeTester /= 10;
      ++size;
    }

    uint8_t index = 0;
    uint64_t newValue = (uint64_t) value;

    while (newValue / 10 > 0) {
      uint8_t remainder = newValue % 10;
      newValue /= 10;
      integerToStringOutput[isNegative + size - index] = remainder + 48;
      ++index;
    }

    uint8_t remainder = newValue % 10;
    integerToStringOutput[isNegative + size - index] = remainder + 48;
    integerToStringOutput[isNegative + size + 1] = 0;

    return integerToStringOutput;
  }

  const char* IntegerToString(uint8_t value) { return IntegerToString<uint8_t>(value); }
  const char* IntegerToString(uint16_t value) { return IntegerToString<uint16_t>(value); }
  const char* IntegerToString(uint32_t value) { return IntegerToString<uint32_t>(value); }
  const char* IntegerToString(uint64_t value) { return IntegerToString<uint64_t>(value); }

  const char* IntegerToString(char value) { return IntegerToString<char>(value); }
  const char* IntegerToString(short value) { return IntegerToString<short>(value); }
  const char* IntegerToString(int value) { return IntegerToString<int>(value); }
  const char* IntegerToString(long long value) { return IntegerToString<long long>(value); }

  char floatToStringOutput[128];
  const char* FloatToString(float value, uint8_t precision, bool pmeter)
  {
    char* intPtr = (char*)IntegerToString((int)value);
    char* floatPtr = floatToStringOutput;

    if (value < 0) {
      value *= -1;
    }

    while (*intPtr != 0)
    {
      *floatPtr = *intPtr;

      ++floatPtr;
      ++intPtr;
    }

    *floatPtr = '.';
    ++floatPtr;

    float newValue = value - (int)value;
    for (uint8_t i = 0; i < precision; i++) {
      newValue *= 10;
      *floatPtr = (int)newValue + 48;
      newValue -= (int)newValue;
      ++floatPtr;
    }

    if (pmeter) {
      *floatPtr = 'p';
      ++floatPtr;

      char* prec = (char*)IntegerToString((int)precision);
      while (*prec != 0)
      {
        *floatPtr = *prec;

        ++floatPtr;
        ++prec;
      }
    }
    *floatPtr = 0;

    return floatToStringOutput;
  }
}
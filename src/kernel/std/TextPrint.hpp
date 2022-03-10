#pragma once

#define VGA_MEMORY (uint8_t*) 0xb8000
#define VGA_WIDTH 80

#include "../../types.hpp"
#include "TextModeColors.hpp"
#include "std.hpp"

extern uint16_t cursorPosition;

namespace kstd
{
  void ClearScreen(uint64_t ClearColor = BACKGROUND_BLACK | FOREGROUND_WHITE);
  void setCursorPosition(uint16_t position);
  uint16_t positionFromCoords(uint8_t x, uint8_t y = BACKGROUND_BLACK | FOREGROUND_WHITE);
  void PrintString(const char* str, uint8_t color = BACKGROUND_BLACK | FOREGROUND_WHITE);
  void PrintStringCenter(const char* str, uint8_t color = BACKGROUND_BLACK | FOREGROUND_WHITE);
  void PrintStringwNLCenter(const char* str, uint8_t color = BACKGROUND_BLACK | FOREGROUND_WHITE);
  void PrintChar(char chr, uint8_t color = BACKGROUND_BLACK | FOREGROUND_WHITE);
  const char* FloatToString(float value, uint8_t precision, bool pmeter = false);

  const char* hexToString(uint8_t value);
  const char* hexToString(uint16_t value);
  const char* hexToString(uint32_t value);
  const char* hexToString(uint64_t value);

  const char* hexToString(char value);
  const char* hexToString(short value);
  const char* hexToString(int value);
  const char* hexToString(long long value);


  const char* IntegerToString(uint8_t value);
  const char* IntegerToString(uint16_t value);
  const char* IntegerToString(uint32_t value);
  const char* IntegerToString(uint64_t value);

  const char* IntegerToString(char value);
  const char* IntegerToString(short value);
  const char* IntegerToString(int value);
  const char* IntegerToString(long long value);
}
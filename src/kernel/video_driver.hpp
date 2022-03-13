#pragma once
#include "../types.hpp"

#define VIDEO_MEMORY (uint8_t*) 0xA0000

namespace video {
    void putpixel(unsigned char* screen, int x, int y, int color);
}
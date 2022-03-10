#pragma once

typedef unsigned long long uint64_t;
typedef unsigned long int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

struct FlagsLimit {
    uint8_t limit : 4;
    uint8_t flags : 4;
};

struct GDTEntry64
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_medium;
    uint8_t access_byte;
    FlagsLimit flags_limit;
    uint8_t base_high;
    uint32_t base4;
    uint32_t reserved;
};

struct GDTEntry32
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_medium;
    uint8_t access_byte;
    FlagsLimit flags_limit;
    uint8_t base_high;
};

struct IDT64
{
  uint16_t offset_low;
  uint16_t selector;
  uint8_t ist;
  uint8_t types_attr;
  uint16_t offset_mid;
  uint32_t offset_high;
  uint32_t zero;
};
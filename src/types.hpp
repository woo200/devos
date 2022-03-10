#pragma once

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

/**
 * @brief Flags & Limit of GDT entry
 * 
 */
struct FlagsLimit {
    uint8_t limit : 4; /** Limit */
    uint8_t flags : 4; /** Flags */
};

/**
 * @brief 64 Bit GDT entry struct
 * 
 */
struct GDTEntry64
{
    uint16_t limit;         /** GDT Entry Limit */
    uint16_t base_low;      /** Base Low */
    uint8_t base_medium;    /** Base Medium */
    uint8_t access_byte;    /** Acces Byte */
    FlagsLimit flags_limit; /** Flags Limit */
    uint8_t base_high;      /** Base High */
    uint32_t base4;         /** Base High(er) */
    uint32_t reserved;      /** Reserved (must be 0) */
};

/**
 * @brief 32 Bit GDT entry struct
 * 
 */
struct GDTEntry32
{
    uint16_t limit;         /** GDT Entry Limit */
    uint16_t base_low;      /** Base Low */
    uint8_t base_medium;    /** Base Mdeium */
    uint8_t access_byte;    /** Access Byte */
    FlagsLimit flags_limit; /** Flags Limit */
    uint8_t base_high;      /** Base High */
};

/**
 * @brief 64 bit IDT entry struct
 * 
 */
struct IDT64
{
  uint16_t offset_low;  /** Offset Low */
  uint16_t selector;    /** Selector */
  uint8_t ist;          /** IST */
  uint8_t types_attr;   /** Types Attributes*/
  uint16_t offset_mid;  /** Offset Medium */
  uint32_t offset_high; /** Offset High */
  uint32_t zero;        /** Reserved */
};
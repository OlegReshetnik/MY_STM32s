#pragma once

#include "system.h"

// pins
#define DAT_PIN     10 // dat pin
#define DAT_PORT    GPIOA // dat port

#define CLK_PIN     9 // clock pin
#define CLK_PORT    GPIOA // clock port

//      Bits:                 Hex:
//        -- 0 --               -- 01 --
//       |       |             |        |
//       5       1            20        02
//       |       |             |        |
//        -- 6 --               -- 40 --
//       |       |             |        |
//       4       2            10        04
//       |       |             |        |
//        -- 3 --  .7           -- 08 --   .80

#define _A 0x77
#define _B 0x7f
#define _C 0x39
#define _D 0x3f
#define _E 0x79
#define _F 0x71
#define _G 0x3d
#define _H 0x76
#define _J 0x1e
#define _L 0x38
#define _N 0x37
#define _O 0x3f
#define _P 0x73
#define _S 0x6d
#define _U 0x3e
#define _Y 0x6e
#define _a 0x5f
#define _b 0x7c
#define _c 0x58
#define _d 0x5e
#define _e 0x7b
#define _f 0x71
#define _h 0x74
#define _i 0x10
#define _j 0x0e
#define _l 0x06
#define _n 0x54
#define _o 0x5c
#define _q 0x67
#define _r 0x50
#define _t 0x78
#define _u 0x1c
#define _y 0x6e
#define _minus 0x40
#define _under 0x08
#define _equal 0x48
#define _degree 0x63
#define _err 0x49
#define _plus 0x44
#define _space 0x00

#define _0 0x3f
#define _1 0x06
#define _2 0x5b
#define _3 0x4f
#define _4 0x66
#define _5 0x6d
#define _6 0x7d
#define _7 0x07
#define _8 0x7f
#define _9 0x6f

void TmClear(void);
void TmSetBright(const uint8_t brightness); // 0-7
void TmWriteByte(const uint8_t position, const uint8_t b); // position 0-3
void TmWriteBytes(const uint8_t b0, const uint8_t b1, const uint8_t b2, const uint8_t b3);
void TmWriteDigit(const uint8_t position, const uint8_t digit); // position 0-3, digit 0x00-0x0F
void TmColon(uint8_t on); // on != 0 -> colon on
void TmWriteTime(uint16_t sec); // 00:00
void TmWriteInt(uint16_t val); // 0-9999, in 99 -> show 0099
void TmInit(void); // init

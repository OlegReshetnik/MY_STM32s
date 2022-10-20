#include "tm1637.h"

#define _dot                    0x80

#define TM1637_DIGITS           4
#define COLON_POS		        1

// Instructions
#define TM_DATA_CMD             0x40
#define TM_DISP_CTRL            0x80
#define TM_ADDR_CMD             0xC0

// Data command set
#define TM_WRITE_DISP           0x00
#define TM_READ_KEYS            0x02
#define TM_FIXED_ADDR           0x04

// Display control command
#define TM_DISP_PWM_MASK        0x07 // First 3 bits are brightness (PWM controlled)
#define TM_DISP_ENABLE          0x08

#define DELAY_US                10

static const uint8_t digits[] = { _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C, _D, _E, _F };

static uint8_t _colon_mask = 0, _byte_colon = 0;

static void _del_1us(void) {
    volatile uint8_t i = 48;
    while(i--) { __NOP(); }
}

static void _del_us(uint16_t us) {
    while(us--) { _del_1us(); }
}

static void _clk_low(){
    CLK_PORT->BRR = 1 << CLK_PIN;
    _del_us(6);
}

static void _clk_hi(){
    CLK_PORT->BSRR = 1 << CLK_PIN;
    _del_us(6);
}


static void _dat(uint8_t level) {
    if (level) {  DAT_PORT->BSRR = 1 << DAT_PIN; }
    else { DAT_PORT->BRR = 1 << DAT_PIN; }
    _del_us(6);
}

static void _start(void) {
	_clk_hi();
	_dat(1);
	_dat(0);
	_clk_low();
}

static void _stop(void) {
	_clk_low();
	_dat(0);
	_clk_hi();
	_dat(1);
}

static void _send(uint8_t b) {
    for (uint8_t i = 0; i<8; i++) {
        _clk_low();
        _dat(b&1);
        b >>= 1;
        _clk_hi();
    }
    _clk_low();
    _dat(1);
    _clk_hi();
    _del_us(10);
}

static void _send_cmd(const uint8_t cmd) {
    _start();
    _send(cmd);
    _stop();
}

static void _send_data(const uint8_t addr, const uint8_t data) {
    _send_cmd(TM_DATA_CMD | TM_FIXED_ADDR);
    _start();
    _send(TM_ADDR_CMD | addr);
    _send(data);
    _stop();
}

void TmClear(void) { for (uint8_t a = 0; a < TM1637_DIGITS; ++a) { _send_data(a, _space); } }

void TmSetBright(const uint8_t brightness) { _send_cmd(TM_DISP_CTRL | TM_DISP_ENABLE | (brightness & TM_DISP_PWM_MASK)); }

void TmWriteByte(const uint8_t position, const uint8_t b) {
    _send_data(position, b | _colon_mask );
    if (position == COLON_POS) _byte_colon = b;
}

void TmWriteBytes(const uint8_t b0, const uint8_t b1, const uint8_t b2, const uint8_t b3) {
    TmWriteByte(0, b0);
    TmWriteByte(1, b1);
    TmWriteByte(2, b2);
    TmWriteByte(3, b3);
}

void TmWriteDigit(const uint8_t position, const uint8_t digit) { TmWriteByte(position, digits[digit&0xF]); }

void TmColon(uint8_t on) {
    if (on) { _colon_mask = _dot; }
    else { _colon_mask = 0; }
    _send_data(COLON_POS, _byte_colon | _colon_mask);
}

void TmWriteTime(uint16_t sec) {
    uint8_t mm = sec / 60, ss = sec % 60;
    _colon_mask = _dot;
    TmWriteDigit(0, mm / 10);
    TmWriteDigit(1, mm % 10);
    TmWriteDigit(2, ss / 10);
    TmWriteDigit(3, ss % 10);
}

void TmWriteInt(uint16_t val) {
    _colon_mask = 0;
    TmWriteDigit(0, val/1000);
    TmWriteDigit(1, (val/100)%10);
    TmWriteDigit(2, (val/10)%10);
    TmWriteDigit(3, val%10);
}

void TmInit(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // enable clock AHB, PA9, PA10
    GPIOA->MODER |= GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0; // 01: General purpose output mode PA9, PA10
    GPIOA->OTYPER |= GPIO_OTYPER_OT_9 | GPIO_OTYPER_OT_10; // 1: Output open-drain PA9, PA10
    //GPIOA->OSPEEDR |= 0; // x0: Low speed
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR10_0; // 01: Pull-up PA9, PA10
    _send_cmd(TM_DATA_CMD | TM_WRITE_DISP);
    _send_cmd(TM_DISP_CTRL | TM_DISP_ENABLE | TM_DISP_PWM_MASK);
    TmClear();
}

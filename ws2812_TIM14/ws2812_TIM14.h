#pragma once

#include "system.h"

//#define WS_GAMMA_TABLE // использовать таблицу гамма коррекции, если не определено, то используем вычисление

// Настройки порта ленты
#define WS_PORT		    GPIOA // ws port
#define WS_PIN	    	9 // ws pin
#define WS_MASK	    	(1 << WS_PIN)

#define WS_LO	19
#define WS_HI	39
#define WS_INT	60


#define NUM_LEDS		12 // количество светодиодов
#define NUM_BYTES       (NUM_LEDS*3)

void WsInit(void);
void WsSend(void);

void wsWeel(void);
void wsFire(void);
void wsColors(void);
void wsSparkles(void);
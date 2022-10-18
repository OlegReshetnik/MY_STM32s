#pragma once

#include "system.h"

//#define WS_GAMMA_TABLE // использовать таблицу гамма коррекции, если не определено, то используем вычисление

// Настройки порта ленты
#define WS_PIN	    	6 // пин подключения
#define WS_PORT		    GPIOA // порт подключения

#define NUM_LEDS		12 // количество светодиодов
#define NUM_BYTES       (NUM_LEDS*3)

void WsInit(void);
void WsSend(void);

void wsWeel(void);
void wsFire(void);
void wsColors(void);
void wsSparkles(void);
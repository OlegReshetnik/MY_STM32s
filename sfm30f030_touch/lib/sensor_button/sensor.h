#pragma once

#include "system.h"

#define SENSOR_PORT     GPIOA
#define SENSOR_PIN      0
#define SENSOR_MASK     (1<<SENSOR_PIN)

void SensorInit(void);
uint8_t SensorTouch(void); // return !=0 is touch

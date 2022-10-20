#include "sensor.h"

static uint16_t SensorStartValue; 

static uint8_t SensorReadOnce(void) {
    uint8_t cnt = 0;

    SENSOR_PORT->MODER |= GPIO_MODER_MODER0_0; // 01: Output mode PA0
    SENSOR_PORT->PUPDR &= ~(GPIO_PUPDR_PUPDR0_0); // 00: No pull-up, pull-down PA0
    SENSOR_PORT->BRR = SENSOR_MASK;

    SENSOR_PORT->MODER &= ~(GPIO_MODER_MODER0_0); // 00: Input mode PA0
    SENSOR_PORT->PUPDR |= GPIO_PUPDR_PUPDR0_0; // 01: Pull-up PA0

    while((SENSOR_PORT->IDR & SENSOR_MASK) == 0) { cnt++; }

    return cnt;
}

uint16_t SensorRead(uint16_t numRead) {
    uint16_t sum = 0;
    while (numRead--) { sum += SensorReadOnce(); }
    return sum;
}

uint8_t SensorTouch(void) {
    return (  SensorRead(1000) > ( (SensorStartValue + (SensorStartValue << 4)) >> 4 )  );
}

void SensorInit(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN; // PA, PB

    //SENSOR_PORT->MODER &= ~(GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1); // 00: Input mode (reset state) PA0
    //SENSOR_PORT->OTYPER |= GPIO_OTYPER_OT_9 | GPIO_OTYPER_OT_10; // 1: Output open-drain PA9, PA10
    //SENSOR_PORT->OSPEEDR |= 0; // x0: Low speed
    //SENSOR_PORT->PUPDR |= GPIO_PUPDR_PUPDR0_0; // 01: Pull-up PA0

    SensorStartValue = SensorRead(1000);
}

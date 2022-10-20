#include "system.h"
#include "sensor.h"

#define LED_PORT        GPIOA
#define LED_PIN         4
#define LED_MASK        (1<<LED_PIN)

void LedInit(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN; // PA, PB
    LED_PORT->MODER |= GPIO_MODER_MODER4_0; // 01: Output mode PA4
}

void SetLed(uint8_t level) {
    if (!level) {  LED_PORT->BSRR = LED_MASK; }
    else { LED_PORT->BRR = LED_MASK; }
}

int main(void) {
    uint32_t oldT = 0;

    SysInit();
    SensorInit();
    LedInit();

    for(;;) {
        if ((millis-oldT) >= 5) {
            oldT = millis;
            SetLed(SensorTouch());
        }
    }
}

#include "system.h"

#ifdef HSE
    void SysCockSet48HSE(void) {
        RCC->CR |= RCC_CR_HSEON;	// Enable HSE
        while ((RCC->CR & RCC_CR_HSERDY) == 0) { ; } // Wait until HSE is ready
        FLASH->ACR |= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY; // Enable Prefetch Buffer & set Flash access to 1 wait states
        RCC->CFGR |= RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR_PLLMUL6; // SYSCLK = PCLK = HCLK, PLLCLK = HSE * 6 = 48 MHz
        RCC->CR |= RCC_CR_PLLON; // Enable PLL
        while ((RCC->CR & RCC_CR_PLLRDY) == 0) { ; } // Wait until PLL is ready
        RCC->CFGR |= RCC_CFGR_SW_PLL; // Select PLL as system clock source
        while ((RCC->CFGR & RCC_CFGR_SWS_PLL) == 0) { ; } // Wait until PLL is used as system clock source
    }
    #define SysClockInit()    SysCockSet48HSE()
#else
    void SysClockSet48HSI(void) {
        FLASH->ACR |= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY; // Enable Prefetch Buffer & set Flash access to 1 wait states
        RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2 | RCC_CFGR_PLLMUL12; // SYSCLK = PCLK = HCLK, PLLCLK = HSE * 6 = 48 MHz
        RCC->CR |= RCC_CR_PLLON; // Enable PLL
        while ((RCC->CR & RCC_CR_PLLRDY) == 0) { ; } // Wait until PLL is ready
        RCC->CFGR |= RCC_CFGR_SW_PLL; // Select PLL as system clock source
        while ((RCC->CFGR & RCC_CFGR_SWS_PLL) == 0) { ; } // Wait until PLL is used as system clock source
    }
    #define SysClockInit()    SysClockSet48HSI()
#endif

volatile uint32_t millis = 0;

void SysTick_Handler(void) { millis++; }

void SysInit() {
    SysClockInit();
    SysTick_Config(48000);
}

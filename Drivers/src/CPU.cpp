
#include "CPU.hpp"

#ifdef USE_OSC
#define XTAL_VALUE (HSE_VALUE / 1000000u)
#else
#define XTAL_VALUE (HSI_VALUE / 1000000u)
#endif /* USE_OSC */

#define PLL_N_VALUE	(432)
#define PLL_Q_VALUE (9)

#define HPRE_PRESCALE (0)
#define PPRE1_PRESCALE (5)
#define PPRE2_PRESCALE (4)

#define FLASH_LATENCY (9)

CPU::CPU(void) {

	uint32_t pllM = XTAL_VALUE;

	SCB_EnableICache();
	SCB_EnableDCache();

    RCC->APB1ENR |= 0x10000000;

#ifdef USE_OSC
    RCC->CR |= 0x00010000;
    while((RCC->CR & 0x00020000) == 0) {}

    RCC->CR &= 0xFFFFFFFE;
#else
    RCC->CR |= 0x00000001;
    while((RCC->CR & 0x00000002) == 0) {}

    RCC->CR &= 0xFFFEFFFF;
#endif /* USE_OSC */

    RCC->PLLCFGR &= 0xF0DC8000;

#ifdef USE_OSC
    RCC->PLLCFGR |= 0x00400000;
#endif /* USE_OSC */

    RCC->PLLCFGR |= pllM | (PLL_N_VALUE << 6) | (PLL_Q_VALUE << 24);

    PWR->CR1 |= 0x00010000;
    while((PWR->CSR1 & 0x00010000) == 0) {};

    RCC->CFGR = 0x00000000;

    RCC->CFGR |= (PPRE2_PRESCALE << 13) | (PPRE1_PRESCALE << 10) | (HPRE_PRESCALE << 4);

    FLASH->ACR &= 0xFFFFF4F0;
    FLASH->ACR |= FLASH_LATENCY | 0x00000100;

    RCC->CFGR |= 0x00000002;

    while((RCC->CFGR & 0x00000008) == 0) {}
}

void assert_failed(uint8_t* file, uint32_t line) {

    while(1) {}
}


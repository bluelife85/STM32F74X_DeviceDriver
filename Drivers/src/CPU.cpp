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

CPUClass CPU;
uint8_t isInitialized;

CPUClass::CPUClass(void) {

	uint32_t pllM = XTAL_VALUE;

	if(isInitialized) {

		assert_failed(__FILE__, __LINE__);
	}

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

void CPUClass::enableIRQ(enum CoreInterrupt irq, void (*evt)(void)) {

	uint32_t index = (uint32_t) irq;

	switch(irq) {
	case CPUClass::IRQ_NMI:
		NVIC_EnableIRQ(NonMaskableInt_IRQn);
		break;
	case CPUClass::IRQ_HardFault:
		break;
	case CPUClass::IRQ_MemManage:
		NVIC_EnableIRQ(MemoryManagement_IRQn);
		break;
	case CPUClass::IRQ_BusFault:
		NVIC_EnableIRQ(BusFault_IRQn);
		break;
	case CPUClass::IRQ_UsageFault:
		NVIC_EnableIRQ(UsageFault_IRQn);
		break;
	case CPUClass::IRQ_SVCall:
		NVIC_EnableIRQ(SVCall_IRQn);
		break;
	case CPUClass::IRQ_DebugMon:
		NVIC_EnableIRQ(DebugMonitor_IRQn);
		break;
	case CPUClass::IRQ_PendSV:
		NVIC_EnableIRQ(PendSV_IRQn);
		break;
	case CPUClass::IRQ_SysTick:
		NVIC_EnableIRQ(SysTick_IRQn);
		break;
	}

	this->coreHandlers[index] = evt;
}

void CPUClass::disableIRQ(enum CoreInterrupt irq) {

	uint32_t index = (uint32_t) irq;

	switch(irq) {
	case this->IRQ_NMI:
		NVIC_DisableIRQ(NonMaskableInt_IRQn);
		break;
	case this->IRQ_HardFault:
		break;
	case this->IRQ_MemManage:
		NVIC_DisableIRQ(MemoryManagement_IRQn);
		break;
	case this->IRQ_BusFault:
		NVIC_DisableIRQ(BusFault_IRQn);
		break;
	case this->IRQ_UsageFault:
		NVIC_DisableIRQ(UsageFault_IRQn);
		break;
	case this->IRQ_SVCall:
		NVIC_DisableIRQ(SVCall_IRQn);
		break;
	case this->IRQ_DebugMon:
		NVIC_DisableIRQ(DebugMonitor_IRQn);
		break;
	case this->IRQ_PendSV:
		NVIC_DisableIRQ(PendSV_IRQn);
		break;
	case this->IRQ_SysTick:
		NVIC_DisableIRQ(SysTick_IRQn);
		break;
	}

	this->coreHandlers[index] = NULL;
}

CallbackHandler CPUClass::getHandler(enum CoreInterrupt irq) {

	return this->coreHandlers[(uint32_t)irq];
}

CallbackHandler CPUClass::getHandler(enum EventInterrupt irq) {

    CallbackHandler ret = NULL;

    try {
        if(irq == IRQ_EVT_INDEX_ERROR)
            throw "Not correct IRQ";

        ret = this->EventCallbacks[(uint32_t)irq];
    } catch (const char* s) {

        assert_failed(s,__LINE__);
    }

	return ret;
}

void CPUClass::clearEventTrigger(enum EventInterrupt irq) {

	switch(irq) {
	case this->IRQ_EVT_INDEX_ERROR:
	    break;
	case this->IRQ_WWDG_EVT_EARLY_WAKEUP:
		WWDG->SR &= 0xFFFFFFFE;
		break;
	case this->IRQ_EXTI_EVT_PVD:
		EXTI->PR |= ~0x00010000;
		break;
	case this->IRQ_RTC_EVT_TIMESTAMP:
		RTC->ISR &= 0x00020800;
		break;
	case this->IRQ_RTC_EVT_TAMP1:
	    RTC->ISR &= ~0x00002000;
		break;
	case this->IRQ_RTC_EVT_TAMP2:
	    RTC->ISR &= ~0x00004000;
		break;
	case this->IRQ_RTC_EVT_TAMP3:
	    RTC->ISR &= ~0x00008000;
		break;
	case this->IRQ_RTC_EVT_WAKEUP:
	    RTC->ISR &= ~0x00000400;
	    break;
	case this->IRQ_FLASH_EVT_EOP:
	    FLASH->SR |= 0x00000001;
	    break;
	case this->IRQ_FLASH_EVT_WRITE_PROTECTION_ERR:
	    FLASH->SR |= 0x00000012;
	    break;
	case this->IRQ_FLASH_EVT_ALIGNMENT_ERR:
	    FLASH->SR |= 0x00000022;
	    break;
	case this->IRQ_FLASH_EVT_PARALLEISM_ERR:
	    FLASH->SR |= 0x00000042;
	    break;
	case this->IRQ_FLASH_EVT_SEQUENCE_ERR:
	    FLASH->SR |= 0x00000082;
	    break;
	case this->IRQ_RCC_EVT_LSI_READY:
	    RCC->CR |= 0x00010000;
	    break;
	case this->IRQ_RCC_EVT_LSE_READY:
	    RCC->CR |= 0x00020000;
	    break;
	case this->IRQ_RCC_EVT_HSI_READY:
	    RCC->CR |= 0x00040000;
	    break;
	case this->IRQ_RCC_EVT_HSE_READY:
	    RCC->CR |= 0x00080000;
	    break;
	case this->IRQ_RCC_EVT_PLL_READY:
	    RCC->CR |= 0x00100000;
	    break;
	case this->IRQ_RCC_EVT_PLLI2S_READY:
	    RCC->CR |= 0x00200000;
	    break;
	case this->IRQ_RCC_EVT_PLLSAI_READY:
	    RCC->CR |= 0x00400000;
	    break;
	case this->IRQ_RCC_EVT_CSS:
	    RCC->CR |= 0x00800000;
	    break;
	case this->IRQ_EXTI_EVT_0:
        EXTI->PR |= 0x00000001;
        break;
	case this->IRQ_EXTI_EVT_1:
	    EXTI->PR |= 0x00000002;
	    break;
	case this->IRQ_EXTI_EVT_2:
	    EXTI->PR |= 0x00000004;
	    break;
	case this->IRQ_EXTI_EVT_3:
	    EXTI->PR |= 0x00000008;
	    break;
	case this->IRQ_EXTI_EVT_4:
	    EXTI->PR |= 0x00000010;
	    break;
	}
}

void assert_failed(const char* file, uint32_t line) {

	__disable_irq();

    while(1) {}
}

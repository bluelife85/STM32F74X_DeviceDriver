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
	case CPUClass::IRQ_NMI:
		NVIC_DisableIRQ(NonMaskableInt_IRQn);
		break;
	case CPUClass::IRQ_HardFault:
		break;
	case CPUClass::IRQ_MemManage:
		NVIC_DisableIRQ(MemoryManagement_IRQn);
		break;
	case CPUClass::IRQ_BusFault:
		NVIC_DisableIRQ(BusFault_IRQn);
		break;
	case CPUClass::IRQ_UsageFault:
		NVIC_DisableIRQ(UsageFault_IRQn);
		break;
	case CPUClass::IRQ_SVCall:
		NVIC_DisableIRQ(SVCall_IRQn);
		break;
	case CPUClass::IRQ_DebugMon:
		NVIC_DisableIRQ(DebugMonitor_IRQn);
		break;
	case CPUClass::IRQ_PendSV:
		NVIC_DisableIRQ(PendSV_IRQn);
		break;
	case CPUClass::IRQ_SysTick:
		NVIC_DisableIRQ(SysTick_IRQn);
		break;
	}

	this->coreHandlers[index] = NULL;
}

CallbackHandler CPUClass::getHandler(enum CoreInterrupt irq) {

	return this->coreHandlers[(uint32_t)irq];
}

void assert_failed(const char* file, uint32_t line) {

	__disable_irq();

    while(1) {}
}

/**
 * interrupt vectors
 */
void NMI_Handler(void) {

	CallbackHandler handler = CPU.getHandler(CPU.IRQ_NMI);

	if(handler == NULL) {

		assert_failed("Attempted to access a NULL pointer.", __LINE__);
	}

	handler();
}

void HardFault_Handler(void) {

	CallbackHandler handler = CPU.getHandler(CPU.IRQ_HardFault);

	if(handler == NULL) {

		assert_failed("Attempted to access a NULL pointer.", __LINE__);
	}

	handler();
}

void MemManage_Handler(void) {

	CallbackHandler handler = CPU.getHandler(CPU.IRQ_MemManage);

	if(handler == NULL) {

		assert_failed("Attempted to access a NULL pointer.", __LINE__);
	}

	handler();
}

void BusFault_Handler(void) {

	CallbackHandler handler = CPU.getHandler(CPU.IRQ_BusFault);

	if(handler == NULL) {

		assert_failed("Attempted to access a NULL pointer.", __LINE__);
	}

	handler();
}

void UsageFault_Handler(void) {

	CallbackHandler handler = CPU.getHandler(CPU.IRQ_UsageFault);

	if(handler == NULL) {

		assert_failed("Attempted to access a NULL pointer.", __LINE__);
	}

	handler();
}

void SVC_Handler(void) {

	CallbackHandler handler = CPU.getHandler(CPU.IRQ_SVCall);

	if(handler == NULL) {

		assert_failed("Attempted to access a NULL pointer.", __LINE__);
	}

	handler();
}

void DebugMon_Handler(void) {

	CallbackHandler handler = CPU.getHandler(CPU.IRQ_DebugMon);

	if(handler == NULL) {

		assert_failed("Attempted to access a NULL pointer.", __LINE__);
	}

	handler();
}

void PendSV_Handler(void) {

	CallbackHandler handler = CPU.getHandler(CPU.IRQ_PendSV);

	if(handler == NULL) {

		assert_failed("Attempted to access a NULL pointer.", __LINE__);
	}

	handler();
}

void SysTick_Handler(void) {

	CallbackHandler handler = CPU.getHandler(CPU.IRQ_SysTick);

	if(handler == NULL) {

		assert_failed("Attempted to access a NULL pointer.", __LINE__);
	}

	handler();
}

void WWDG_IRQHandler(void) {}
void PVD_IRQHandler(void) {}
void TAMP_STAMP_IRQHandler(void) {}
void RTC_WKUP_IRQHandler(void) {}
void FLASH_IRQHandler(void) {}
void RCC_IRQHandler(void) {}
void EXTI0_IRQHandler(void) {}
void EXTI1_IRQHandler(void) {}
void EXTI2_IRQHandler(void) {}
void EXTI3_IRQHandler(void) {}
void EXTI4_IRQHandler(void) {}
void DMA1_Stream0_IRQHandler(void) {}
void DMA1_Stream1_IRQHandler(void) {}
void DMA1_Stream2_IRQHandler(void) {}
void DMA1_Stream3_IRQHandler(void) {}
void DMA1_Stream4_IRQHandler(void) {}
void DMA1_Stream5_IRQHandler(void) {}
void DMA1_Stream6_IRQHandler(void) {}
void ADC_IRQHandler(void) {}
void CAN1_TX_IRQHandler(void) {}
void CAN1_RX0_IRQHandler(void) {}
void CAN1_RX1_IRQHandler(void) {}
void CAN1_SCE_IRQHandler(void) {}
void EXTI9_5_IRQHandler(void) {}
void TIM1_BRK_TIM9_IRQHandler(void) {}
void TIM1_UP_TIM10_IRQHandler(void) {}
void TIM1_TRG_COM_TIM11_IRQHandler(void) {}
void TIM1_CC_IRQHandler(void) {}
void TIM2_IRQHandler(void) {}
void TIM3_IRQHandler(void) {}
void TIM4_IRQHandler(void) {}
void I2C1_EV_IRQHandler(void) {}
void I2C1_ER_IRQHandler(void) {}
void I2C2_EV_IRQHandler(void) {}
void I2C2_ER_IRQHandler(void) {}
void SPI1_IRQHandler(void) {}
void SPI2_IRQHandler(void) {}
void USART1_IRQHandler(void) {}
void USART2_IRQHandler(void) {}
void USART3_IRQHandler(void) {}
void EXTI15_10_IRQHandler(void) {}
void RTC_Alarm_IRQHandler(void) {}
void OTG_FS_WKUP_IRQHandler(void) {}
void TIM8_BRK_TIM12_IRQHandler(void) {}
void TIM8_UP_TIM13_IRQHandler(void) {}
void TIM8_TRG_COM_TIM14_IRQHandler(void) {}
void TIM8_CC_IRQHandler(void) {}
void DMA1_Stream7_IRQHandler(void) {}
void FMC_IRQHandler(void) {}
void SDMMC1_IRQHandler(void) {}
void TIM5_IRQHandler(void) {}
void SPI3_IRQHandler(void) {}
void UART4_IRQHandler(void) {}
void UART5_IRQHandler(void) {}
void TIM6_DAC_IRQHandler(void) {}
void TIM7_IRQHandler(void) {}
void DMA2_Stream0_IRQHandler(void) {}
void DMA2_Stream1_IRQHandler(void) {}
void DMA2_Stream2_IRQHandler(void) {}
void DMA2_Stream3_IRQHandler(void) {}
void DMA2_Stream4_IRQHandler(void) {}
void ETH_IRQHandler(void) {}
void ETH_WKUP_IRQHandler(void) {}
void CAN2_TX_IRQHandler(void) {}
void CAN2_RX0_IRQHandler(void) {}
void CAN2_RX1_IRQHandler(void) {}
void CAN2_SCE_IRQHandler(void) {}
void OTG_FS_IRQHandler(void) {}
void DMA2_Stream5_IRQHandler(void) {}
void DMA2_Stream6_IRQHandler(void) {}
void DMA2_Stream7_IRQHandler(void) {}
void USART6_IRQHandler(void) {}
void I2C3_EV_IRQHandler(void) {}
void I2C3_ER_IRQHandler(void) {}
void OTG_HS_EP1_OUT_IRQHandler(void) {}
void OTG_HS_EP1_IN_IRQHandler(void) {}
void OTG_HS_WKUP_IRQHandler(void) {}
void OTG_HS_IRQHandler(void) {}
void DCMI_IRQHandler(void) {}
void RNG_IRQHandler(void) {}
void FPU_IRQHandler(void) {}
void UART7_IRQHandler(void) {}
void UART8_IRQHandler(void) {}
void SPI4_IRQHandler(void) {}
#if !defined (LQFP100)
void SPI5_IRQHandler(void) {}
void SPI6_IRQHandler(void) {}
#endif /* !defined (LQFP100) */
void SAI1_IRQHandler(void) {}
#if !defined (STM32F745)
void LTDC_IRQHandler(void) {}
void LTDC_ER_IRQHandler(void) {}
#endif /* !defined (STM32F745) */
void DMA2D_IRQHandler(void) {}
void SAI2_IRQHandler(void) {}
void QUADSPI_IRQHandler(void) {}
void LPTIM1_IRQHandler(void) {}
void CEC_IRQHandler(void) {}
void I2C4_EV_IRQHandler(void) {}
void I2C4_ER_IRQHandler(void) {}
void SPDIF_RX_IRQHandler(void) {}

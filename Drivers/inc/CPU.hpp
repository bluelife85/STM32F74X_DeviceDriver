#ifndef INC_CPU_HPP_
#define INC_CPU_HPP_

#include "stm32f74x.h"

class CPU{
private:
	void (*coreHandlers[9])(void);
	void (*EventCallbacks[])(void);
public:
	CPU();
};

#ifdef __cplusplus
extern "C" {
#endif /* cplusplus */
void assert_failed(const char* file, uint32_t line);

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void WWDG_IRQHandler(void);							/* it has 1 event. */
void PVD_IRQHandler(void);							/* it has 1 event. */
void TAMP_STAMP_IRQHandler(void);					/* it has 1 event. */
void RTC_WKUP_IRQHandler(void);						/* it has 1 event. */
void FLASH_IRQHandler(void);						/* it has 3 events. */
void RCC_IRQHandler(void);							/* it has 7 events. */
void EXTI0_IRQHandler(void);						/* it has 2 events. */
void EXTI1_IRQHandler(void);						/* it has 2 events. */
void EXTI2_IRQHandler(void);						/* it has 2 events. */
void EXTI3_IRQHandler(void);						/* it has 2 events. */
void EXTI4_IRQHandler(void);						/* it has 2 events. */
void DMA1_Stream0_IRQHandler(void);					/* it has 5 events. */
void DMA1_Stream1_IRQHandler(void);					/* it has 5 events. */
void DMA1_Stream2_IRQHandler(void);					/* it has 5 events. */
void DMA1_Stream3_IRQHandler(void);					/* it has 5 events. */
void DMA1_Stream4_IRQHandler(void);					/* it has 5 events. */
void DMA1_Stream5_IRQHandler(void);					/* it has 5 events. */
void DMA1_Stream6_IRQHandler(void);					/* it has 5 events. */
void ADC_IRQHandler(void);							/* it has 12 events. */
void CAN1_TX_IRQHandler(void);						/* it has 3 events. */
void CAN1_RX0_IRQHandler(void);						/* it has 3 events. */
void CAN1_RX1_IRQHandler(void);						/* it has 3 events. */
void CAN1_SCE_IRQHandler(void);						/* it has 5 events. */
void EXTI9_5_IRQHandler(void);						/* it has 5 events. */
void TIM1_BRK_TIM9_IRQHandler(void);				/* it has 5 events. */
void TIM1_UP_TIM10_IRQHandler(void);				/* it has 5 events. */
void TIM1_TRG_COM_TIM11_IRQHandler(void);			/* it has 5 events. */
void TIM1_CC_IRQHandler(void);						/* it has 4 events. */
void TIM2_IRQHandler(void);							/* it has 6 events. */
void TIM3_IRQHandler(void);							/* it has 6 events. */
void TIM4_IRQHandler(void);							/* it has 6 events. */
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void RTC_Alarm_IRQHandler(void);
void OTG_FS_WKUP_IRQHandler(void);
void TIM8_BRK_TIM12_IRQHandler(void);
void TIM8_UP_TIM13_IRQHandler(void);
void TIM8_TRG_COM_TIM14_IRQHandler(void);
void TIM8_CC_IRQHandler(void);
void DMA1_Stream7_IRQHandler(void);
void FMC_IRQHandler(void);
void SDMMC1_IRQHandler(void);
void TIM5_IRQHandler(void);
void SPI3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);
void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream1_IRQHandler(void);
void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);
void DMA2_Stream4_IRQHandler(void);
void ETH_IRQHandler(void);
void ETH_WKUP_IRQHandler(void);
void CAN2_TX_IRQHandler(void);
void CAN2_RX0_IRQHandler(void);
void CAN2_RX1_IRQHandler(void);
void CAN2_SCE_IRQHandler(void);
void OTG_FS_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);
void DMA2_Stream6_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);
void USART6_IRQHandler(void);
void I2C3_EV_IRQHandler(void);
void I2C3_ER_IRQHandler(void);
void OTG_HS_EP1_OUT_IRQHandler(void);
void OTG_HS_EP1_IN_IRQHandler(void);
void OTG_HS_WKUP_IRQHandler(void);
void OTG_HS_IRQHandler(void);
void DCMI_IRQHandler(void);
void RNG_IRQHandler(void);
void FPU_IRQHandler(void);
void UART7_IRQHandler(void);
void UART8_IRQHandler(void);
void SPI4_IRQHandler(void);
#if !defined (LQFP100)
void SPI5_IRQHandler(void);
void SPI6_IRQHandler(void);
#endif /* !defined (LQFP100) */
void SAI1_IRQHandler(void);
#if !defined (STM32F745)
void LTDC_IRQHandler(void);
void LTDC_ER_IRQHandler(void);
#endif /* !defined (STM32F745) */
void DMA2D_IRQHandler(void);
void SAI2_IRQHandler(void);
void QUADSPI_IRQHandler(void);
void LPTIM1_IRQHandler(void);
void CEC_IRQHandler(void);
void I2C4_EV_IRQHandler(void);
void I2C4_ER_IRQHandler(void);
void SPDIF_RX_IRQHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INC_CPU_HPP_ */

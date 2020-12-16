/*
 * interrupts.hpp
 *
 *  Created on: 2020. 12. 16.
 *      Author: bluel
 */

#ifndef INC_INTERRUPTS_HPP_
#define INC_INTERRUPTS_HPP_

#include "CPU.hpp"

#ifdef __cplusplus
extern "C" {
#endif /* cplusplus */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void WWDG_IRQHandler(void);
void PVD_IRQHandler(void);
void TAMP_STAMP_IRQHandler(void);
void RTC_WKUP_IRQHandler(void);
void FLASH_IRQHandler(void);
void RCC_IRQHandler(void);
void EXTI0_IRQHandler(void);                        /* it has 2 events. */
void EXTI1_IRQHandler(void);                        /* it has 2 events. */
void EXTI2_IRQHandler(void);                        /* it has 2 events. */
void EXTI3_IRQHandler(void);                        /* it has 2 events. */
void EXTI4_IRQHandler(void);                        /* it has 2 events. */
void DMA1_Stream0_IRQHandler(void);                 /* it has 5 events. */
void DMA1_Stream1_IRQHandler(void);                 /* it has 5 events. */
void DMA1_Stream2_IRQHandler(void);                 /* it has 5 events. */
void DMA1_Stream3_IRQHandler(void);                 /* it has 5 events. */
void DMA1_Stream4_IRQHandler(void);                 /* it has 5 events. */
void DMA1_Stream5_IRQHandler(void);                 /* it has 5 events. */
void DMA1_Stream6_IRQHandler(void);                 /* it has 5 events. */
void ADC_IRQHandler(void);                          /* it has 12 events. */
void CAN1_TX_IRQHandler(void);                      /* it has 3 events. */
void CAN1_RX0_IRQHandler(void);                     /* it has 3 events. */
void CAN1_RX1_IRQHandler(void);                     /* it has 3 events. */
void CAN1_SCE_IRQHandler(void);                     /* it has 5 events. */
void EXTI9_5_IRQHandler(void);                      /* it has 5 events. */
void TIM1_BRK_TIM9_IRQHandler(void);                /* it has 5 events. */
void TIM1_UP_TIM10_IRQHandler(void);                /* it has 5 events. */
void TIM1_TRG_COM_TIM11_IRQHandler(void);           /* it has 6 events. */
void TIM1_CC_IRQHandler(void);                      /* it has 4 events. */
void TIM2_IRQHandler(void);                         /* it has 6 events. */
void TIM3_IRQHandler(void);                         /* it has 6 events. */
void TIM4_IRQHandler(void);                         /* it has 6 events. */
void I2C1_EV_IRQHandler(void);                      /* it has 7 events. */
void I2C1_ER_IRQHandler(void);                      /* it has 6 events. */
void I2C2_EV_IRQHandler(void);                      /* it has 7 events. */
void I2C2_ER_IRQHandler(void);                      /* it has 6 events. */
void SPI1_IRQHandler(void);                         /* it has 6 events. */
void SPI2_IRQHandler(void);                         /* it has 6 events. */
void USART1_IRQHandler(void);                       /* it has 12 events. */
void USART2_IRQHandler(void);                       /* it has 12 events. */
void USART3_IRQHandler(void);                       /* it has 12 events. */
void EXTI15_10_IRQHandler(void);                    /* it has 6 events. */
void RTC_Alarm_IRQHandler(void);                    /* it has 1 event. */
void OTG_FS_WKUP_IRQHandler(void);                  /* it has 1 event. */
void TIM8_BRK_TIM12_IRQHandler(void);               /* it has 5 events. */
void TIM8_UP_TIM13_IRQHandler(void);                /* it has 5 events. */
void TIM8_TRG_COM_TIM14_IRQHandler(void);           /* it has 6 events. */
void TIM8_CC_IRQHandler(void);                      /* it has 4 events. */
void DMA1_Stream7_IRQHandler(void);                 /* it has 5 events. */
void FMC_IRQHandler(void);                          /* it has 7 events. */
void SDMMC1_IRQHandler(void);                       /* it has 22 events. */
void TIM5_IRQHandler(void);                         /* it has 6 events. */
void SPI3_IRQHandler(void);                         /* it has 6 events. */
void UART4_IRQHandler(void);                        /* it has 12 events. */
void UART5_IRQHandler(void);                        /* it has 12 events. */
void TIM6_DAC_IRQHandler(void);                     /* it has 3 events. */
void TIM7_IRQHandler(void);                         /* it has 1 event. */
void DMA2_Stream0_IRQHandler(void);                 /* it has 5 events. */
void DMA2_Stream1_IRQHandler(void);                 /* it has 5 events. */
void DMA2_Stream2_IRQHandler(void);                 /* it has 5 events. */
void DMA2_Stream3_IRQHandler(void);                 /* it has 5 events. */
void DMA2_Stream4_IRQHandler(void);                 /* it has 5 events. */
void ETH_IRQHandler(void);                          /* it has 24 events. */
void ETH_WKUP_IRQHandler(void);                     /* it has 1 event. */
void CAN2_TX_IRQHandler(void);                      /* it has 3 events. */
void CAN2_RX0_IRQHandler(void);                     /* it has 3 events. */
void CAN2_RX1_IRQHandler(void);                     /* it has 3 events. */
void CAN2_SCE_IRQHandler(void);                     /* it has 5 events. */
void OTG_FS_IRQHandler(void);                       /* it has 26 events. */
void DMA2_Stream5_IRQHandler(void);                 /* it has 5 events. */
void DMA2_Stream6_IRQHandler(void);                 /* it has 5 events. */
void DMA2_Stream7_IRQHandler(void);                 /* it has 5 events. */
void USART6_IRQHandler(void);                       /* it has 12 events. */
void I2C3_EV_IRQHandler(void);                      /* it has 6 events. */
void I2C3_ER_IRQHandler(void);                      /* it has 6 events. */
void OTG_HS_EP1_OUT_IRQHandler(void);               /* it has 1 event. */
void OTG_HS_EP1_IN_IRQHandler(void);                /* it has 1 event. */
void OTG_HS_WKUP_IRQHandler(void);                  /* it has 1 event. */
void OTG_HS_IRQHandler(void);                       /* it has 27 events. */
void DCMI_IRQHandler(void);                         /* it has 6 events. */
void RNG_IRQHandler(void);                          /* it has 3 events. */
void FPU_IRQHandler(void);                          /* it has 14 events. */
void UART7_IRQHandler(void);                        /* it has 12 events. */
void UART8_IRQHandler(void);                        /* it has 12 events. */
void SPI4_IRQHandler(void);                         /* it has 6 events. */
#if !defined (LQFP100)
void SPI5_IRQHandler(void);                         /* it has 6 events. */
void SPI6_IRQHandler(void);                         /* it has 6 events. */
#endif /* !defined (LQFP100) */
void SAI1_IRQHandler(void);                         /* it has 7 events. */
#if !defined (STM32F745)
void LTDC_IRQHandler(void);                         /* it has 2 events. */
void LTDC_ER_IRQHandler(void);                      /* it has 2 events. */
#endif /* !defined (STM32F745) */
void DMA2D_IRQHandler(void);                        /* it has 6 events. */
void SAI2_IRQHandler(void);                         /* it has 7 events. */
void QUADSPI_IRQHandler(void);                      /* it has 5 events. */
void LPTIM1_IRQHandler(void);                       /* it has 6 events. */
void CEC_IRQHandler(void);                          /* it has 13 events. */
void I2C4_EV_IRQHandler(void);                      /* it has 6 events. */
void I2C4_ER_IRQHandler(void);                      /* it has 7 events. */
void SPDIF_RX_IRQHandler(void);                     /* it has 9 events. */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INC_INTERRUPTS_HPP_ */

/*
 * interrupts.cpp
 *
 *  Created on: 2020. 12. 16.
 *      Author: bluel
 */

#include "interrupts.hpp"

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

void WWDG_IRQHandler(void) {

    CallbackHandler handler = CPU.getHandler(CPU.IRQ_WWDG_EVT_EARLY_WAKEUP);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(CPU.IRQ_WWDG_EVT_EARLY_WAKEUP);
}

void PVD_IRQHandler(void) {

    CallbackHandler handler = CPU.getHandler(CPU.IRQ_EXTI_EVT_PVD);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(CPU.IRQ_EXTI_EVT_PVD);
}

void TAMP_STAMP_IRQHandler(void) {

    CPUClass::EventInterrupt evt;
    CallbackHandler handler;

    evt = ((RTC->ISR & 0x00000800) && (RTC->CR & 0x00008000)) ? CPU.IRQ_RTC_EVT_TIMESTAMP :
          ((RTC->ISR & 0x00002000) && (RTC->TAMPCR & 0x00010000)) ? CPU.IRQ_RTC_EVT_TAMP1 :
          ((RTC->ISR & 0x00004000) && (RTC->TAMPCR & 0x00080000)) ? CPU.IRQ_RTC_EVT_TAMP2 :
          ((RTC->ISR & 0x00008000) && (RTC->TAMPCR & 0x00400000)) ? CPU.IRQ_RTC_EVT_TAMP3 :
                  CPU.IRQ_EVT_INDEX_ERROR;

    handler = CPU.getHandler(evt);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(evt);
}

void RTC_WKUP_IRQHandler(void) {

    CallbackHandler handler = CPU.getHandler(CPU.IRQ_RTC_EVT_WAKEUP);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(CPU.IRQ_RTC_EVT_WAKEUP);
}

void FLASH_IRQHandler(void) {

    CPUClass::EventInterrupt evt;
    CallbackHandler handler;

    evt = ((FLASH->SR & 0x00000001) && (FLASH->CR & 0x01000000))? CPU.IRQ_FLASH_EVT_EOP :
          ((FLASH->SR & 0x00000010) && (FLASH->CR & 0x02000000)) ? CPU.IRQ_FLASH_EVT_WRITE_PROTECTION_ERR :
          ((FLASH->SR & 0x00000020) && (FLASH->CR & 0x02000000)) ? CPU.IRQ_FLASH_EVT_ALIGNMENT_ERR :
          ((FLASH->SR & 0x00000040) && (FLASH->CR & 0x02000000)) ? CPU.IRQ_FLASH_EVT_PARALLEISM_ERR :
          ((FLASH->SR & 0x00000080) && (FLASH->CR & 0x02000000)) ? CPU.IRQ_FLASH_EVT_SEQUENCE_ERR :
                  CPU.IRQ_EVT_INDEX_ERROR;

    handler = CPU.getHandler(evt);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(evt);
}

void RCC_IRQHandler(void) {

    CPUClass::EventInterrupt evt;
    CallbackHandler handler;

    evt = ((RCC->CIR & 0x00000001) && (RCC->CIR & 0x00000100)) ? CPU.IRQ_RCC_EVT_LSI_READY :
          ((RCC->CIR & 0x00000002) && (RCC->CIR & 0x00000200)) ? CPU.IRQ_RCC_EVT_LSE_READY :
          ((RCC->CIR & 0x00000004) && (RCC->CIR & 0x00000400)) ? CPU.IRQ_RCC_EVT_HSI_READY :
          ((RCC->CIR & 0x00000008) && (RCC->CIR & 0x00000800)) ? CPU.IRQ_RCC_EVT_HSE_READY :
          ((RCC->CIR & 0x00000010) && (RCC->CIR & 0x00001000)) ? CPU.IRQ_RCC_EVT_PLL_READY :
          ((RCC->CIR & 0x00000020) && (RCC->CIR & 0x00002000)) ? CPU.IRQ_RCC_EVT_PLLI2S_READY :
          ((RCC->CIR & 0x00000040) && (RCC->CIR & 0x00004000)) ? CPU.IRQ_RCC_EVT_PLLSAI_READY :
          ((RCC->CIR & 0x00000080) && (RCC->CR & 0x00080000)) ? CPU.IRQ_RCC_EVT_CSS :
                  CPU.IRQ_EVT_INDEX_ERROR;

    handler = CPU.getHandler(evt);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(evt);
}

void EXTI0_IRQHandler(void) {

    CallbackHandler handler = CPU.getHandler(CPU.IRQ_EXTI_EVT_0);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(CPU.IRQ_EXTI_EVT_0);
}

void EXTI1_IRQHandler(void) {

    CallbackHandler handler = CPU.getHandler(CPU.IRQ_EXTI_EVT_1);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(CPU.IRQ_EXTI_EVT_1);
}

void EXTI2_IRQHandler(void) {

    CallbackHandler handler = CPU.getHandler(CPU.IRQ_EXTI_EVT_2);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(CPU.IRQ_EXTI_EVT_2);
}

void EXTI3_IRQHandler(void) {

    CallbackHandler handler = CPU.getHandler(CPU.IRQ_EXTI_EVT_3);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(CPU.IRQ_EXTI_EVT_3);
}

void EXTI4_IRQHandler(void) {

    CallbackHandler handler = CPU.getHandler(CPU.IRQ_EXTI_EVT_4);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(CPU.IRQ_EXTI_EVT_4);
}

void DMA1_Stream0_IRQHandler(void) {

    CPUClass::EventInterrupt evt;
    CallbackHandler handler;

    evt = ((DMA1->LISR & 0x00000001) && (DMA1_Stream0->FCR & 0x00000080)) ? CPU.IRQ_DMA1_STREAM1_EVT_FIFO_ERR :
          ((DMA1->LISR & 0x00000004) && (DMA1_Stream0->CR & 0x0000002)) ? CPU.IRQ_DMA1_STREAM1_EVT_DIRECT_MODE_ERR :
          ((DMA1->LISR & 0x00000008) && (DMA1_Stream0->CR & 0x0000004)) ? CPU.IRQ_DMA1_STREAM1_EVT_XSFER_ERR :
          ((DMA1->LISR & 0x00000010) && (DMA1_Stream0->CR & 0x0000008)) ? CPU.IRQ_DMA1_STREAM1_EVT_HALF_XSFER :
          ((DMA1->LISR & 0x00000020) && (DMA1_Stream0->CR & 0x0000010)) ? CPU.IRQ_DMA1_STREAM1_EVT_XSFER_COMPLETE :
                  CPU.IRQ_EVT_INDEX_ERROR;

    handler = CPU.getHandler(evt);

    if(handler == NULL) {

        assert_failed("Attempted to access a NULL pointer.", __LINE__);
    }

    handler();

    CPU.clearEventTrigger(evt);
}
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



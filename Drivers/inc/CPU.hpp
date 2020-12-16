#ifndef INC_CPU_HPP_
#define INC_CPU_HPP_

#include "stm32f74x.h"


typedef void (*CallbackHandler)(void);

class CPUClass {
private:
	CallbackHandler coreHandlers[9];
	CallbackHandler EventCallbacks[601];
public:
	enum CoreInterrupt {
		IRQ_NMI                                             = 0,
		IRQ_HardFault                                       = 1,
		IRQ_MemManage                                       = 2,
		IRQ_BusFault                                        = 3,
		IRQ_UsageFault                                      = 4,
		IRQ_SVCall                                          = 5,
		IRQ_DebugMon                                        = 6,
		IRQ_PendSV                                          = 7,
		IRQ_SysTick                                         = 8
	};

	enum EventInterrupt {
		IRQ_EVT_INDEX_ERROR                                 = 65535,
		IRQ_WWDG_EVT_EARLY_WAKEUP                           = 0,
		IRQ_EXTI_EVT_PVD                                    = 1,
		IRQ_RTC_EVT_TAMP1                                   = 2,
		IRQ_RTC_EVT_TAMP2                                   = 3,
		IRQ_RTC_EVT_TAMP3                                   = 4,
		IRQ_RTC_EVT_TIMESTAMP                               = 5,
		IRQ_RTC_EVT_WAKEUP                                  = 6,
		IRQ_FLASH_EVT_EOP                                   = 7,
		IRQ_FLASH_EVT_WRITE_PROTECTION_ERR                  = 8,
		IRQ_FLASH_EVT_ALIGNMENT_ERR                         = 9,
		IRQ_FLASH_EVT_PARALLEISM_ERR                        = 10,
		IRQ_FLASH_EVT_SEQUENCE_ERR                          = 11,
		IRQ_RCC_EVT_LSI_READY                               = 12,
		IRQ_RCC_EVT_LSE_READY                               = 13,
		IRQ_RCC_EVT_HSI_READY                               = 14,
		IRQ_RCC_EVT_HSE_READY                               = 15,
		IRQ_RCC_EVT_PLL_READY                               = 16,
		IRQ_RCC_EVT_PLLI2S_READY                            = 17,
		IRQ_RCC_EVT_PLLSAI_READY                            = 18,
		IRQ_RCC_EVT_CSS                                     = 19,
		IRQ_EXTI_EVT_0                                      = 20,
		IRQ_EXTI_EVT_1                                      = 21,
		IRQ_EXTI_EVT_2                                      = 22,
		IRQ_EXTI_EVT_3                                      = 23,
		IRQ_EXTI_EVT_4                                      = 24,
	};
	CPUClass();
	void enableIRQ(enum CoreInterrupt irq, void (*evt)(void));
	void disableIRQ(enum CoreInterrupt irq);
	void enableIRQ(enum EventInterrupt irq, void (*evt)(void));
	void disableIRQ(enum EventInterrupt irq);

	CallbackHandler getHandler(enum CoreInterrupt irq);
	CallbackHandler getHandler(enum EventInterrupt irq);
	void clearEventTrigger(enum EventInterrupt irq);
};

#ifdef __cplusplus
extern "C" {
#endif /* cplusplus */
void assert_failed(const char* file, uint32_t line);

#ifdef __cplusplus
}
#endif /* __cplusplus */

extern CPUClass CPU;

#endif /* INC_CPU_HPP_ */

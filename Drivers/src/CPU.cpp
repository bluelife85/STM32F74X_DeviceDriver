
#include "CPU.hpp"

#ifdef USE_OSC
#define XTAL_VALUE (HSE_VALUE / 1000000u)
#else
#define XTAL_VALUE (HSI_VALUE / 1000000u)
#endif /* USE_OSC */

CPU::CPU(void) {

	SCB_EnableICache();
	SCB_EnableDCache();


}

void assert_failed(uint8_t* file, uint32_t line) {

    while(1) {}
}


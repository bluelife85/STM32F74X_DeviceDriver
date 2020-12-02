#ifndef INC_CPU_HPP_
#define INC_CPU_HPP_

#include "stm32f74x.h"

class CPU {
private:
public:
	CPU();
};

#ifdef __cplusplus
extern "C" {
#endif /* cplusplus */
void assert_failed(uint8_t* file, uint32_t line);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INC_CPU_HPP_ */

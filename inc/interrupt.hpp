/*
 * systick.hpp
 *
 *  Created on: 2019/03/31
 *      Author: User
 */

#ifndef MYHEADERS_INTERRUPT_HPP_
#define MYHEADERS_INTERRUPT_HPP_

#include <functional>
#include <vector>
#include <map>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

namespace systick
{
	void init(const uint32_t SysTickFrequency = 1000, const uint32_t IRQ_priority = 0);
	void additionCallFunction(std::function<void(void)>&& addFunc);
}

namespace EXTI0Intrrupt
{
	void init(const uint8_t IRQ_priority);
	void additionCallFunction(const std::function<void(void)>&& addFunc);
}

namespace EXTI1Intrrupt
{
	void init(const uint8_t IRQ_priority);
	void additionCallFunction(const std::function<void(void)>&& addFunc);
}

namespace CAN_intrrupt
{
	void init(const uint8_t IRQ_priority);
	void additionCallFunction(const std::function<void(const CanRxMsg&)>&& addFunc);
}
#endif /* MYHEADERS_INTERRUPT_HPP_ */

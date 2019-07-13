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

class SysTick_Interrupt
{
private:
	static std::map<SysTick_Interrupt* const,const std::function<void(void)>> callFunctions_;
public:
	SysTick_Interrupt() = delete;
	SysTick_Interrupt(const std::function<void(void)>&& addFunc)
	{
		callFunctions_.insert(std::make_pair(this, addFunc));
	}

	static void update()
	{
		for(auto i : callFunctions_)i.second();
	}

	virtual ~SysTick_Interrupt() { SysTick_Interrupt::callFunctions_.erase(this); }
};

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

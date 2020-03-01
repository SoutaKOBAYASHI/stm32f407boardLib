/*
 * systick.hpp
 *
 *  Created on: 2019/03/31
 *      Author: User
 */

#ifndef SYSTICK_HPP_
#define SYSTICK_HPP_

#include <functional>
#include <vector>
#include <map>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

class SysTick_Interrupt
{
private:
	static std::map<SysTick_Interrupt* const,const std::function<void(void)>> callFunctions_;
	static uint32_t now_freq_;
public:
	SysTick_Interrupt() = delete;
	SysTick_Interrupt(const std::function<void(void)>&& addFunc);

	static void init(const uint32_t frequency, const uint32_t priority)
	{
		RCC_ClocksTypeDef RCC_Clocks;
		RCC_GetClocksFreq(&RCC_Clocks);
		SysTick_Config(RCC_Clocks.HCLK_Frequency / frequency);
		NVIC_SetPriority(SysTick_IRQn, priority);
		now_freq_ = frequency;
	}

	static void update(){ for(auto i : callFunctions_)i.second(); }

	static inline uint32_t readFreq(){ return now_freq_; }

	virtual ~SysTick_Interrupt() { SysTick_Interrupt::callFunctions_.erase(this); }
};
#endif /* MYHEADERS_INTERRUPT_HPP_ */

/*
 * intrrupt.cpp
 *
 *  Created on: 2019/04/06
 *      Author: User
 */

#include <interrupt.hpp>

namespace systick
{
	static std::vector<std::function<void(void)>> sysTick_callsFunctions;

	void init(const uint32_t SysTickFrequency, const uint32_t IRQ_priority)
	{
		RCC_ClocksTypeDef RCC_Clocks;
		RCC_GetClocksFreq(&RCC_Clocks);
		SysTick_Config(RCC_Clocks.HCLK_Frequency / SysTickFrequency);
		NVIC_SetPriority(SysTick_IRQn, 1);
	}

	void additionCallFunction(std::function<void(void)>&& addFunc){ sysTick_callsFunctions.push_back(addFunc); }

	extern "C"
	{
		void SysTick_Handler(){ for(auto i : sysTick_callsFunctions)i(); }
	}
}

namespace EXTI0Intrrupt
{
	static std::vector<std::function<void(void)>> callsFunctions;

	void init(const uint8_t IRQ_priority)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource0);

		EXTI_InitTypeDef EXTI_InitStruct;
		EXTI_InitStruct.EXTI_Line		= EXTI_Line0;
		EXTI_InitStruct.EXTI_Mode		= EXTI_Mode_Interrupt;
		EXTI_InitStruct.EXTI_Trigger	= EXTI_Trigger_Rising_Falling;
		EXTI_InitStruct.EXTI_LineCmd	= ENABLE;
		EXTI_Init(&EXTI_InitStruct);


		NVIC_InitTypeDef NVIC_initStruct;
		NVIC_initStruct.NVIC_IRQChannel	= EXTI0_IRQn;
		NVIC_initStruct.NVIC_IRQChannelPreemptionPriority = IRQ_priority;
		NVIC_initStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_initStruct);

	}

	void additionCallFunction(const std::function<void(void)>&& addFunc){ callsFunctions.push_back(addFunc); }

	extern "C"
	{
		void EXTI0_IRQHandler()
		{
			for(auto i : callsFunctions)i();
			EXTI_ClearFlag(EXTI_Line0);
		}
	}
}

namespace EXTI1Intrrupt
{
	static std::vector<std::function<void(void)>> callsFunctions;

	void init(const uint8_t IRQ_priority)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource1);

		EXTI_InitTypeDef EXTI_InitStruct;
		EXTI_InitStruct.EXTI_Line		= EXTI_Line1;
		EXTI_InitStruct.EXTI_Mode		= EXTI_Mode_Interrupt;
		EXTI_InitStruct.EXTI_Trigger	= EXTI_Trigger_Rising_Falling;
		EXTI_InitStruct.EXTI_LineCmd	= ENABLE;
		EXTI_Init(&EXTI_InitStruct);


		NVIC_InitTypeDef NVIC_initStruct;
		NVIC_initStruct.NVIC_IRQChannel	= EXTI1_IRQn;
		NVIC_initStruct.NVIC_IRQChannelPreemptionPriority = IRQ_priority;
		NVIC_initStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_initStruct);

	}

	void additionCallFunction(const std::function<void(void)>&& addFunc){ callsFunctions.push_back(addFunc); }

	extern "C"
	{
		void EXTI1_IRQHandler()
		{
			for(auto i : callsFunctions)i();
			EXTI_ClearFlag(EXTI_Line1);
		}
	}
}

namespace CAN_intrrupt
{
	static std::vector<std::function<void(const CanRxMsg&)>> callsFunctions;

	void init(const uint8_t IRQ_priority)
	{
		NVIC_InitTypeDef NVIC_initStruct;
		NVIC_initStruct.NVIC_IRQChannel	= CAN1_RX0_IRQn;
		NVIC_initStruct.NVIC_IRQChannelPreemptionPriority = IRQ_priority;
		NVIC_initStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_initStruct);
	}

	void additionCallFunction(const std::function<void(const CanRxMsg&)>&& addFunc){ callsFunctions.push_back(addFunc); }

	extern "C"
	{
		void CAN1_RX0_IRQHandler()
		{
			CanRxMsg CanRxMsgStruct;
			CAN_Receive(CAN1, CAN_FIFO0, &CanRxMsgStruct);
			for(auto i : callsFunctions)i(CanRxMsgStruct);
		}
	}
}

/*
 * electric_valve.h
 *
 *  Created on: 2019/02/28
 *      Author: User
 */

#ifndef MYHEADERS_ELECTRIC_VALVE_HPP_
#define MYHEADERS_ELECTRIC_VALVE_HPP_

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include <type_traits>
#include <utility>

enum class EvName : uint16_t
{
	EV0		= (0x0001 << 0),
	EV1		= (0x0001 << 1),
	EV2		= (0x0001 << 2),
	EV3		= (0x0001 << 3),
	EV4		= (0x0001 << 4),
	EV5		= (0x0001 << 5),
	EV6		= (0x0001 << 6),
	EV7		= (0x0001 << 7),
	EV8		= (0x0001 << 8),
	EV9		= (0x0001 << 9),
	EV10	= (0x0001 << 10),
	EV11	= (0x0001 << 11),
	EV12	= (0x0001 << 12),
	EV13	= (0x0001 << 13),
	EV14	= (0x0001 << 14),
	EV15	= (0x0001 << 15),
};

enum class EvState { Set, Reset };

template<EvName useEvName>
class EV
{
public:
	EV()
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

		constexpr GPIO_InitTypeDef GPIO_InitStruct
		{
			useEvName,			//GPIO_Pin
			GPIO_Mode_OUT,		//GPIO_Mode
			GPIO_Speed_100MHz,	//GPIO_Speed
			GPIO_OType_PP,		//GPIO_OType
			GPIO_PuPd_NOPULL	//GPIO_PuPd
		};
		GPIO_Init_reference(usePortName, GPIO_InitStruct);
	}

	inline void setNewState(EvState newState)
	{
		if(newState == EvState::Set)GPIO_SetBits(usePortName, (uint16_t)useEvName);
		else GPIO_ResetBits(usePortName, (uint16_t)useEvName);
	}

	virtual ~EV();

protected:
	static GPIO_TypeDef* const usePortName = GPIOE;

	static void GPIO_Init_reference(GPIO_TypeDef* const GPIOx, const GPIO_InitTypeDef& GPIO_InitStruct)
	{
	  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;

	  /* ------------------------- Configure the port pins ---------------- */
	  /*-- GPIO Mode Configuration --*/
	  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
	  {
		pos = ((uint32_t)0x01) << pinpos;
		/* Get the port pins position */
		currentpin = (GPIO_InitStruct.GPIO_Pin) & pos;

		if (currentpin == pos)
		{
		  GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
		  GPIOx->MODER |= (((uint32_t)GPIO_InitStruct.GPIO_Mode) << (pinpos * 2));

		  if ((GPIO_InitStruct.GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct.GPIO_Mode == GPIO_Mode_AF))
		  {
			/* Speed mode configuration */
			GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
			GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct.GPIO_Speed) << (pinpos * 2));

			/* Output mode configuration*/
			GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos)) ;
			GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct.GPIO_OType) << ((uint16_t)pinpos));
		  }

		  /* Pull-up Pull down resistor configuration*/
		  GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
		  GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct.GPIO_PuPd) << (pinpos * 2));
		}
	  }
	}
};

#endif /* MYHEADERS_ELECTRIC_VALVE_HPP_ */

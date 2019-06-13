/*
 * rotary_encoder.h
 *
 *  Created on: 2019/03/01
 *      Author: User
 */

#ifndef MYHEADERS_ROTARY_ENCODER_HPP_
#define MYHEADERS_ROTARY_ENCODER_HPP_

#include <type_traits>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

enum class encoderName : uint8_t
{
	RotEnc1,
	RotEnc2,
	RotEnc3,
	RotEnc4,
	RotEnc5
};

template<encoderName useRotEnc, uint16_t setPeriod = UINT16_MAX>
class RotaryEncoder
{
private:

public:
	TIM_TypeDef* const useTimer;
	RotaryEncoder() : useTimer(getUseTimer_())
	{
		timerClockInit_();
		configEncoderInterfaceMode_();
		configEncoderPins_();
	}

	template<typename T>
	std::enable_if_t<std::is_unsigned<T>::value, T> readCount() const
	{
		return (T)useTimer->CNT;
	}

	template<typename T>
	std::enable_if_t<std::is_signed_v<T> && !std::is_floating_point_v<T>, T> readCount() const
	{
		const uint32_t countValue = (uint32_t)useTimer->CNT;
		std::make_unsigned_t<T> returnValue = 0;
	    if(countValue > ((uint32_t)(useTimer->ARR/2)))
		{
	    	/*Complement representation*/
			returnValue = returnValue - 1;	//returnValue is 0x~FFFF.
			returnValue = returnValue - (std::make_unsigned_t<T>)useTimer->ARR;
			returnValue = returnValue + (std::make_unsigned_t<T>)countValue;
		}
		else
		{
			returnValue = (std::make_unsigned_t<T>)countValue;
		}
		return (T)returnValue;
	}

	template<typename T>
	inline std::enable_if_t<std::is_floating_point<T>::value, T> readCount() const
		{ return (double)readCount<int32_t>(); }

	inline void clearCount(){ useTimer->CNT = 0; }
	inline void setCount(uint32_t setValue){ useTimer->CNT = setValue; }

	virtual ~RotaryEncoder(){}

protected:
	inline void timerClockInit_()
	{
		constexpr uint32_t RCC_Periph =
				useRotEnc == encoderName::RotEnc1 ? RCC_APB2Periph_TIM1 :
				useRotEnc == encoderName::RotEnc2 ? RCC_APB1Periph_TIM3 :
				useRotEnc == encoderName::RotEnc3 ? RCC_APB1Periph_TIM4 :
				useRotEnc == encoderName::RotEnc4 ? RCC_APB1Periph_TIM5 : RCC_APB2Periph_TIM8;

		RCC_APB1PeriphClockCmd(RCC_Periph, ENABLE);
	}

	inline void configEncoderInterfaceMode_()
	{
		TIM_EncoderInterfaceConfig(useTimer, TIM_EncoderMode_TI12 , TIM_ICPolarity_Rising , TIM_ICPolarity_Rising);
		TIM_Cmd(useTimer, ENABLE);

		TIM_SetAutoreload(useTimer, (uint32_t)UINT16_MAX);

		TIM_SetCounter(useTimer, 0);
	}

	std::enable_if_t<useRotEnc == encoderName::RotEnc1, void> configEncoderPins_()
	{

	}
	std::enable_if_t<useRotEnc == encoderName::RotEnc2, void> configEncoderPins_()
	{

	}
	std::enable_if_t<useRotEnc == encoderName::RotEnc3, void> configEncoderPins_()
	{

	}
	std::enable_if_t<useRotEnc == encoderName::RotEnc4, void> configEncoderPins_()
	{

	}
	std::enable_if_t<useRotEnc == encoderName::RotEnc5, void> configEncoderPins_()
	{

	}

	constexpr TIM_TypeDef* getUseTimer_()
	{
		return	useRotEnc == encoderName::RotEnc1 ? TIM1 :
				useRotEnc == encoderName::RotEnc2 ? TIM3 :
				useRotEnc == encoderName::RotEnc3 ? TIM4 :
				useRotEnc == encoderName::RotEnc4 ? TIM5 : TIM8;
	}
};



#endif /* MYHEADERS_ROTARY_ENCODER_HPP_ */

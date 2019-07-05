/*
 * uart.hpp
 *
 *  Created on: 2019/03/29
 *      Author: User
 */

#ifndef MYHEADERS_UART_HPP_
#define MYHEADERS_UART_HPP_

#include <vector>
#include <array>
#include <string>
#include <functional>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

enum class uartName{uart1, uart2, uart3};

template<uartName useUartName, uint32_t setBaudrate = 9600>
class UART
{
public:
	UART()
	{
		uartInit_();
		pinsInit_();
	}

	/*transmit a byte.*/
	void TransmitData(const uint8_t sendByte)
	{
		while(!USART_GetFlagStatus(useUartName_(), USART_FLAG_TXE));
		USART_SendData(useUartName_(), (uint16_t)sendByte);
	}

	/*overloaded functions of transmitting.*/
	inline void TransmitData(const char sendByte) { TransmitData((uint8_t)sendByte); }

	inline void TransmitData(const uint8_t* pSendData, const size_t size) { for (size_t i = 0; i < size; i++)TransmitData(*(pSendData + i)); }
	inline void TransmitData(const char* pSendData, const size_t size) { for (size_t i = 0; i < size; i++)TransmitData(*(pSendData + i)); }

	inline void TransmitData(const std::string & sendString) { TransmitData((uint8_t*)sendString.c_str(), sendString.size()); }
	template<size_t S>
	inline void TransmitData(const std::array<uint8_t, S> & sendDataArray) { for (auto i : sendDataArray)TransmitData((uint8_t)i); }
	template<size_t S>
	inline void TransmitData(const std::array<char, S> & sendDataArray) { for (auto i : sendDataArray)TransmitData((uint8_t)i); }
	inline void TransmitData(const std::vector<uint8_t> & sendVector) { for (auto i : sendVector)TransmitData((uint8_t)i); }

private:
	void pinsInit_()
	{

	}
	void uartInit_()
	{
		if(useUartName_() == USART1)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		}
		else if (useUartName_() == USART2)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		}
		else
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
		}

		USART_InitTypeDef USART_InitStruct;
		USART_StructInit(&USART_InitStruct);
		USART_InitStruct.USART_Mode		= USART_Mode_Rx | USART_Mode_Tx;
		USART_InitStruct.USART_BaudRate	= setBaudrate;
		USART_Init(useUartName_(), &USART_InitStruct);

		USART_Cmd(useUartName_(), ENABLE);

		USART_ITConfig(useUartName_(), USART_IT_RXNE, ENABLE);

		NVIC_InitTypeDef NVIC_InitStruct;
		NVIC_InitStruct.NVIC_IRQChannel 					= 	useUartName == uartName::uart1 ? USART1_IRQn :
																useUartName == uartName::uart2 ? USART3_IRQn : UART4_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0x00;
		NVIC_InitStruct.NVIC_IRQChannelCmd					= ENABLE;
		NVIC_Init(&NVIC_InitStruct);
	}
	constexpr USART_TypeDef* useUartName_()
	{
		return	useUartName == uartName::uart1 ? USART1 :
				useUartName == uartName::uart2 ? USART3 : UART4;
	}
};

#endif /* MYHEADERS_UART_HPP_ */

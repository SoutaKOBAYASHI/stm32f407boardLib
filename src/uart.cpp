/*
 * uart.cpp
 *
 *  Created on: 2019/03/29
 *      Author: User
 */
#include "uart.hpp"

std::function<void(const std::string&)> uartSendString = [](const std::string&){};

void UART::pinsInit_usart1()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
}
void UART::pinsInit_usart2()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
}

void UART::uartInit_(const uint32_t setBaudrate)
{
	if(useUartName_ == USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	}
	else
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	}

	USART_InitTypeDef USART_InitStruct;
	USART_StructInit(&USART_InitStruct);
	USART_InitStruct.USART_Mode		= USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_BaudRate	= defaultBaudrate_;
	USART_Init(useUartName_, &USART_InitStruct);

	USART_Cmd(useUartName_, ENABLE);

	USART_ITConfig(useUartName_, USART_IT_RXNE, ENABLE);

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel 					= useUartName_ == USART1 ? USART1_IRQn : USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void UART::TransmitData(uint8_t sendByte)
{
	while(!USART_GetFlagStatus(useUartName_, USART_FLAG_TXE));
	USART_SendData(useUartName_, (uint16_t)sendByte);
}


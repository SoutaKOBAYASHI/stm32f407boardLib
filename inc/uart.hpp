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

class UART
{
public:
	UART() = delete;

	enum class name{uart1, uart2};
	UART(const name useUartName, const uint32_t setBaudrate = defaultBaudrate_) : useUartName_(useUartName == name::uart1 ? USART1 : USART2)
	{
		uartInit_(setBaudrate);
		if(useUartName_ == USART1)pinsInit_usart1();
		else pinsInit_usart2();
	}

	/*transmit a byte.*/
	void TransmitData(const uint8_t sendByte);

	/*overloaded functions of transmitting.*/
	inline void TransmitData(const char sendByte){ TransmitData((uint8_t)sendByte); }

	inline void TransmitData(const uint8_t* pSendData, const size_t size){ for(size_t i = 0;i < size;i++)TransmitData(*(pSendData+i)); }
	inline void TransmitData(const char* pSendData, const size_t size){ for(size_t i = 0;i < size;i++)TransmitData(*(pSendData+i)); }

	inline void TransmitData(const std::string& sendString) { TransmitData((uint8_t*)sendString.c_str(), sendString.size()); }
	template<size_t S>
	inline void TransmitData(const std::array<uint8_t,S>& sendDataArray){ for(auto i : sendDataArray)TransmitData(sendDataArray.at(i)); }
	template<size_t S>
	inline void TransmitData(const std::array<char,S>& sendDataArray){ for(auto i : sendDataArray)TransmitData((uint8_t)i); }
	inline void TransmitData(const std::vector<uint8_t>& sendVector){ for(auto i : sendVector)TransmitData(sendVector.at(i)); }

private:
	void pinsInit_usart1();
	void pinsInit_usart2();
	void uartInit_(const uint32_t setBaudrate);
	static constexpr uint32_t defaultBaudrate_ = 9600;
	USART_TypeDef* const useUartName_;
};

extern std::function<void(const std::string&)> uartSendString;

#endif /* MYHEADERS_UART_HPP_ */

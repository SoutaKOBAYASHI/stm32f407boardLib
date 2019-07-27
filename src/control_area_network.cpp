/*
 * control_area_network.cpp
 *
 *  Created on: 2019/07/27
 *      Author: SotaKobayashi
 */

#include "control_area_network.hpp"

std::map<CAN_Interrupt* const,const std::function<void(const CanRxMsg&)>> CAN_Interrupt::can_call_functions_;

extern "C"
{
	void CAN1_RX0_IRQHandler()
	{
		CAN_Interrupt::callback();
	}
}

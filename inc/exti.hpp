/*
 * exti.hpp
 *
 *  Created on: 2019/08/03
 *      Author: SotaKobayashi
 */

#ifndef EXTI_HPP_
#define EXTI_HPP_

enum class ExtiLineName : uint16_t
{
	LINE0	= (0x01 << 0),
	LINE1	= (0x01 << 1),
	LINE2	= (0x01 << 2),
	LINE3	= (0x01 << 3),
	LINE4	= (0x01 << 4),
	LINE5	= (0x01 << 5),
	LINE6	= (0x01 << 6),
	LINE7	= (0x01 << 7),
	LINE8	= (0x01 << 8),
	LINE9	= (0x01 << 9),
	LINE10	= (0x01 << 10),
	LINE11	= (0x01 << 11),
	LINE12	= (0x01 << 12),
	LINE13	= (0x01 << 13),
	LINE14	= (0x01 << 14),
	LINE15	= (0x01 << 15)
};

template<ExtiLineName EXTI_LINE_NAME>
class ExtiInterrupt
{

};



#endif /* EXTI_HPP_ */

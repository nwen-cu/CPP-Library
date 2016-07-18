/*
 * Clock.h
 *
 *  Created on: 2016Äê7ÔÂ11ÈÕ
 *      Author: Wennx-Desktop
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include<msp430.h>
#include<IO.h>

class Clock
{
public:
	static void DCO_FreqSelect(int mode);
	static void DCO_RangeSelect(int mode);

	static void Modulator(int mode);
	static void DisModulator(int mode);

	static void FLL_Div(int mode);
	static void FLL_N(int mode);
	static void FLL_Ref(int mode);
	static void FLL_RefDiv(int mode);

	static void ACLK_Ref(int mode)
	{
		GPIO::Ports(5).FuncSelect(4, 1);
		GPIO::Ports(5).FuncSelect(5, 1);
		UCSCTL4 |= 0xF8FF;
	}
	static void ACLK_Div_Out(int mode);
	static void ACLK_Div(int mode);

	static void SMCLK_Ref(int mode);
	static void SMCLK_Div(int mode);

	static void MCLK_Ref(int mode);
	static void MCLK_Div(int mode);
};



#endif /* CLOCK_H_ */

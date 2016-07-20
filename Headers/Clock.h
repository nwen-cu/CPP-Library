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

enum RefCLK {XT1CLK, XT2CLK, REFOCLK, VLOCLK, DCOCLK, DCOCLKDIV};

class Clock
{
public:
	static void DCO_FreqSelect(int mode);
	static void DCO_RangeSelect(int mode);

	static void Modulator(int mode);
	static void DisModulator(int mode);

	static void FLL_Div(int division)
	{
		switch(division)
		{
		case 1:
			UCSCTL2_H &= 0x8F;
			break;
		case 2:
			UCSCTL2_H &= 0x9F;
			UCSCTL2_H |= 0x10;
			break;
		case 4:
			UCSCTL2_H &= 0xAF;
			UCSCTL2_H |= 0x20;
			break;
		case 8:
			UCSCTL2_H &= 0xBF;
			UCSCTL2_H |= 0x30;
			break;
		case 16:
			UCSCTL2_H &= 0xCF;
			UCSCTL2_H |= 0x40;
			break;
		case 32:
			UCSCTL2_H &= 0xDF;
			UCSCTL2_H |= 0x50;
			break;
		}
	}
	static void FLL_N(int n)
	{
		int i;
		for(i = 9; i >= 0; i--)
		{
			if((n & (1 << i)) >> i)
			{
				UCSCTL2 |= (1 << i);
			}
			else
			{
				UCSCTL2 &= ~(1 << i);
			}
		}
	}
	static void FLL_Ref(RefCLK clk)
	{
		switch(clk)
		{
		case XT1CLK:
			UCSCTL3_L &= 0x8F;
			break;
		case XT2CLK:
			UCSCTL3_L |= 0x50;
			UCSCTL3_L &= 0xDF;
			break;
		case REFOCLK:
			UCSCTL3_L |= 0x20;
			UCSCTL3_L &= 0xAF;
			break;
		}
	}
	static void FLL_RefDiv(int division)
	{
		switch(division)
		{
		case 1:
			UCSCTL3_L &= 0xF8;
			break;
		case 2:
			UCSCTL3_L |= 0x01;
			UCSCTL3_L &= 0xF9;
			break;
		case 4:
			UCSCTL3_L |= 0x02;
			UCSCTL3_L &= 0xFA;
			break;
		case 8:
			UCSCTL3_L |= 0x03;
			UCSCTL3_L &= 0xFB;
			break;
		case 12:
			UCSCTL3_L |= 0x04;
			UCSCTL3_L &= 0xFC;
			break;
		case 16:
			UCSCTL3_L |= 0x05;
			UCSCTL3_L &= 0xFD;
			break;
		}
	}

	static void ACLK_Ref(RefCLK clk)
	{
		switch(clk)
		{
		case XT1CLK:
			GPIO::Ports(5).FuncSelect(4, 1);
			GPIO::Ports(5).FuncSelect(5, 1);
			UCSCTL4_H &= 0xF8;
			break;
		case XT2CLK:
			GPIO::Ports(5).FuncSelect(2, 1);
			GPIO::Ports(5).FuncSelect(3, 1);
			UCSCTL4_H |= 0x05;
			UCSCTL4_H &= 0xFD;
			break;
		case REFOCLK:
			UCSCTL4_H |= 0x02;
			UCSCTL4_H &= 0xFA;
			break;
		case VLOCLK:
			UCSCTL4_H |= 0x01;
			UCSCTL4_H &= 0xF9;
			break;
		case DCOCLK:
			UCSCTL4_H |= 0x03;
			UCSCTL4_H &= 0xFB;
			break;
		case DCOCLKDIV:
			UCSCTL4_H |= 0x04;
			UCSCTL4_H &= 0xFC;
			break;
		}
		GPIO::Ports(5).FuncSelect(4, 1);
		GPIO::Ports(5).FuncSelect(5, 1);
		UCSCTL4 |= 0xF8FF;
	}
	static void ACLK_Output_Div(int division)
	{
		switch(division)
		{
		case 1:
			UCSCTL5_H &= 0x8F;
			break;
		case 2:
			UCSCTL5_H |= 0x10;
			UCSCTL5_H &= 0x9F;
			break;
		case 4:
			UCSCTL5_H |= 0x20;
			UCSCTL5_H &= 0xAF;
			break;
		case 8:
			UCSCTL5_H |= 0x30;
			UCSCTL5_H &= 0xBF;
			break;
		case 16:
			UCSCTL5_H |= 0x40;
			UCSCTL5_H &= 0xCF;
			break;
		case 32:
			UCSCTL5_H |= 0x50;
			UCSCTL5_H &= 0xDF;
			break;
		}
	}
	static void ACLK_Div(int division)
	{
		switch(division)
		{
		case 1:
			UCSCTL5_H &= 0xF8;
			break;
		case 2:
			UCSCTL5_H |= 0x01;
			UCSCTL5_H &= 0xF9;
			break;
		case 4:
			UCSCTL5_H |= 0x02;
			UCSCTL5_H &= 0xFA;
			break;
		case 8:
			UCSCTL5_H |= 0x03;
			UCSCTL5_H &= 0xFB;
			break;
		case 16:
			UCSCTL5_H |= 0x04;
			UCSCTL5_H &= 0xFC;
			break;
		case 32:
			UCSCTL5_H |= 0x05;
			UCSCTL5_H &= 0xFD;
			break;
		}
	}

	static void SMCLK_Ref(RefCLK clk)
	{
		switch(clk)
		{
		case XT1CLK:
			UCSCTL4_L &= 0x8F;
			break;
		case XT2CLK:
			UCSCTL4_L |= 0x50;
			UCSCTL4_L &= 0xDF;
			break;
		case REFOCLK:
			UCSCTL4_L |= 0x20;
			UCSCTL4_L &= 0xAF;
			break;
		case VLOCLK:
			UCSCTL4_L |= 0x10;
			UCSCTL4_L &= 0x9F;
			break;
		case DCOCLK:
			UCSCTL4_L |= 0x30;
			UCSCTL4_L &= 0xBF;
			break;
		case DCOCLKDIV:
			UCSCTL4_L |= 0x40;
			UCSCTL4_H &= 0xCF;
			break;
		}
	}
	static void SMCLK_Div(int division)
	{
		switch(division)
		{
		case 1:
			UCSCTL5_L &= 0x8F;
			break;
		case 2:
			UCSCTL5_L |= 0x10;
			UCSCTL5_L &= 0x9F;
			break;
		case 4:
			UCSCTL5_L |= 0x20;
			UCSCTL5_L &= 0xAF;
			break;
		case 8:
			UCSCTL5_L |= 0x30;
			UCSCTL5_L &= 0xBF;
			break;
		case 16:
			UCSCTL5_L |= 0x40;
			UCSCTL5_L &= 0xCF;
			break;
		case 32:
			UCSCTL5_L |= 0x50;
			UCSCTL5_L &= 0xDF;
			break;
		}
	}

	static void MCLK_Ref(RefCLK clk)
	{
		switch(clk)
		{
		case XT1CLK:
			UCSCTL4_L &= 0xF8;
			break;
		case XT2CLK:
			UCSCTL4_L |= 0x05;
			UCSCTL4_L &= 0xFD;
			break;
		case REFOCLK:
			UCSCTL4_L |= 0x02;
			UCSCTL4_L &= 0xFA;
			break;
		case VLOCLK:
			UCSCTL4_L |= 0x01;
			UCSCTL4_L &= 0xF9;
			break;
		case DCOCLK:
			UCSCTL4_L |= 0x03;
			UCSCTL4_L &= 0xFB;
			break;
		case DCOCLKDIV:
			UCSCTL4_L |= 0x04;
			UCSCTL4_L &= 0xFC;
			break;
		}
	}
	static void MCLK_Div(int division)
	{
		switch(division)
		{
		case 1:
			UCSCTL5_L &= 0xF8;
			break;
		case 2:
			UCSCTL5_L |= 0x01;
			UCSCTL5_L &= 0xF9;
			break;
		case 4:
			UCSCTL5_L |= 0x02;
			UCSCTL5_L &= 0xFA;
			break;
		case 8:
			UCSCTL5_L |= 0x03;
			UCSCTL5_L &= 0xFB;
			break;
		case 16:
			UCSCTL5_L |= 0x04;
			UCSCTL5_L &= 0xFC;
			break;
		case 32:
			UCSCTL5_L |= 0x05;
			UCSCTL5_L &= 0xFD;
			break;
		}
	}
};



#endif /* CLOCK_H_ */

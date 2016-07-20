/*
 * main.cpp
 *
 *  Created on: 2016Äê7ÔÂ9ÈÕ
 *      Author: Wennx-Desktop
 */

#include<msp430.h>
#include<IO.h>
#include<Interrupt.h>
#include<KeyMatrix.h>
//#include<Timer.h>
#include<LCD.h>
#include<Filter.h>
#include<Clock.h>




void main()
{
	void Int1(int);
	WDTCTL=WDTPW+WDTHOLD;
	GPIO::Port_Init();
	//Interrupt::GIntEnabled(0);
	//GPIO::Ports(1).ResEnabled(0, 1);
	//GPIO::Ports(1).Output(0, 1);
	//GPIO::Ports(1).ResEnabled(2, 1);
	//GPIO::Ports(1).Output(2, 0);  87
	//Interrupt::EnInterruptP(1, 2, 0, KeyMatrix::KeyPress);
	//GPIO::Ports(1).Output(0, 0);
	GPIO::Ports(3).DriveSelectB(1);
	GPIO::Ports(4).DriveSelectB(1);
	LCD::LCD_Init(3, 4, 0, 1, 2, 3);
	//LCD::LCD_Test();
	Clock::FLL_Ref(XT2CLK);
	Clock::FLL_Div(1);
	Clock::FLL_N(1);
	Clock::Modulator();
	Clock::DCO_FreqSelect(0);
	Clock::DCO_RangeSelect(3);
	Clock::ACLK_Ref(DCOCLK);
	GPIO::Ports(1).FuncSelect(0, 1);
	Filter::Filter_Init(6, 6, 7, 4, 1, 6, 5, 4);
	Filter::FilterMode(1, 0);
	Filter::FilterFreq(1, 50000);
	Filter::FilterQual(1, 90);
	/*for(;;)
	{
		GPIO::Ports(1).Output(0, 1);
		GPIO::Ports(1).Output(0, 0);
	}*/
	//Interrupt::GIntEnabled(1);
	//KeyMatrix::KeyMatrix_Init(4, 1, 0, 3, 2, 5);
	//(*Interrupt::f1[2])(0);
	//_BIS_SR(LPM3_bits + GIE);
	for(;;);
}

void Int1(int)
{
	if(GPIO::Ports(1).Output(0))
		GPIO::Ports(1).Output(0, 0);
	else
		GPIO::Ports(1).Output(0, 1);}

void KeyMatrix::KeyDefination(int r, int c)
{
	GPIO::Ports(3).OutputB(0);
	switch(r * 10 + c)
	{
	case 0:
		GPIO::Ports(3).Output(2, 1);
		GPIO::Ports(3).Output(0, 1);
		break;
	case 1:
		GPIO::Ports(3).Output(3, 1);
		GPIO::Ports(3).Output(0, 1);
		break;
	case 2:
		GPIO::Ports(3).Output(4, 1);
		GPIO::Ports(3).Output(0, 1);
		break;
	case 3:
		GPIO::Ports(3).Output(5, 1);
		GPIO::Ports(3).Output(0, 1);
		break;
	case 10:
		GPIO::Ports(3).Output(2, 1);
		GPIO::Ports(3).Output(1, 1);
		break;
	case 11:
		GPIO::Ports(3).Output(3, 1);
		GPIO::Ports(3).Output(1, 1);
		break;
	case 12:
		GPIO::Ports(3).Output(4, 1);
		GPIO::Ports(3).Output(1, 1);
		break;
	case 13:
		GPIO::Ports(3).Output(5, 1);
		GPIO::Ports(3).Output(1, 1);
		break;
	case 20:
		GPIO::Ports(3).Output(2, 1);
		GPIO::Ports(3).Output(6, 1);
		break;
	case 21:
		GPIO::Ports(3).Output(3, 1);
		GPIO::Ports(3).Output(6, 1);
		break;
	case 22:
		GPIO::Ports(3).Output(4, 1);
		GPIO::Ports(3).Output(6, 1);
		break;
	case 23:
		GPIO::Ports(3).Output(5, 1);
		GPIO::Ports(3).Output(6, 1);
		break;
	case 30:
		GPIO::Ports(3).Output(2, 1);
		GPIO::Ports(3).Output(7, 1);
		break;
	case 31:
		GPIO::Ports(3).Output(3, 1);
		GPIO::Ports(3).Output(7, 1);
		break;
	case 32:
		GPIO::Ports(3).Output(4, 1);
		GPIO::Ports(3).Output(7, 1);
		break;
	case 33:
		GPIO::Ports(3).Output(5, 1);
		GPIO::Ports(3).Output(7, 1);
		break;
	}
}

/*#pragma vector=PORT1_VECTOR
__interrupt void IntP1()
{
	GPIO::Ports(1).Output(0, 1);
}
*/


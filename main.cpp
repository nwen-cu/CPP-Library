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
#include<Timer.h>
#include<LCD.h>
#include<Filter.h>
#include<Clock.h>
#include<ADC.h>




void main()
{
	void Int1(int);
	WDTCTL=WDTPW+WDTHOLD;
	GPIO::Port_Init();
	char Output[16];
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
	KeyMatrix::KeyMatrix_Init(2, 1, 4, 7, 3, 6);
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
	Clock::SMCLK_Ref(XT1CLK);
	Timer::TimerA1_Init(ACLK);
	Timer::TimerA1_Output(10);
	GPIO::Ports(2).Direction(0, 1);
	GPIO::Ports(2).FuncSelect(0, 1);
	ADC::ADC_Init();
	/*for(;;)
	{
		GPIO::Ports(1).Output(0, 1);
		GPIO::Ports(1).Output(0, 0);
	}*/
	//Interrupt::GIntEnabled(1);

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
		LCD::WriteString("     Key 1      ", 1);
		break;
	case 1:
		LCD::WriteString("     Key 2      ", 1);
		break;
	case 2:
		LCD::WriteString("     Key 3      ", 1);
		break;
	case 3:
		LCD::WriteString("     Key F1     ", 1);
		break;
	case 10:
		LCD::WriteString("     Key 4      ", 2);
		break;
	case 11:
		LCD::WriteString("     Key 5      ", 2);
		break;
	case 12:
		LCD::WriteString("     Key 6      ", 2);
		break;
	case 13:
		LCD::WriteString("     Key F2     ", 2);
		break;
	case 20:
		LCD::WriteString("     Key 7      ", 3);
		break;
	case 21:
		LCD::WriteString("     Key 8      ", 3);
		break;
	case 22:
		LCD::WriteString("     Key 9      ", 3);
		break;
	case 23:
		LCD::WriteString("   Key CLEAR    ", 3);
		break;
	case 30:
		LCD::WriteString("     Key 0      ", 4);
		break;
	case 31:
		LCD::WriteString("     Key .      ", 4);
		break;
	case 32:
		LCD::WriteString("     Key SET    ", 4);
		break;
	case 33:
		float a = 31415.6797;
		LCD::WriteString("   Key ENTER    ", 4);
		LCD::WriteNum(-a);
		break;
	}
}

/*#pragma vector=PORT1_VECTOR
__interrupt void IntP1()
{
	GPIO::Ports(1).Output(0, 1);
}
*/


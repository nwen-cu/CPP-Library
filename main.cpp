/*
 * main.cpp
 *
 *  Created on: 2016Äê7ÔÂ9ÈÕ
 *      Author: Wennx-Desktop
 */

#include<msp430.h>
#include<IO.h>
#include<Interrupt.h>



void main()
{
	void Int1(int);
	WDTCTL=WDTPW+WDTHOLD;
	GPIO::Port_Init();
	//Interrupt::GIntEnabled(0);
	//GPIO::Ports(1).ResEnabled(0, 1);
	//GPIO::Ports(1).Output(0, 1);
	GPIO::Ports(1).ResEnabled(2, 1);
	GPIO::Ports(1).Output(2, 0);
	Interrupt::EnInterruptP(1, 2, 0, Int1);
	Interrupt::GIntEnabled(1);
	//(*Interrupt::f1[2])(0);
	//_BIS_SR(LPM3_bits + GIE);
	for(;;);
}

void Int1(int)
{
	GPIO::Ports(1).Output(0, 1);
}

/*#pragma vector=PORT1_VECTOR
__interrupt void IntP1()
{
	GPIO::Ports(1).Output(0, 1);
}
*/


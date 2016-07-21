/*
 * Timer.h
 *
 *  Created on: 2016Äê7ÔÂ9ÈÕ
 *      Author: Wennx-Desktop
 */

#ifndef TIMER_H_
#define TIMER_H_

#include<msp430.h>
#include<Clock.h>
#include<Interrupt.h>

class Timer
{

public:
	static void TimerA0_Init(RefCLK ClkMode);

	static long DelayCounter;
	static void Delay(int ms)
	{
		//Clock::ACLK_Ref(1);
		TA0CCR0 = 33;
		TA0CTL = TASSEL_1 + MC_2 + TACLR + TAIE;
		Interrupt::GIntEnabled(1);
		while(DelayCounter < ms);
	}

	static void TimerA1_Init(RefCLK ClkMode)
	{
		switch(ClkMode)
		{
		case ACLK:
			TA1CTL |= 0x0100;
			TA1CTL &= 0xFDFF;
			break;
		case SMCLK:
			TA1CTL |= 0x0200;
			TA1CTL &= 0xFEFF;
			break;
		}
	}

	static void TimerA1_Output(int Counter)
	{
		/*TA1CCTL1 |= 0x0040;
		TA1CCTL1 &= 0xFF5F;
		TA1CCR0 = 16484;
		TA1CCR1 = 100;
		TA1CTL |= 0x0010;
		TA1CTL &= 0xFFEF;
		TA1CTL | 0x0004;*/
		P2DIR |= BIT0;
		P2SEL |= BIT0;
		TA1CCTL1 = OUTMOD_3;
		TA1CCR0 = 16484;
		TA1CCR1 = 100;
		TA1CTL = TASSEL_1 + MC_2 + TACLR;
	}
};

long Timer::DelayCounter = 0;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void T0_Int()
{
	Timer::DelayCounter++;
}

#endif /* TIMER_H_ */

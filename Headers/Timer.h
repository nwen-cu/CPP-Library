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
	static void TimerA0_Init(int ClkMode);

	static long DelayCounter;
	static void Delay(int ms)
	{
		Clock::ACLK_Ref(1);
		TA0CCR0 = 33;
		TA0CTL = TASSEL_1 + MC_2 + TACLR + TAIE;
		Interrupt::GIntEnabled(1);
		while(DelayCounter < ms);
	}
};

long Timer::DelayCounter = 0;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void T0_Int()
{
	Timer::DelayCounter++;
}

#endif /* TIMER_H_ */

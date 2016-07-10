/*
 * Interrupt.h
 *
 *  Created on: 2016Äê7ÔÂ9ÈÕ
 *      Author: Wennx-Desktop
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include<IO.h>

typedef void (*func)(int);

class Interrupt
{
public:
	static func f1[8];
	static func f2[8];

	static void GIntEnabled(int value)
	{
		if(value)
			_EINT();
		else
			_DINT();
	}

	static void EnInterruptP(int p, int bit, int edge, func f)
	{
		GPIO::Ports(p).Direction(bit, 0);
		GPIO::Ports(p).IntEdgeSelect(bit, edge);
		GPIO::Ports(p).IntEnabled(bit, 1);
		if(p == 1)
			f1[bit] = f;
		else
			f2[bit] = f;
	}
	static void DisInterruptP(int p, int bit)
	{
		GPIO::Ports(p).IntEnabled(bit, 0);
	}
	static void InterruptP1()
	{
		for(int i = 7; i >= 0; i--)
		{
			if(GPIO::Ports(1).IntFlag(i))
			{
				(*f1[i])(i);
				GPIO::Ports(1).IntFlag(i, 0);
			}
		}
	}

	static void InterruptP2()
	{
		for(int i = 7; i >= 0; i--)
		{
			if(GPIO::Ports(2).IntFlag(i))
			{
				(*f2[i])(i);
				GPIO::Ports(2).IntFlag(i, 0);
			}
		}
	}

};

func Interrupt::f1[8] = {0};
func Interrupt::f2[8] = {0};

#pragma vector=PORT1_VECTOR
__interrupt void IntP1()
{
	Interrupt::InterruptP1();
}

#pragma vector=PORT2_VECTOR
__interrupt void IntP2()
{
	Interrupt::InterruptP2();
}


#endif /* INTERRUPT_H_ */

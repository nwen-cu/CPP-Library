/*
 * KeyMatrix.h
 *
 *  Created on: 2016Äê7ÔÂ10ÈÕ
 *      Author: Wennx-Desktop
 */

#ifndef KEYMATRIX_H_
#define KEYMATRIX_H_

#include<IO.h>
#include<Interrupt.h>

class KeyMatrix
{

	static int ColPort;
	static int RowPort;
	static int ColL;
	static int ColH;
	static int RowL;
	static int RowH;

public:

	static void KeyMatrix_Init(int Col, int Row, int Cl, int Ch, int Rl, int Rh)
	{
		ColPort = Col;
		RowPort = Row;
		ColL = Cl;
		ColH = Ch;
		RowL = Rl;
		RowH = Rh;
		int i;
		for(i = Ch; i >= Cl; i--)
		{
			GPIO::Ports(Col).Direction(i, 1);
			GPIO::Ports(Col).Output(i, 1);
		}
		for(i = Rh; i >= Rl; i--)
		{
			GPIO::Ports(Row).ResEnabled(i, 1);
			GPIO::Ports(Row).Output(i, 0);
			Interrupt::EnInterruptP(Row, i, 0, KeyPress);
		}
		Interrupt::GIntEnabled(1);
	}

	static void KeyPress(int it)
	{
		int i;
		//Interrupt::DisInterruptP(RowPort, it);
		int tmp = GPIO::Ports(ColPort).OutputB();
		GPIO::Ports(ColPort).OutputB(0);
		for(i = ColH; i >= ColL; i--)
		{
			GPIO::Ports(ColPort).Output(i, 1);
			if(GPIO::Ports(RowPort).Input(it))
			{
				GPIO::Ports(1).Output(0, 1);
				KeyDefination(it - RowL, i - ColL);
				break;
			}
			GPIO::Ports(ColPort).Output(i, 0);
		}
		GPIO::Ports(ColPort).OutputB(tmp);
	}

	static void KeyDefination(int r, int c);
};

int KeyMatrix::ColPort = 0;
int KeyMatrix::RowPort = 0;
int KeyMatrix::ColL = 0;
int KeyMatrix::ColH = 0;
int KeyMatrix::RowL = 0;
int KeyMatrix::RowH = 0;


#endif /* KEYMATRIX_H_ */

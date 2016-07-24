/*
 * IO.h
 *
 *  Created on: 2016Äê7ÔÂ9ÈÕ
 *      Author: Wennx-Desktop
 */

#ifndef IO_H_
#define IO_H_

#include<msp430.h>

typedef volatile unsigned char reg;

class Port
{
	reg *In;
	reg *Out;
	reg *Dir;
	reg *DriSel;
	reg *FSel;
	reg *REn;
	reg *IntEn;
	reg *IntEdSel;
	reg *IntFlg;

public:
	Port(reg *PxIN, reg *PxOUT, reg *PxDIR, reg *PxDS, reg *PxSEL, reg *PxREN, reg *PxIE = 0, reg *PxIES = 0, reg *PxIFG = 0)
	{

		In = PxIN;
		Out = PxOUT;
		Dir = PxDIR;
		DriSel = PxDS;
		FSel = PxSEL;
		REn = PxREN;
		IntEn = PxIE;
		IntEdSel = PxIES;
		IntFlg = PxIFG;
		*PxOUT = 0x00;
		*PxDIR = 0xFF;
		*PxDS = 0x00;
		*PxSEL = 0x00;
		*PxREN = 0x00;
		*PxIE = 0x00;
		*PxIES = 0x00;
		*PxIFG = 0x00;

	}

	int InputB()
	{
		return *In;
	}
	int Input(int bit)
	{
		return (((1 << bit) & *In) >> bit);
	}

	void OutputB(int value)
	{
		*Out = value;
	}
	int OutputB()
	{
		return *Out;
	}
	void Output(int bit, int value)
	{
		if(value)
			*Out |= (1 << bit);
		else
			*Out &= ~(1 << bit);
	}
	int Output(int bit)
	{
		return (((1 << bit) & *Out) >> bit);
	}

	void DirectionB(int value)
	{
		*Dir = 0xFF * value;
	}
	int DirectionB()
	{
		return *Dir;
	}
	void Direction(int bit, int value)
	{
		if(value)
			*Dir |= (1 << bit);
		else
			*Dir &= ~(1 << bit);
	}
	int Direction(int bit)
	{
		return (((1 << bit) & *Dir) >> bit);
	}

	void DriveSelectB(int value)
	{
		*DriSel = 0xFF * value;
	}
	int DriveSelectB()
	{
		return *DriSel;
	}
	void DriveSelect(int bit, int value)
	{
		if(value)
			*DriSel |= (1 << bit);
		else
			*DriSel &= ~(1 << bit);
	}
	int DriSelect(int bit)
	{
		return (((1 << bit) & *DriSel) >> bit);
	}

	void FuncSelectB(int value)
	{
		*FSel = 0xFF * value;
	}
	int FuncSelectB()
	{
		return *FSel;
	}
	void FuncSelect(int bit, int value)
	{
		if(value)
			*FSel |= (1 << bit);
		else
			*FSel &= ~(1 << bit);
	}
	int FuncSelect(int bit)
	{
		return (((1 << bit) & *FSel) >> bit);
	}

	void ResEnabledB(int value)
	{
		*REn = 0xFF * value;
	}
	int ResEnabledB()
	{
		return *REn;
	}
	void ResEnabled(int bit, int value)
	{
		if(value)
			*REn |= (1 << bit);
		else
			*REn &= ~(1 << bit);
	}
	int ResEnabled(int bit)
	{
		return (((1 << bit) & *REn) >> bit);
	}

	void IntEnabledB(int value)
	{
		*IntEn = 0xFF * value;
	}
	int IntEnabledB()
	{
		return *IntEn;
	}
	void IntEnabled(int bit, int value)
	{
		if(value)
			*IntEn |= (1 << bit);
		else
			*IntEn &= ~(1 << bit);
	}
	int IntEnabled(int bit)
	{
		return (((1 << bit) & *IntEn) >> bit);
	}

	void IntEdgeSelectB(int value)
	{
		*IntEdSel = 0xFF * value;
	}
	int IntEdgeSelectB()
	{
		return *IntEdSel;
	}
	void IntEdgeSelect(int bit, int value)
	{
		if(value)
			*IntEdSel |= (1 << bit);
		else
			*IntEdSel &= ~(1 << bit);
	}
	int IntEdgeSelect(int bit)
	{
		return (((1 << bit) & *IntEdSel) >> bit);
	}

	void IntFlagB(int value)
	{
		*IntFlg = 0xFF * value;
	}
	int IntFlagB()
	{
		return *IntFlg;
	}
	void IntFlag(int bit, int value)
	{
		if(value)
			*IntFlg |= (1 << bit);
		else
			*IntFlg &= ~(1 << bit);
	}
	int IntFlag(int bit)
	{
		return (((1 << bit) & *IntFlg) >> bit);
	}

};





class GPIO
{
	static Port *p[9];
public:
	static void Port_Init()
	{
		P1OUT = 0;
		P2OUT = 0;
		P3OUT = 0;
		P4OUT = 0;
		P5OUT = 0;
		P6OUT = 0;
		P7OUT = 0;
		P8OUT = 0;
		P1DIR = 0xFF;
		P2DIR = 0xFF;
		P3DIR = 0xFF;
		P4DIR = 0xFF;
		P5DIR = 0xFF;
		P6DIR = 0xFF;
		P7DIR = 0xFF;
		P8DIR = 0xFF;
	}

	static Port& Ports(int ind)
	{
		if(p[ind])return *p[ind];
		switch(ind)
		{
		case 1:
			p[1] = new Port(&P1IN, &P1OUT, &P1DIR, &P1DS, &P1SEL, &P1REN, &P1IE, &P1IES, &P1IFG);
			break;
		case 2:
			p[2] = new Port(&P2IN, &P2OUT, &P2DIR, &P2DS, &P2SEL, &P2REN, &P2IE, &P2IES, &P2IFG);
			break;
		case 3:
			p[3] = new Port(&P3IN, &P3OUT, &P3DIR, &P3DS, &P3SEL, &P3REN);
			break;
		case 4:
			p[4] = new Port(&P4IN, &P4OUT, &P4DIR, &P4DS, &P4SEL, &P4REN);
			break;
		case 5:
			p[5] = new Port(&P5IN, &P5OUT, &P5DIR, &P5DS, &P5SEL, &P5REN);
			break;
		case 6:
			p[6] = new Port(&P6IN, &P6OUT, &P6DIR, &P6DS, &P6SEL, &P6REN);
			break;
		case 7:
			p[7] = new Port(&P7IN, &P7OUT, &P7DIR, &P7DS, &P7SEL, &P7REN);
			break;
		case 8:
			p[8] = new Port(&P8IN, &P8OUT, &P8DIR, &P8DS, &P8SEL, &P8REN);
			break;
		}
		return *p[ind];
	}
};
Port *GPIO::p[9] = {0};

void Delay_1ms()
{
	int i;
	for(i = 150; i > 0; i--)_NOP();
}

void Delay_Nms(int n)
{
	int i;
	for(i = n; i > 0; i--)Delay_1ms();
}

#endif /* IO_H_ */

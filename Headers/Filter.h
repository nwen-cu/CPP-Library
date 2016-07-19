/*
 * Filter.h
 *
 *  Created on: 2016Äê7ÔÂ16ÈÕ
 *      Author: Wennx-Desktop
 */

#ifndef HEADERS_FILTER_H_
#define HEADERS_FILTER_H_

#include<IO.h>
#include<Clock.h>

class Filter
{
	static int AddrPort;
	static int DataPort;
	static int CtrlPort;
	static int AddrH;
	static int AddrL;
	static int D1bit;
	static int D0bit;
	static int RWbit;
	static int Ebit;
public:
	static void Filter_Init(int APort, int DPort, int CPort, int AH, int AL, int D1, int D0, int RW, int E)
	{
		AddrPort = APort;
		DataPort = DPort;
		CtrlPort = CPort;
		AddrH = AH;
		AddrL = AL;
		D1bit = D1;
		D0bit = D0;
		RWbit = RW;
		Ebit = E;

		int i;
		for(i = AddrH; i >= AddrL; i--)
		{
				GPIO::Ports(AddrPort).Direction(i, 1);
		}
		GPIO::Ports(DataPort).Direction(D1bit, 1);
		GPIO::Ports(DataPort).Direction(D0bit, 1);
		GPIO::Ports(CtrlPort).Direction(RWbit, 1);
		GPIO::Ports(CtrlPort).Direction(Ebit, 1);

		GPIO::Ports(CtrlPort).Output(RWbit, 1);
	}

	static void WriteData(int addr, int data)
	{
		int i;
		for(i = AddrH; i >= AddrL; i--)
		{
			GPIO::Ports(AddrPort).Output(i, (addr & (1 << (i - AddrL))) >> (i - AddrL));
		}
		GPIO::Ports(CtrlPort).Output(RWbit, 0);
		GPIO::Ports(DataPort).Output(D1bit, (data & 2) >> 1);
		GPIO::Ports(DataPort).Output(D0bit, data & 1);
		GPIO::Ports(CtrlPort).Output(RWbit, 1);

	}

	static void FilterMode(int fil, int mode)
	{
		if(fil = 1)
		{
			WriteData(0, mode);
		}
		else
		{
			WriteData(8, mode);
		}
	}

	static void FilterFreq(int fil, int freq)
	{
		int addr = 1;
		if(fil == 2)addr += 8;
		WriteData(addr, freq & 3);
		addr++;
		WriteData(addr, (freq >> 2) & 3);
		addr++;
		WriteData(addr, (freq >> 4) & 3);
		addr++;
		WriteData(addr, (freq >> 6) & 3);
	}

	static void FilterQual(int fil, int qual)
	{
		int addr = 4;
		if(fil == 2)addr += 8;
		WriteData(addr, qual & 3);
		addr++;
		WriteData(addr, (qual >> 2) & 3);
		addr++;
		WriteData(addr, (qual >> 2) & 3);
	}

};

int Filter::AddrPort = 0;
int Filter::DataPort = 0;
int Filter::CtrlPort = 0;
int Filter::AddrH = 0;
int Filter::AddrL = 0;
int Filter::D1bit = 0;
int Filter::D0bit = 0;
int Filter::RWbit = 0;
int Filter::Ebit = 0;


#endif /* HEADERS_FILTER_H_ */

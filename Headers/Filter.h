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
	static int OEbit;
public:
	static void Filter_Init(int APort, int DPort, int CPort, int AH, int AL, int D1, int D0, int OE)
	{
		AddrPort = APort;
		DataPort = DPort;
		CtrlPort = CPort;
		AddrH = AH;
		AddrL = AL;
		D1bit = D1;
		D0bit = D0;
		OEbit = OE;

		int i;
		for(i = AddrH; i >= AddrL; i--)
		{
				GPIO::Ports(AddrPort).Direction(i, 1);
		}
		GPIO::Ports(DataPort).Direction(D1bit, 1);
		GPIO::Ports(DataPort).Direction(D0bit, 1);
		GPIO::Ports(CtrlPort).Direction(OEbit, 1);

	}

	static void Delay_1ms()
	{
		int i;
		for(i = 150; i > 0; i--)_NOP();
	}

	static void Delay_Nms(int n)
	{
		int i;
		for(i = n; i > 0; i--)Delay_1ms();
	}

	static void WriteData(int addr, int data)
	{
		int i;
		for(i = AddrH; i >= AddrL; i--)
		{
			GPIO::Ports(AddrPort).Output(i, (addr & (1 << (i - AddrL))) >> (i - AddrL));
		}

		GPIO::Ports(DataPort).Output(D1bit, (data & 2) >> 1);
		GPIO::Ports(DataPort).Output(D0bit, data & 1);
		GPIO::Ports(CtrlPort).Output(OEbit, 0);
		Delay_1ms();
		GPIO::Ports(CtrlPort).Output(OEbit, 1);
		Delay_1ms();

	}

	static void FilterMode(int fil, int mode)
	{
		if(fil == 1)
		{
			WriteData(0, mode);
		}
		else
		{
			WriteData(8, mode);
		}
	}

	static void FilterFreq(int fil, long freq)
	{
		int addr = 1;
		if(fil == 2)addr += 8;
		WriteData(addr, freq & 3);
		addr++;
		WriteData(addr, (freq >> 2) & 3);
		addr++;
		WriteData(addr, (freq >> 4) & 3);
	}

	static void FilterQual(int fil, int qual)
	{
		int addr = 4;
		if(fil == 2)addr += 8;
		WriteData(addr, qual & 3);
		addr++;
		WriteData(addr, (qual >> 2) & 3);
		addr++;
		WriteData(addr, (qual >> 4) & 3);
		addr++;
		WriteData(addr, (qual >> 6) & 1);
	}

};

int Filter::AddrPort = 0;
int Filter::DataPort = 0;
int Filter::CtrlPort = 0;
int Filter::AddrH = 0;
int Filter::AddrL = 0;
int Filter::D1bit = 0;
int Filter::D0bit = 0;
int Filter::OEbit = 0;


#endif /* HEADERS_FILTER_H_ */

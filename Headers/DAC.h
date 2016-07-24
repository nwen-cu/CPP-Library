/*
 * DAC.h
 *
 *  Created on: 2016Äê7ÔÂ24ÈÕ
 *      Author: Wennx-Desktop
 */

#ifndef HEADERS_DAC_H_
#define HEADERS_DAC_H_

#include<IO.h>

class DAC
{
	static int DataPort;
	static int CtrlPort;
	static int CSbit;
	static int WRbit;
	static float VRef
public:
	static void DAC_Init(int DPort, int CPort, int CS, int WR, float Vref)
	{
		DataPort = DPort;
		CtrlPort = CPort;
		CSbit = CS;
		WRbit = WR;
		VRef = Vref;
	}

	static void DAC_Write(int data)
	{
		GPIO::Ports(DataPort).DirectionB(1);
		GPIO::Ports(DataPort).OutputB(data);
		GPIO::Ports(CtrlPort).Output(WRbit, 1);
		GPIO::Ports(CtrlPort).Output(WRbit, 0);
		GPIO::Ports(CtrlPort).Output(WRbit, 1);
	}

	static void AnlogOutput(int voltage)
	{

	}
};



#endif /* HEADERS_DAC_H_ */

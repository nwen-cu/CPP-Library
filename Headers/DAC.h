/*
 * DAC.h
 *
 *  Created on: 2016Äê7ÔÂ24ÈÕ
 *      Author: Wennx-Desktop
 */

#ifndef HEADERS_DAC_H_
#define HEADERS_DAC_H_

#include<IO.h>
#include<LCD.h>

class DAC
{
	static int DataPort;
	static int CtrlPort;
	static int CSbit;
	static int WRbit;
	static float VRef;
public:
	static void DAC_Init(int DPort, int CPort, int CS, int WR, float Vref)
	{
		DataPort = DPort;
		CtrlPort = CPort;
		CSbit = CS;
		WRbit = WR;
		VRef = Vref;

		GPIO::Ports(CtrlPort).Direction(CSbit, 1);
		GPIO::Ports(CtrlPort).Direction(WRbit, 1);
		GPIO::Ports(CtrlPort).Output(CSbit, 1);
		GPIO::Ports(CtrlPort).Output(WRbit, 1);
	}

	static void DAC_Write(int data)
	{
		GPIO::Ports(CtrlPort).Output(WRbit, 1);
		GPIO::Ports(CtrlPort).Output(CSbit, 0);
		GPIO::Ports(DataPort).DirectionB(1);
		GPIO::Ports(DataPort).OutputB(data);
		GPIO::Ports(CtrlPort).Output(WRbit, 0);
		Delay_Nms(500);
		GPIO::Ports(CtrlPort).Output(WRbit, 1);
		GPIO::Ports(CtrlPort).Output(CSbit, 1);
	}

	static void AnlogOutput(float voltage)
	{

		LCD::WriteNum(voltage);
		LCD::WriteNum((float)(255.0 * voltage / VRef), 2);
		LCD::WriteNum((int)(255.0 * voltage / VRef), 3);
		DAC_Write((int)(255.0 * voltage / VRef));
	}


};

int DAC::DataPort = 0;
int DAC::CtrlPort = 0;
int DAC::CSbit = 0;
int DAC::WRbit = 0;
float DAC::VRef = 0;



#endif /* HEADERS_DAC_H_ */

/*
 * LCD.h
 *
 *  Created on: 2016Äê7ÔÂ11ÈÕ
 *      Author: Wennx-Desktop
 */

#ifndef LCD_H_
#define LCD_H_

#include<IO.h>
//#include<Timer.h>

class LCD
{
	static int DPort;
	static int CPort;
	static int RSbit;
	static int RWbit;
	static int Ebit;
	static int RSTbit;
public:
	/*static void LCD_Init(int DP, int CP, int RS, int RW, int E, int RST)
	{
		DPort = DP;
		CPort = CP;
		RSbit = RS;
		RWbit = RW;
		Ebit = E;
		RSTbit = RST;

		GPIO::Ports(DP).DriveSelectB(1);
		GPIO::Ports(DP).ResEnabledB(1);
		GPIO::Ports(CP).DriveSelect(RS, 1);
		GPIO::Ports(CP).ResEnabled(RS, 1);
		GPIO::Ports(CP).DriveSelect(RW, 1);
		GPIO::Ports(CP).ResEnabled(RW, 1);
		GPIO::Ports(CP).DriveSelect(E, 1);
		GPIO::Ports(CP).ResEnabled(E, 1);
		GPIO::Ports(CP).DriveSelect(RST, 1);
		GPIO::Ports(CP).ResEnabled(RST, 1);

		GPIO::Ports(CP).Output(RST, 1);
		GPIO::Ports(CP).Output(RST, 0);
		GPIO::Ports(CP).Output(RST, 1);

		WriteCommand(0x30, 0);
		WriteCommand(0x30, 0);
		WriteCommand(0x0C, 1);
		WriteCommand(0x01, 1);
		WriteCommand(0x06, 1);
	}

	 static void WriteData(int data)
	{
		RDbf();
		GPIO::Ports(CPort).Output(RSbit, 1);
		GPIO::Ports(CPort).Output(RWbit, 0);
		GPIO::Ports(CPort).Output(Ebit, 1);
		GPIO::Ports(DPort).OutputB(data);
		GPIO::Ports(CPort).Output(Ebit, 0);
	}

	static void WriteCommand(int cmd, int busyc)
	{
		if(busyc)RDbf();
		GPIO::Ports(CPort).Output(RSbit, 0);
		GPIO::Ports(CPort).Output(RWbit, 0);
		GPIO::Ports(CPort).Output(Ebit, 1);
		GPIO::Ports(DPort).OutputB(cmd);
		GPIO::Ports(CPort).Output(Ebit, 0);
	}

	static void WriteString(int line, char *string)
	{
		int addr, i;
		switch(line)
		{
		case 1:
			addr = 0x80;
			break;
		case 2:
			addr = 0x90;
			break;
		case 3:
			addr = 0x88;
			break;
		case 4:
			addr = 0x98;
			break;
		}

		WriteCommand(addr, 1);
		for(i = 0; i < 16; i++)
		{
			WriteData(*string++);
		}

	}

	static void RDbf()
	{
		for(;;)
		{
			GPIO::Ports(CPort).Output(RSbit, 0);
			GPIO::Ports(CPort).Output(RWbit, 1);
			GPIO::Ports(CPort).Output(Ebit, 0);
			GPIO::Ports(DPort).OutputB(0xFF);
			GPIO::Ports(CPort).Output(Ebit, 0);
			GPIO::Ports(DPort).DirectionB(0);
			if(GPIO::Ports(DPort).Input(7) == 0)
			{
				GPIO::Ports(DPort).DirectionB(1);
				break;
			}
		}
	}

	static void Delay()
	{
		int i = 1000;
		while(i--);
	}*/

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

	static void LCD_Init(int DP, int CP, int RS, int RW, int E, int RST)
	{
		DPort = DP;
		CPort = CP;
		RSbit = RS;
		RWbit = RW;
		Ebit = E;
		RSTbit = RST;

		GPIO::Ports(CPort).Direction(RSbit, 1);
		GPIO::Ports(CPort).ResEnabled(RSbit, 1);
		GPIO::Ports(CPort).Direction(RWbit, 1);
		GPIO::Ports(CPort).ResEnabled(RWbit, 1);
		GPIO::Ports(CPort).Direction(Ebit, 1);
		GPIO::Ports(CPort).ResEnabled(Ebit, 1);
		GPIO::Ports(CPort).Direction(RSTbit, 1);
		GPIO::Ports(CPort).ResEnabled(RSTbit, 1);

		GPIO::Ports(DPort).DirectionB(1);
		GPIO::Ports(DPort).ResEnabledB(1);

		Delay_Nms(500);
		GPIO::Ports(CPort).Output(RSTbit, 0);
		Delay_1ms();
		GPIO::Ports(CPort).Output(RSTbit, 1);
		Delay_Nms(500);
		WriteCommand(0x30);
		Delay_Nms(100);
		WriteCommand(0x30);
		Delay_Nms(40);
		WriteCommand(0x08);
		Delay_Nms(100);
		WriteCommand(0x10);
		Delay_Nms(100);
		WriteCommand(0x0C);
		Delay_Nms(100);
		WriteCommand(0x01);
		Delay_Nms(10);
		WriteCommand(0x06);
		Delay_Nms(100);

	}

	static void LCD_Test()
	{
		WriteCommand(0x80, 0);
		Delay_Nms(100);
		int i;
		char adder1[] = "      Adeptus   Mechanicus      ";
		char *p = adder1;
		for(i=0;i<32;i++)
		{
			WriteData(*p);
			p++;
		}
	}

	static void WriteCommand(int cmd, int busytest = 1)
	{
		if(busytest)BusyTest();
		GPIO::Ports(CPort).Output(RSbit, 0);
		GPIO::Ports(DPort).DirectionB(1);
		GPIO::Ports(CPort).Output(RWbit, 0);
		GPIO::Ports(DPort).OutputB(cmd);
		GPIO::Ports(CPort).Output(Ebit, 1);
		Delay_1ms();
		GPIO::Ports(CPort).Output(Ebit, 0);
	}

	static void WriteData(int data)
	{
		BusyTest();
		GPIO::Ports(DPort).DirectionB(1);
		GPIO::Ports(CPort).Output(RSbit, 1);
		GPIO::Ports(CPort).Output(RWbit, 0);
		GPIO::Ports(DPort).OutputB(data);
		GPIO::Ports(CPort).Output(Ebit, 1);
		Delay_1ms();
		GPIO::Ports(CPort).Output(Ebit, 0);
	}

	static void BusyTest()
	{
		GPIO::Ports(DPort).DirectionB(0);
		GPIO::Ports(CPort).Output(RSbit, 0);
		GPIO::Ports(CPort).Output(RWbit, 1);
		GPIO::Ports(CPort).Output(Ebit, 1);
		while(GPIO::Ports(DPort).Input(7))
		{
			GPIO::Ports(1).Output(0, 1);
		}
		GPIO::Ports(1).Output(0, 0);
	}

	static void SetPosition(int x, int y)
	{
		int pos;
		switch(x)
		{
		case 1:
			pos = 0x80;
			break;
		case 2:
			pos = 0x90;
			break;
		case 3:
			pos = 0x88;
			break;
		case 4:
			pos = 0x98;
			break;
		}
		pos += y;
		WriteCommand(pos);
		Delay_Nms(100);
	}

	static void WriteString(char *s, int x = 1, int y = 0)
	{
		int i;
		_delay_cycles(10);
		SetPosition(x, y);
		for(i = 0; i < 16; i++)
		{
			WriteData(*s);
			s++;
		}
	}

	static void WriteNum(int num, int x = 1,int y = 0)
	 {
		int i, b = 0;
		char tmp[] = "                ";
		for(i = 1; i < 10000;i *= 10)
		{
			tmp[15 - b] = (num / i) % 10 + 0x30;
			b++;
		}
		WriteString(tmp, x, y);
	 }

	static void WriteNumTest(float n, int x = 1,int y = 0)
	{
		int dot = 0, b = 15, i = 0, tmp;
		float num = n;
		char s[] = "                  ";
		if(num < 0)
		{
			s[0] = '-';
			i++;
			num = -num;
		}
		while(num >= 1)
		{
			num /= 10;
			dot++;
		}
		if(dot == 0)
		{
			s[i] = '0';
			s[i + 1] = '.';
			i += 2;
			dot = -1;
		}
		for(; i <= b; i++)
		{
			tmp = (num *= 10);
			num -= tmp;
			s[i] = tmp + 0x30;
			dot--;
			if(!dot)
			{
				i++;
				s[i] = '.';
				b = i + 4;

			}
		}
		WriteString(s, x, y);
	}


};

int LCD::DPort = 0;
int LCD::CPort = 0;
int LCD::RSbit = 0;
int LCD::RWbit = 0;
int LCD::Ebit = 0;
int LCD::RSTbit = 0;

#endif /* LCD_H_ */

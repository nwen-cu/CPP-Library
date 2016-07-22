/*
 * ADC.h
 *
 *  Created on: 2016Äê7ÔÂ17ÈÕ
 *      Author: Wennx-Desktop
 */

#ifndef HEADERS_ADC_H_
#define HEADERS_ADC_H_

#include<IO.h>
#include<LCD.h>
#include<Interrupt.h>


class ADC
{
public:
	static void ADC_Init(int channel = 0)
	{
		ADC12CTL0 = ADC12SHT02 + ADC12REF2_5V + ADC12REFON + ADC12ON;
		ADC12CTL1 = ADC12SHP;
		ADC12IE = 1;
		ADC12MCTL0 = ADC12SREF_5;
		ADC12CTL0 |= ADC12ENC;
		P6SEL |= 1;
		for(;;)
		{
			ADC12CTL0 |= ADC12SC;
		}
	}
	static void EnableADCInt();
	static void ADCStart();

};

#pragma vector=ADC12_VECTOR
__interrupt void ADC_Interrupt()
{
	float tmp;
	switch(ADC12IV)
	{
	case 6:

		tmp = ADC12MEM0;
		tmp /= 819;
		//tmp += 2.5;
		LCD::WriteNum(tmp);
	}
}



#endif /* HEADERS_ADC_H_ */

/*
 * ADC.h
 *
 *  Created on: 2016Äê7ÔÂ17ÈÕ
 *      Author: Wennx-Desktop
 */

#ifndef HEADERS_ADC_H_
#define HEADERS_ADC_H_

#include<IO.h>
#include<Interrupt.h>

class ADC
{
	static void ADC_Init(int channel = 0)
	{
		ADC12CTL0 = ADC12SHT02 + ADC12REF2_5V + ADC12REFON + ADC12ON;
		ADC12CTL1 = ADC12SHP;
		ADC12IE = 1;
		ADC12CTL0 |= ADC12ENC;
		P6SEL |= 1;
		for(;;)
		{
			ADC12CTRL0 |= ADC12SC;
		}
	}
	static void EnableADCInt();
	static void ADCStart();

};

#pragma vector=ADC12_VECTOR
__interrupt void ADC_Interrupt()
{
	switch(ADC12V)
	{
	case 6:

	}
}



#endif /* HEADERS_ADC_H_ */

/*
 * ADC.h
 *
 *  Created on: 2016��7��17��
 *      Author: Wennx-Desktop
 */

#ifndef HEADERS_ADC_H_
#define HEADERS_ADC_H_

#include<IO.h>
#include<Interrupt.h>

class ADC
{
	static void ADC_Init();
	static void EnableADCInt();
	static void ADCStart();

};

#pragma vector=ADC12_VECTOR
__interrupt void ADC_Interrupt()
{

}



#endif /* HEADERS_ADC_H_ */

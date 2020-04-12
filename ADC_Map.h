/******************************************************************************
 *
 * Module: Analog to Digital Converter
 *
 * File Name: ADC_Map.h
 *
 * Description: Header file for mapping Registers of Analog to Digital Converter Driver
 *
 * Created on: Sep 26, 2019
 *
 * Author: Ahmed Eldakhly & Hesham Hafez
 *
 *******************************************************************************/

#ifndef ADC_MAP_H_
#define ADC_MAP_H_

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "Macro.h"
#include "std_types.h"

/*******************************************************************************
 *                          Mapped Registers                                   *
 *******************************************************************************/

#define ADC_ADMUX	(*(volatile uint8*)0x27)	/*ADC Multiplexer Selection Register – ADMUX*/
#define ADC_ADCSRA	(*(volatile uint8*)0x26)	/*ADC Control and Status Register A – ADCSRA*/
#define ADC_ADCH	(*(volatile uint8*)0x25)	/*The ADC Data Register – ADCH*/
#define ADC_ADCL	(*(volatile uint8*)0x24)	/*The ADC Data Register – ADCL*/
#define ADC_Data	(*(volatile uint16*)0x24)	/*The ADC Data Register*/
#define ADC_SFIOR	(*(volatile uint8*)0x50)	/*Special FunctionIO Register – SFIOR*/


/*******************************************************************************
 *                          Registers Pins                                     *
 *******************************************************************************/

/**************************** ADC_ADMUX PINS ***********************************/
#define ADC_REFS1	7u		/*Bit 7 – REFS1: Reference Selection Bit*/
#define ADC_REFS0	6u		/*Bit 6 – REFS0: Reference Selection Bit*/
#define ADC_ADLAR	5u		/*Bit 5 – ADLAR: ADC Left Adjust Result*/
#define ADC_MUX4	4u		/*Bit 4 – MUX4: Analog Channel and Gain Selection Bit*/
#define ADC_MUX3	3u		/*Bit 3 – MUX3: Analog Channel and Gain Selection Bit*/
#define ADC_MUX2	2u		/*Bit 2 – MUX2: Analog Channel and Gain Selection Bit*/
#define ADC_MUX1	1u		/*Bit 1 – MUX1: Analog Channel and Gain Selection Bit*/
#define ADC_MUX0	0u		/*Bit 0 – MUX0: Analog Channel and Gain Selection Bit*/

/**************************** ADC_ADCSRA PINS ***********************************/
#define ADC_ADEN	7u		/*Bit 7 – ADEN: ADC Enable*/
#define ADC_ADSC	6u		/*Bit 6 – ADSC: ADC Start Conversion*/
#define ADC_ADATE	5u		/*Bit 5 – ADATE: ADC Auto Trigger Enable*/
#define ADC_ADIF	4u		/*Bit 4 – ADIF: ADC Interrupt Flag*/
#define ADC_ADIE	3u		/*Bit 3 – ADIE: ADC Interrupt Enable*/
#define ADC_ADPS2	2u		/*Bit 2 – ADPS2: ADC Prescaler Select Bit*/
#define ADC_ADPS1	1u		/*Bit 1 – ADPS1: ADC Prescaler Select Bit*/
#define ADC_ADPS0	0u		/*Bit 0 – ADPS0: ADC Prescaler Select Bit*/

/**************************** ADC_SFIOR PINS ***********************************/
#define ADC_ADTS2	7u		/*Bit 7 – ADTS2: ADC Auto Trigger Source*/
#define ADC_ADTS1	6u		/*Bit 6 – ADTS1: ADC Auto Trigger Source*/
#define ADC_ADTS0	5u		/*Bit 5 – ADTS0: ADC Auto Trigger Source*/




#endif /* ADC_MAP_H_ */

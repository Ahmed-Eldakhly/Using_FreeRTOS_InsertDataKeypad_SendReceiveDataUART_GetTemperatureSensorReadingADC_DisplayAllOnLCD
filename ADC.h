/******************************************************************************
 *
 * Module: Analog to Digital Converter
 *
 * File Name: ADC.h
 *
 * Description: Header file for Analog to Digital Converter Driver
 *
 * Created on: Sep 26, 2019
 *
 * Author: Ahmed Eldakhly & Hesham Hafez
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "ADC_Map.h"

extern volatile uint32 g_adcResult;

typedef enum
{
	AREF_INTERNAL_VREF_OFF = 0,
	AVCC = 1,
	INTERNAL_VREF = 2
}EnmADCReference_t;

typedef enum
{
	RIGHT_ADJUSTMENT,
	LEFT_ADJUSTMENT
}EnmADCAdjustment_t;

typedef enum
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7

}EnmADCAnalogChannel_t;

typedef enum
{
	PRESCALER_2A,
	PRESCALER_2B,
	PRESCALER_4,
	PRESCALER_8,
	PRESCALER_16,
	PRESCALER_32,
	PRESCALER_64,
	PRESCALER_128

}EnmADCPrescaler_t;


typedef enum
{
	FREE_RUNNING_MODE 	= 0,
	EXTERNAL_INTRRUPT_0 = 2,
	TIMER0_COMPARE_MATCH= 3,
	SINGLE_MODE
}EnmADCAutoTriggerSource_t;


typedef enum
{
	ADC_INTERRUPT_DISABLE,
	ADC_INTERRUPT_ENABLE

}EnmADCInterrupt_t;

typedef struct
{
	EnmADCReference_t			Reference;
	EnmADCAdjustment_t			Adjustment;
	EnmADCAnalogChannel_t		Channel;
	EnmADCPrescaler_t			Prescaler;
	EnmADCAutoTriggerSource_t	TriggerSource;
	EnmADCInterrupt_t 			IntConfig;
}StrADCconfig_t;

extern StrADCconfig_t ADC_Config;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:	ADC_Init
 *
 * Description: 	Initialize the ADC Driver
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void ADC_Init(void);

/*******************************************************************************
 * Function Name:	ADC_ReadChannel
 *
 * Description: 	Function responsible for read analog data from a certain ADC channel
 * 					and convert it to digital using the ADC driver.
 *
 * Inputs:			Channel Number
 *
 * Outputs:			Digital uint16 Data
 *
 * Return:			NULL
 *******************************************************************************/
void ADC_SelectChannel(EnmADCAnalogChannel_t a_ChannelNumber);

/*******************************************************************************
 * Function Name:	ADC_DeInit
 *
 * Description: 	Disable the ADC Driver
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void ADC_DeInit(void);

void ADC_StartConversion(void);

uint16 ADC_ReadChannel(void);

#endif /* ADC_H_ */

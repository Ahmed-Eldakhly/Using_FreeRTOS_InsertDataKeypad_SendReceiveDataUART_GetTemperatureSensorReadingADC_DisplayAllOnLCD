/******************************************************************************
 *
 * Module: Analog to Digital Converter
 *
 * File Name: ADC.c
 *
 * Description: source file for Analog to Digital Converter Driver
 *
 * Created on: Sep 26, 2019
 *
 * Author: Ahmed Eldakhly & Hesham Hafez
 *
 *******************************************************************************/


/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "ADC.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
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
void ADC_Init(void)
{
	switch(ADC_Config.Reference)
	{
	case AREF_INTERNAL_VREF_OFF:
		CLEAR_BIT(ADC_ADMUX,ADC_REFS1);
		CLEAR_BIT(ADC_ADMUX,ADC_REFS0);
		break;
	case AVCC:
		CLEAR_BIT(ADC_ADMUX,ADC_REFS1);
		SET_BIT(ADC_ADMUX,ADC_REFS0);
		break;
	case INTERNAL_VREF:
		SET_BIT(ADC_ADMUX,ADC_REFS1);
		SET_BIT(ADC_ADMUX,ADC_REFS0);
		break;
	default:
		CLEAR_BIT(ADC_ADMUX,ADC_REFS1);
		CLEAR_BIT(ADC_ADMUX,ADC_REFS0);
		break;
	}

	switch(ADC_Config.Adjustment)
	{
	case RIGHT_ADJUSTMENT:
		CLEAR_BIT(ADC_ADMUX,ADC_ADLAR);
		break;
	case LEFT_ADJUSTMENT:
		SET_BIT(ADC_ADMUX,ADC_ADLAR);
		break;
	default:
		CLEAR_BIT(ADC_ADMUX,ADC_ADLAR);
		break;
	}

	switch(ADC_Config.Channel)
	{
	case ADC0:
		CLEAR_BIT(ADC_ADMUX,ADC_MUX4);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX3);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX2);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX1);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX0);
		break;
	case ADC1:
		CLEAR_BIT(ADC_ADMUX,ADC_MUX4);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX3);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX2);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX1);
		SET_BIT(ADC_ADMUX,ADC_MUX0);
		break;
	case ADC2:
		CLEAR_BIT(ADC_ADMUX,ADC_MUX4);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX3);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX2);
		SET_BIT(ADC_ADMUX,ADC_MUX1);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX0);
		break;
	case ADC3:
		CLEAR_BIT(ADC_ADMUX,ADC_MUX4);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX3);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX2);
		SET_BIT(ADC_ADMUX,ADC_MUX1);
		SET_BIT(ADC_ADMUX,ADC_MUX0);
		break;
	case ADC4:
		CLEAR_BIT(ADC_ADMUX,ADC_MUX4);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX3);
		SET_BIT(ADC_ADMUX,ADC_MUX2);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX1);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX0);
		break;
	case ADC5:
		CLEAR_BIT(ADC_ADMUX,ADC_MUX4);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX3);
		SET_BIT(ADC_ADMUX,ADC_MUX2);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX1);
		SET_BIT(ADC_ADMUX,ADC_MUX0);
		break;
	case ADC6:
		CLEAR_BIT(ADC_ADMUX,ADC_MUX4);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX3);
		SET_BIT(ADC_ADMUX,ADC_MUX2);
		SET_BIT(ADC_ADMUX,ADC_MUX1);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX0);
		break;
	case ADC7:
		CLEAR_BIT(ADC_ADMUX,ADC_MUX4);
		CLEAR_BIT(ADC_ADMUX,ADC_MUX3);
		SET_BIT(ADC_ADMUX,ADC_MUX2);
		SET_BIT(ADC_ADMUX,ADC_MUX1);
		SET_BIT(ADC_ADMUX,ADC_MUX0);
		break;
	default:
		/*Do Nothing*/
		break;
	}

	SET_BIT(ADC_ADCSRA,ADC_ADEN);
	CLEAR_BIT(ADC_ADCSRA,ADC_ADSC);

	switch(ADC_Config.IntConfig)
	{
	case ADC_INTERRUPT_DISABLE:
		CLEAR_BIT(ADC_ADCSRA,ADC_ADIE);
		break;
	case ADC_INTERRUPT_ENABLE:
		SET_BIT(ADC_ADCSRA,ADC_ADIE);
		break;
	default:
		/*Do Nothing*/
		break;
	}

	switch(ADC_Config.Prescaler)
	{
	case PRESCALER_2A:
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS2);
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS1);
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS0);
		break;
	case PRESCALER_2B:
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS2);
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS1);
		SET_BIT(ADC_ADCSRA,ADC_ADPS0);
		break;
	case PRESCALER_4:
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS2);
		SET_BIT(ADC_ADCSRA,ADC_ADPS1);
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS0);
		break;
	case PRESCALER_8:
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS2);
		SET_BIT(ADC_ADCSRA,ADC_ADPS1);
		SET_BIT(ADC_ADCSRA,ADC_ADPS0);
		break;
	case PRESCALER_16:
		SET_BIT(ADC_ADCSRA,ADC_ADPS2);
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS1);
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS0);
		break;
	case PRESCALER_32:
		SET_BIT(ADC_ADCSRA,ADC_ADPS2);
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS1);
		SET_BIT(ADC_ADCSRA,ADC_ADPS0);
		break;
	case PRESCALER_64:
		SET_BIT(ADC_ADCSRA,ADC_ADPS2);
		SET_BIT(ADC_ADCSRA,ADC_ADPS1);
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS0);
		break;
	case PRESCALER_128:
		SET_BIT(ADC_ADCSRA,ADC_ADPS2);
		SET_BIT(ADC_ADCSRA,ADC_ADPS1);
		SET_BIT(ADC_ADCSRA,ADC_ADPS0);
		break;
	default:
		SET_BIT(ADC_ADCSRA,ADC_ADPS2);
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS1);
		CLEAR_BIT(ADC_ADCSRA,ADC_ADPS0);
		break;
	}

	switch(ADC_Config.TriggerSource)
	{
	case FREE_RUNNING_MODE:
		SET_BIT(ADC_ADCSRA,ADC_ADATE);
		CLEAR_BIT(ADC_SFIOR,ADC_ADTS2);
		CLEAR_BIT(ADC_SFIOR,ADC_ADTS1);
		CLEAR_BIT(ADC_SFIOR,ADC_ADTS0);
		break;
	case EXTERNAL_INTRRUPT_0:
		SET_BIT(ADC_ADCSRA,ADC_ADATE);
		CLEAR_BIT(ADC_SFIOR,ADC_ADTS2);
		SET_BIT(ADC_SFIOR,ADC_ADTS1);
		CLEAR_BIT(ADC_SFIOR,ADC_ADTS0);
		break;
	case TIMER0_COMPARE_MATCH:
		SET_BIT(ADC_ADCSRA,ADC_ADATE);
		CLEAR_BIT(ADC_SFIOR,ADC_ADTS2);
		SET_BIT(ADC_SFIOR,ADC_ADTS1);
		SET_BIT(ADC_SFIOR,ADC_ADTS0);
		break;
	case SINGLE_MODE:
		CLEAR_BIT(ADC_ADCSRA,ADC_ADATE);
		break;
	default:
		/*Do Nothing*/
		break;
	}

}

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
void ADC_SelectChannel(EnmADCAnalogChannel_t a_ChannelNumber)
{
	/* channel number must be from 0 --> 7 */
	/* clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	/* choose the correct channel by setting the channel number in MUX4:0 bits */
	ADC_ADMUX = (ADC_ADMUX & 0xE0)|(a_ChannelNumber);
}

void ADC_StartConversion(void)
{
	SET_BIT(ADC_ADCSRA,ADC_ADSC); /* start conversion write '1' to ADSC */
	switch(ADC_Config.IntConfig)
	{
	case ADC_INTERRUPT_DISABLE:
		while(GET_BIT(ADC_ADCSRA,ADC_ADIF)==LOW);
		SET_BIT(ADC_ADCSRA,ADC_ADIF); /* clear ADIF by write '1' to it :) */
		break;
	case ADC_INTERRUPT_ENABLE:
		/*DO Nothing*/
		break;
	default:
		/*DO Nothing*/
		break;
	}
}

uint16 ADC_ReadChannel(void)
{
	uint16 ReturnVal;
	if(ADC_Config.Adjustment == LEFT_ADJUSTMENT)
	{
		ReturnVal = (ADC_Data>>6);
	}
	else
	{
		ReturnVal = ADC_Data;
	}
	return ReturnVal;
}
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
void ADC_DeInit(void)
{
	CLEAR_BIT(ADC_ADCSRA,ADC_ADEN);
	CLEAR_BIT(ADC_ADCSRA,ADC_ADIE);
}

/*****************************************************************************
 * Module 	  : FreeRTOS User Story1 Tasks implementation
 *
 * File name  : UserStory1.c
 *
 * Created on : Oct 11, 2019
 *
 * Author     : Ahmed Eldakhly & Hesham Hafez
 ******************************************************************************/

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "UserTasks.h"
#include "queue.h"

/*******************************************************************************
 *                           static Global Variables                           *
 *******************************************************************************/
/*Queue between PushButtonTask & LCD Task*/
static xQueueHandle Queue_PushButton;

/*Queue between Send UART received data & LCD Task*/
static xQueueHandle Queue_UART_Task;

/*Queue between Temperature sensor reading] & LCD Task*/
static xQueueHandle Queue_Temp_Sensor_Task;


/*******************************************************************************
 *                           Global Variables                    		       *
 *******************************************************************************/
TaskHandle_t  InitTask_Flag = NULL;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:	init_Task
 *
 * Description: 	Create all tasks in the system
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void init_Task(void * a_Task_ptr)
{
	/*initialize all HW and preipherals*/
	PushButton_Init();
	UART_Init();
	DIO_SetPinDirection(DIO_PIN1,INPUT);
	ADC_Init();
	ADC_StartConversion();
	LCD_init();

	/*Create Queues*/
	Queue_PushButton = xQueueCreate( 3 , sizeof(uint8) );
	Queue_Temp_Sensor_Task = xQueueCreate( 3 , sizeof(uint32) );
	Queue_UART_Task = xQueueCreate( 3 , sizeof(uint8) );

	/*Create 4 Tasks*/
	/*create Push Button task to reset LCD*/
	xTaskCreate(PushButton_Task  , "PushButton_Task" , 100 ,
			NULL , (1 | portPRIVILEGE_BIT) , NULL);

	/*create UART Task to receive Data by UART*/
	xTaskCreate(UART_Task  , "UART_Task" , configMINIMAL_STACK_SIZE ,
			NULL , (3 | portPRIVILEGE_BIT) , NULL);

	/*create ADC task to read temperature sensor*/
	xTaskCreate(ADC_Task  , "ADC_Task" , 100 ,
			NULL , (2 | portPRIVILEGE_BIT) , NULL);

	/*create LCD task to display other tasks on LCD*/
	xTaskCreate(LCD_Task  , "LCD_Task" , configMINIMAL_STACK_SIZE,
			NULL , (4 | portPRIVILEGE_BIT) , NULL);

	/*suspend this task*/
	vTaskSuspend(InitTask_Flag);
}

/*******************************************************************************
 * Function Name:	PushButtonA_Task
 *
 * Description: 	Push Button ATask
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void PushButton_Task(void * a_Task_ptr)
{
	vTaskDelay(50);
	/* Data is sent to LCD by Queue*/
	uint8 SendData = 1;
	/*de_bouncing Flag to make sure key is pressed*/
	uint8 Debouncing = 0;

	/*comparing value to check if key is pressed*/
	uint8 OldPressedValue = 0;

	while(1)
	{
		/*Check if Button is pressed and enable de_bouncing*/
		if(Debouncing == 0 && Buttons_getPressedButton()==2)
		{
			OldPressedValue =  Buttons_getPressedButton();
			Debouncing++;
			/*de_bouncing Delay*/
			vTaskDelay(10);
		}
		else if(Debouncing == 1)
		{
			/*check if button is still pressed after de_bouncing time*/
			while(OldPressedValue == Buttons_getPressedButton())
			{
				SendData = 1;
				/*Send push Button was pressed to Lcd by queue*/
				xQueueSend(Queue_PushButton , &SendData , 100);
				vTaskDelay(20);
			}
			Debouncing = 2;
		}
		else if(Debouncing == 2)
		{
			SendData = 0;
			/*Send push Button was released to Lcd by queue*/
			Debouncing = 0;
			vTaskDelay(20);
		}
		else
		{
			/*Send push Button is in Idle state to Lcd by queue*/
			SendData = 3;
			xQueueSend(Queue_PushButton , &SendData , 100);
			vTaskDelay(20);
		}
	}
}

/*******************************************************************************
 * Function Name:	ADC_Task
 *
 * Description: 	calculate temperature and send it to LCD
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void ADC_Task(void * a_Task_ptr)
{
	vTaskDelay(150);

	/*temperature sensor sample value*/
	uint32 temp;

	/*compare with old value of temperature*/
	uint32 oldtemp = 0;
	while(1)
	{
		/*temperature sensor equation*/
		temp= (((uint32)ADC_ReadChannel()*750)/(1534))/2; /* calculate the temp from the ADC value*/
		if (temp!=oldtemp)
		{
			oldtemp=temp;

			/*send new temperature to LCD task to display it on LCD*/
			xQueueSend(Queue_Temp_Sensor_Task , &temp , 10);
		}

		/*start a new sample*/
		ADC_StartConversion();
		vTaskDelay(200);
	}
}
/*******************************************************************************
 * Function Name:	LCD_Task
 *
 * Description: 	LCD Task
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void LCD_Task(void * a_Task_ptr)
{
	vTaskDelay(100);
	/*received data from Push Button Task to display button state on LCD*/
	uint8 PushButton_Task_Data = 0;

	/*received message from ADC Task to display button state on LCD*/
	uint32 Temp_Task_Data = 0;

	/*received message from UART Task to display button state on LCD*/
	uint8 UART_Task_Data = 0;

	/*dummy & TenPowerDigit & DigitCounter buffers to convert integer number to string*/
	uint8 DigitCounter = 0;
	uint8 dummy = 0;
	uint8 TenPowerDigit = 1;

	/*LCD strings*/
	uint8 Temperature_String[] = "Temp=";
	uint8 UART_String[] = "UART DATA=";
	while(1)
	{
		/*receive messages from other tasks by queues*/
		xQueueReceive(Queue_PushButton , &PushButton_Task_Data , 10);
		xQueueReceive(Queue_Temp_Sensor_Task , &Temp_Task_Data , 10);
		xQueueReceive(Queue_UART_Task , &UART_Task_Data , 10);

		dummy = Temp_Task_Data;
		TenPowerDigit = 1;

		/*Clear LCD if Push button is pressed*/
		if(PushButton_Task_Data == 1)
		{
			LCD_clearScreen();
		}
		/*display temperature and received messages from UART on LCD*/
		else
		{
			LCD_displayStringRowColumn(0 , 0 , Temperature_String);

			/*Convert integer to string*/
			for(;dummy != 0;)
			{
				DigitCounter++;
				TenPowerDigit *= 10;
				dummy /= 10;
			}
			for(;DigitCounter > 0;DigitCounter--)
			{
				LCD_displayCharacter((Temp_Task_Data/(TenPowerDigit/10))+48);
				Temp_Task_Data %=(TenPowerDigit/10);
				TenPowerDigit /= 10;
			}

			/*display UART received Data*/
			LCD_displayStringRowColumn(1 , 0 , UART_String);
			LCD_displayCharacter(UART_Task_Data);
		}
		vTaskDelay(50);
	}
}

/*******************************************************************************
 * Function Name:	UART_Task
 *
 * Description: 	UART receive data
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void UART_Task(void * a_Task_ptr)
{

	vTaskDelay(100);
	uint8 UART_Data = 8;
	while(1)
	{
		/*receive data from UART*/
		UART_Data = USART_DataRegister;

		/* Data is sent to LCD by Queue*/
		xQueueSend(Queue_UART_Task , &UART_Data , 100);
		vTaskDelay(200);
	}
}


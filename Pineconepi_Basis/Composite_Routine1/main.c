/**
  ******************************************************************************
  * @file    main.c 
  * @author  LGG
  * @version V1.0.0
  * @date    15-July-2019
  * @brief   Use key to control LED flashing in different ways.
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "PineconePinano.h"
#include "button.h"
#include "led.h"


/* Define status */
#define 	TRUE		1
#define		FALSE		0

#define 	ENABLE	1
#define 	DISABLE	0


/* Define correlation variables */
unsigned char time_10ms = 0;
unsigned char time_100ms = 0;


/* Define correlation falgs */
unsigned char flag_10ms = FALSE;
unsigned char flag_100ms = FALSE;


/* Define LED display mode */
en_led_mode mode = LED_MODE_0;


/* Declare function */
void KEY_Process(key_value key_value);


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main()
{
	key_value temp;
	
	KEY_Init();	/* Initialize KEY */
	LED_Init();	/* Initialize LED */
	
	/* Initialize TIMER0 */
	TMOD = 0x00;
	TL0 = 0x2f;
	TH0 = 0xf8;
	ET0 = 1;
	EA = 1;
	TR0 = 1;
	
	while(1)
	{
		/* Handle 10ms event */
		if(flag_10ms == TRUE)
		{
			flag_10ms = FALSE;
			temp = KEY_Scan();
			if(temp != NULL_Pressed)
				KEY_Process(temp);
		}
		
		/* Handle 100ms event */
		if(flag_100ms == TRUE)
		{
			flag_100ms = FALSE;
			led_mode_handle(mode);
		}
	}
}


/**
  * @brief  TIMER1 interrupt fun
  * @param  None
  * @retval None
  */
void TM0_Isr() interrupt 1
{
	/* Timing 10 ms */
	if(++time_10ms >= 10)
	{
		time_10ms = 0;
		flag_10ms = TRUE;
		
		if(++time_100ms >= 20)
		{
			time_100ms = 0;
			flag_100ms = TRUE;
		}
	}
}


/**
  * @brief  key process.
  * @param  key value
  * @retval None
  */
void KEY_Process(key_value key_value)
{
	switch(key_value)
	{
		case KEY1_Pressed:		//K2 pressed
			mode = LED_MODE_1;	//LED MODE1 blink
			break;

		case KEY2_Pressed:		//K3 pressed
			mode = LED_MODE_2;	//LED MODE1 blink
			break;
			
		case KEY3_Pressed:		//K4 pressed
			mode = LED_MODE_3;	//LED MODE1 blink
			break;
			
		case KEY4_Pressed:		//5 pressed
			mode = LED_MODE_4;	//LED MODE1 blink
			break;
			
			
		case KEY1_LongPressed:	//K2 long_pressed
			mode = LED_MODE_0;
			P1 = 0x00;		//LED all bright
			break;
			
		case KEY2_LongPressed:	//K3 long_pressed
			mode = LED_MODE_0;
			P1 = 0x0f;		//LED lift bright
			break;
			
		case KEY3_LongPressed:	//K4 long_pressed
			mode = LED_MODE_0;
			P1 = 0xf0;		//LED right bright
			break;
			
		case KEY4_LongPressed:	//K5 long_pressed
			mode = LED_MODE_0;
			P1 = 0xff;		//LED all exterminate
			break;

		default:				//Other
			break;
	}
}



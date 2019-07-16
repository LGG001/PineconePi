/**
  ******************************************************************************
  * @file    button.h 
  * @author  LGG
  * @version V1.0.0
  * @date    15-July-2019
  * @brief   This file contains the headers of button handlers.
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_H
#define __BUTTON_H


/* Includes ------------------------------------------------------------------*/
#include "PineconePinano.h"


/* Define button related time constant */
#define	RELEASE_TIMES					3				//key release time
#define	DEBOUNCE_TIMES				5				//key debounce time
#define	LONG_PRESSED_TIMES		200			//key long_pressed time


/* Define button KEY-VALUE */
#define KEY_VALUE			0xcc				//none
#define KEY1_VALUE		0xc8				//KEY1 pressed value
#define KEY2_VALUE		0xc4				//KEY2 pressed value
#define KEY3_VALUE		0x8c				//KEY3 pressed value
#define KEY4_VALUE		0x4c				//KEY4 pressed value


/* Enum button status */
typedef enum
{
	IDLE,					//idle
	Debounce,			//debounce
	Pressed,			//pressed
	Long_Pressed,	//long_pressed
	Release,			//release
}key_status;


/* Enum button status */
typedef enum
{
	NULL_Pressed=0,		//none
	KEY1_Pressed,			//KEY1 pressed
	KEY2_Pressed,			//KEY2 pressed
	KEY3_Pressed,			//KEY3 pressed
	KEY4_Pressed,			//KEY4 pressed
	KEY1_LongPressed,	//KEY1 long pressed
	KEY2_LongPressed,	//KEY2 long pressed
	KEY3_LongPressed,	//KEY3 long pressed
	KEY4_LongPressed,	//KEY4 long pressed
}key_value;


/* Define time variables struct */
typedef struct
{
	unsigned int Time_Debounce;			//debounce time
	unsigned int Time_LongPressed;	//long_pressed time
	unsigned int Time_Release;			//release time
}key_time;


/* Define button parameter struct */
typedef struct
{
	unsigned int Index;				//index
	key_value Value1;					//value_1(pressed)
	key_value Value2;					//value_2(long_pressed)
	key_status State1;				//status_1(pressed)
	key_status State2;				//status_2(long_pressed)
}KEY_Table;




/* Exported functions ------------------------------------------------------- */
void KEY_Init(void);	
key_value KEY_Scan(void);

#endif

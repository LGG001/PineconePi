/**
  ******************************************************************************
  * @file    button.c 
  * @author  LGG
  * @version V1.0.0
  * @date    15-July-2019
  * @brief   This file is button related functions.
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "button.h"


/* key-value tab */
const KEY_Table key_tab[]=
{
	{KEY1_VALUE,	KEY1_Pressed,	KEY1_LongPressed,	Pressed, Long_Pressed},		//KEY1-pressed-long_pressed
	{KEY2_VALUE, 	KEY2_Pressed,	KEY2_LongPressed,	Pressed, Long_Pressed},		//KEY2-pressed-long_pressed
	{KEY3_VALUE, 	KEY3_Pressed,	KEY3_LongPressed,	Pressed, Long_Pressed},		//KEY3-pressed-long_pressed
	{KEY4_VALUE,	KEY4_Pressed,	KEY4_LongPressed,	Pressed, Long_Pressed},		//KEY4-pressed-long_pressed
};


/**
  * @brief  KEY Initialize
  * @param  None
  * @retval None
  */
void KEY_Init(void)
{	
	/* Initialize P3 as push-pull putput */
	P3M0 = 0x00;
	P3M1 = 0x00;
	
	/* P3 output high */
	P3 = 0xff;
}


/**
  * @brief  KEY scan
  * @param  None
  * @retval key_value
  */
key_value KEY_Scan(void)
{
	static key_status state;												//key satatus
	static key_time 	time;													//key time
	static long_pressed_flag = 0;										//long_pressed flag
	volatile key_value KEY_Value = NULL_Pressed;		//key-value
	static unsigned char i;													//sacn key-value tab count
	unsigned int key_temp;
	
	key_temp = (P3 & KEY_VALUE);										//read key-value
	if(key_temp != KEY_VALUE)												//determine if a key is pressed
	{
		time.Time_Release = RELEASE_TIMES;						//assign release time
		switch(state)																	//state judgement
		{
			case IDLE:																	//idle
				time.Time_Debounce = DEBOUNCE_TIMES;			//assign debounce time
				state = Debounce;													//state is set debounce
				break;
				
			case Debounce:															//debounce
				if(--time.Time_Debounce == 0)							//debounce completed
				{
					time.Time_LongPressed = LONG_PRESSED_TIMES;	//assign long_pressed time
					
					for(i=0; ;i++)												//loop the key-value tab
					{
						if(key_temp == key_tab[i].Index)		//index of the query
						{
							state = key_tab[i].State1;				//the corresponding index state is set to pressed
							break;
						}
						else if(i >= 4)							//out of range or the corresponding key value cannot be found
						{
							state=IDLE;								//set the state to idle
							return NULL_Pressed;			//retuen none
						}
					}
				}
				break;
				
			case Pressed:											//pressed
				if(--time.Time_LongPressed == 0)//long_pressed debounce completed
				{
					for(i=0; ;i++)								//loop the key-value tab
					{
						if(key_temp == key_tab[i].Index)	//index of the query
						{
							state = key_tab[i].State2;			//the corresponding index state is set to long_pressed
							break;
						}
						else if(i > 4)						//out of range or the corresponding key value cannot be found
						{
							state=IDLE;							//set the state to idle
							return NULL_Pressed;		//retuen none
						}
					}
				}
				break;

			case Long_Pressed:							//long_pressed
				if(long_pressed_flag != 1)		
				{
					long_pressed_flag = 1;			//set long_pressed flag
					KEY_Value=key_tab[i].Value2;//set the key-value to long_pressed
				}
				state=IDLE;							//set the state to idle
				break;
				
			default:									//other, set the state to idle
				state=IDLE;
				break;
		}
	}
	else
	{
		if(time.Time_Release != 0)				//at idle time, stkey.release = 0
		{
			if(--time.Time_Release == 0)		//key release
			{
				switch(state)
				{
					case Pressed:								//pressed
						if(long_pressed_flag == 1)//long_pressed is exist, clear long_pressed flag
							long_pressed_flag = 0;
						else
							KEY_Value=key_tab[i].Value1;	//assign key-value
						state=IDLE;								//set the state to idle
						break;
						
					case Long_Pressed:					//long_pressed
						long_pressed_flag = 0;		//clear long_pressed flag
						state=IDLE;								//set the state to idle
						break;
						
					default:							//other, set the state to idle
						state=IDLE;
						break;
				}
			}
		}
	}
	return KEY_Value;							//return key-value
}


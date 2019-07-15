/**
  ******************************************************************************
  * @file    led.c 
  * @author  LGG
  * @version V1.0.0
  * @date    15-July-2019
  * @brief   This file is LED related functions.
  ******************************************************************************
  */
	

/* Includes ------------------------------------------------------------------*/
#include "led.h"


/**
  * @brief  LED Initialize
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
	/* Initialize P1 as push-pull putput */
	P1M0 = 0xff;
	P1M1 = 0x00;
	P1 = 0xff;
	
	/* Initialize P5^5 as push-pull putput */
	P5M0 |= 0x20;
	P5M0 &= 0xdf;
	P55 = 0;
}



/**
  * @brief  LED Flashing from left to right
  * @param  None
  * @retval None
  */
void blink_left_to_right(void)
{
	/* Initialize variables */
	static unsigned char i = 0;
	static unsigned char temp = 0x80;
	
	/* Variable increase and prevent cross-border */
	if(++i > 7)
	{
		i = 0;
		temp = 0x80;
	}
	
	/* Output and shifting */
	P1 = ~temp;
	temp >>= 1;
}


/**
  * @brief  LED Flashing from right to left
  * @param  None
  * @retval None
  */
void blink_right_to_left(void)
{
	/* Initialize variables */
	static unsigned char i = 0;
	static unsigned char temp = 0x01;
	
	/* Variable increase and prevent cross-border */
	if(++i > 7)
	{
		i = 0;
		temp = 0x01;
	}
	
	/* Output and shifting */
	P1 = ~temp;
	temp <<= 1;
}


/**
  * @brief  LED Flashing from inside to outside
  * @param  None
  * @retval None
  */
void blink_inside_to_outside(void)
{
	/* Initialize variables */
	static unsigned char i = 0;
	static unsigned char temp_1 = 0x08;
	static unsigned char temp_2 = 0x10;
	
	/* Output and shifting */
	P1 = ~((temp_2 << i) | (temp_1 >> i));
	
	/* Variable increase and prevent cross-border */
	if(++i > 3)
	{
		i = 0;
		temp_1 = 0x08;
		temp_2 = 0x10;
	}
}


/**
  * @brief  LED Flashing from outside to inside
  * @param  None
  * @retval None
  */
void blink_outside_to_inside(void)
{
	/* Initialize variables */
	static unsigned char i = 0;
	static unsigned char temp_1 = 0x01;
	static unsigned char temp_2 = 0x80;
	
	/* Output and shifting */
	P1 = ~((temp_2 >> i) | (temp_1 <<i));
	
	/* Variable increase and prevent cross-border */
	if(++i > 3)
	{
		i = 0;
		temp_1 = 0x01;
		temp_2 = 0x80;
	}
}


/**
  * @brief  According to the mode to determine the LED flashing mode
  * @param  None
  * @retval None
  */
void led_mode_handle(en_led_mode mode)
{
	/* Initialize variables */
	static unsigned char i;
	
	if(++i > 200)
		i = 1;
	
	switch(mode)
	{
		case LED_MODE_0:	//MODE0
			break;					//None
		
		case LED_MODE_1:	//MODE1
			blink_left_to_right();	//LED Flashing from left to right
			break;
		
		case LED_MODE_2:	//MODE2
			blink_right_to_left();	//LED Flashing from right to left
			break;
		
		case LED_MODE_3:	//MODE3
			if(i%2)
				blink_inside_to_outside();	//LED Flashing from inside to outside
			break;
		
		case LED_MODE_4:	//MODE4
			if(i%2)
				blink_outside_to_inside();	//LED Flashing from outside to inside
			break;
		
		default:					//Other
			P1 = 0xff;			//LED all exterminate
			break;
	}
}








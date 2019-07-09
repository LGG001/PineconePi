/**
  ******************************************************************************
  * @file    main.c 
  * @author  LGG
  * @version V1.0.0
  * @date    09-July-2019
  * @brief   Realize the function of eight of flowing water light.
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "PineconePinano.h"
#include "Intrins.h"


/* Define LED enable bit */
sbit LED_Enable = P5^5;


/* Declare function */
void Delay_Ms(unsigned short ms);


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main()
{
	/* Define variable for cycle show */
	unsigned char temp = 0x01;
	
	/* Enable LED control bit */
	LED_Enable = 0;
	
	/* loop */
	while(1)
	{
		do
		{
			P1 = ~temp;		
			Delay_Ms(500);
		}while(temp <<= 1);
		
		temp = 0x01;
	}
}


/**
  * @brief  Delay_Ms.
  * @param  ms: delay ms(ms)
  * @retval None
  */
void Delay_Ms(unsigned short ms)
{
	unsigned short k;
	unsigned char i, j;
	for(k = 0; k < ms; k++)
	{
		_nop_();
		i = 32;
		j = 40;
		do
		{
		  while (--j);
		} while (--i);
	}
}








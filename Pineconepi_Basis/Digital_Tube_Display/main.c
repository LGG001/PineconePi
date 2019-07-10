/**
  ******************************************************************************
  * @file    main.c 
  * @author  LGG
  * @version V1.0.0
  * @date    10-July-2019
  * @brief   Digital tube displays from 0 to 99.
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "PineconePinano.h"


/* Define status */
#define 	TRUE		1
#define		FALSE		0


/* Define diaplay truth-value */
unsigned char Segment_num[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


/* Define correlation variables */
unsigned char number = 0;
unsigned char time_5ms = 0;
unsigned char time_1s = 0;


/* Define correlation falgs */
unsigned char flag_5ms = FALSE;
unsigned char flag_1s = FALSE;


/* Define bit */
sbit Seg1_Enable = P4^3;
sbit Seg2_Enable = P4^4;


/* Declare function */
void Segment_Display(void);


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main()
{
	/* Initialize P1 P4^3 P4^4 */
	P1M0 = 0xff;
	P1M1 = 0x00;
	P4M0 |= 0x30;
	P4M1 &= 0xcf;
	
	/* Initialize TIMER0 */
	TMOD = 0x00;
	TL0 = 0x2f;
	TH0 = 0xf8;
	ET0 = 1;
	EA = 1;
	TR0 = 1;
	
	/* loop */
	while(1)
	{
		/* Handle 5ms event */
		if(flag_5ms == TRUE)
		{
			flag_5ms = FALSE;
			Segment_Display();
		}
		
		/* Handle 1s event */
		if(flag_1s == TRUE)
		{
			flag_1s = FALSE;
			if(++number >99)
				number = 0;
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
	if(++time_5ms >= 5)
	{
		time_5ms = 0;
		flag_5ms = TRUE;
		
		/* Timing 1 s */
		if(++time_1s >= 200)
		{
			time_1s = 0;
			flag_1s = TRUE;
		}
	}
}


/**
  * @brief  Digital tube display fun
  * @param  None
  * @retval None
  */
void Segment_Display(void)
{
	static unsigned char temp = 0;
	
	if(++temp >= 200)
		temp = 0;
	
	/* Show units */
	if(temp % 2)
	{
		Seg2_Enable = 1;
		Seg1_Enable = 0;
		P1 = Segment_num[number%10];
	}
	/* Show tens */
	else
	{
		Seg1_Enable = 1;
		Seg2_Enable = 0;
		P1 = Segment_num[number/10];
	}
}

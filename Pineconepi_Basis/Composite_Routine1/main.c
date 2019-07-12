
#include "PineconePinano.h"
#include "button.h"
#include "led.h"


/* Define status */
#define 	TRUE		1
#define		FALSE		0


/* Define correlation variables */
unsigned char time_10ms = 0;
unsigned char time_100ms = 0;


/* Define correlation falgs */
unsigned char flag_10ms = FALSE;
unsigned char flag_100ms = FALSE;


void KEY_Process(key_value key_value);






void main()
{
	key_value temp;
	
	KEY_Init();
	LED_Init();
	
	/* Initialize TIMER0 */
	TMOD = 0x00;
	TL0 = 0x2f;
	TH0 = 0xf8;
	ET0 = 1;
	EA = 1;
	TR0 = 1;
	
	while(1)
	{
		/* Handle 5ms event */
		if(flag_10ms == TRUE)
		{
			flag_10ms = FALSE;
			temp = KEY_Scan();
			if(temp != NULL_Pressed)
				KEY_Process(temp);
		}
		
		if(flag_100ms == TRUE)
		{
			flag_100ms = FALSE;
			blink_inside_to_outside();
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
  * @������       KeyProcess
  * @��  ��       �����������ݼ�ֵ��ִ����Ӧ�Ĳ���
  * @��  ��       key_val����ֵ
  * @����ֵ       ��
  */
void KEY_Process(key_value key_value)
{
	switch(key_value)
	{
		case KEY1_Pressed:					//KEY1���£��̰���
			P10 = !P10;
			break;

		case KEY2_Pressed:					//KEY2���£��̰���
			P11 = 0;
			break;
			
		case KEY3_Pressed:					//KEY3���£��̰���
			P12 = 0;
			break;
			
		case KEY4_Pressed:					//KEY4���£��̰��� 
			P13 = 0;
			break;
			
			
		case KEY1_LongPressed:					//KEY1����
			P10 = 1;
			break;
			
		case KEY2_LongPressed:					//KEY2����
			P11 = !P11;
			break;
			
		case KEY3_LongPressed:					//KEY3����
			P12 = 1;
			break;
			
		case KEY4_LongPressed:					//KEY4����
			P13 = 1;
			break;
			

		default:								//����
			break;
	}
}



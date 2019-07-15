/**
  ******************************************************************************
  * @file    led.h 
  * @author  LGG
  * @version V1.0.0
  * @date    15-July-2019
  * @brief   This file contains the headers of led handlers.
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H


/* Includes ------------------------------------------------------------------*/
#include "PineconePinano.h"


/* Define LED mode enum */
typedef enum{
	LED_MODE_0 = 0,
	LED_MODE_1,
	LED_MODE_2,
	LED_MODE_3,
	LED_MODE_4,
}en_led_mode;


/* Exported functions ------------------------------------------------------- */
void LED_Init(void);
void blink_left_to_right(void);
void blink_right_to_left(void);
void blink_inside_to_outside(void);
void blink_outside_to_inside(void);
void led_mode_handle(en_led_mode mode);

#endif




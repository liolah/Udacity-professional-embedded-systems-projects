/*
 * led.h
 *
 * Created: 12/23/2022 12:16:38 AM
 *  Author: Hesham Hany
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO Driver/dio.h"

typedef enum EN_ledError_t
  {
  LED_OK, LED_ERROR_INIT, LED_ERROR_ON, LED_ERROR_OFF, LED_ERROR_TOGGLE
  } EN_ledError_t;

// Initialize the LED
EN_ledError_t LED_init(uint8_t ledport, uint8_t ledpin);

// Turn on the LED
EN_ledError_t LED_on(uint8_t ledport, uint8_t ledpin);

// Turn off the LED
EN_ledError_t LED_off(uint8_t ledport, uint8_t ledpin);

// Toggle the LED
EN_ledError_t LED_toggle(uint8_t ledport, uint8_t ledpin);

#endif /* LED_H_ */
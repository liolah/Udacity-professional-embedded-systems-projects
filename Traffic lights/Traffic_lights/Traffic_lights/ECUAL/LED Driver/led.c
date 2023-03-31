/*
 * led.c
 *
 * Created: 12/23/2022 12:16:53 AM
 *  Author: Hesham Hany
 */ 

#include "led.h"

 // Initialize the LED
EN_ledError_t LED_init(uint8_t ledport, uint8_t ledpin) {
  // Check if the dio was initialized correctly
  if (DIO_init(ledpin, ledport, OUT) == DIO_OK) {
    return LED_OK;
    }
  // Return error code to indicate that the led initialization failed
  return LED_ERROR_INIT;
  }

// Turn on the LED
EN_ledError_t LED_on(uint8_t ledport, uint8_t ledpin) {
  if (DIO_write(ledpin, ledport, HIGH) == DIO_OK) {
    return LED_OK;
    }
  // Return error code to indicate that attempting to turn on the led has failed
  return LED_ERROR_ON;
}

// Turn off the LED
EN_ledError_t LED_off(uint8_t ledport, uint8_t ledpin){
  if (DIO_write(ledpin, ledport, LOW) == DIO_OK) {
    return LED_OK;
    }
  // Return error code to indicate that attempting to turn off the led has failed
  return LED_ERROR_OFF;
}

// Toggle the LED
EN_ledError_t LED_toggle(uint8_t ledport, uint8_t ledpin){
  if (DIO_toggle(ledpin, ledport) == DIO_OK) {
    return LED_OK;
    }
  // Return error code to indicate that attempting to toggle the led has failed
  return LED_ERROR_TOGGLE;
}
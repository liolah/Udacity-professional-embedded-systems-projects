/*
 * button.c
 *
 * Created: 12/23/2022 12:17:16 AM
 *  Author: Hesham Hany
 */ 

#include "button.h"

 // Initialize the button
EN_buttonError_t BUTTON_init(uint8_t buttonPort, uint8_t buttonPin) {
  // Check if the button initialization was successful
  if (DIO_init(buttonPin, buttonPort, IN) == DIO_OK) {
    // Return a code indicating that the button initialization was successful
    return BUTTON_OK;
    }
  // Return an error code indicating that the button initialization has failed
  return BUTTON_ERROR_INIT;
  }

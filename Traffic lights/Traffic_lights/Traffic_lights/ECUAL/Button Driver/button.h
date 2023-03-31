/*
 * button.h
 *
 * Created: 12/23/2022 12:17:03 AM
 *  Author: Hesham Hany
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO Driver/dio.h"

#define EXTERNAL_INT_BUTTON_PORT PORT_D
#define EXTERNAL_INT_BUTTON_PIN   2

typedef enum EN_buttonError_t
  {
  BUTTON_OK, BUTTON_ERROR_INIT
  } EN_buttonError_t;

// Initialize the button
EN_buttonError_t BUTTON_init(uint8_t buttonPort, uint8_t buttonPin);

#endif /* BUTTON_H_ */
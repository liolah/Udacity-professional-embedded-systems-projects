/*
 * dio.c
 *
 * Created: 12/23/2022 12:16:12 AM
 *  Author: Hesham Hany
 */

#include "dio.h"

 // Initialize the pin direction
EN_dioError_t DIO_init(uint8_t pinNumber, uint8_t portNumber, uint8_t direction) {
  // Validate the pin number
  if (pinNumber > 7) {
    return WRONG_PIN;
    }
  // Validate the port number
  if (portNumber != PORT_A && portNumber != PORT_B && portNumber != PORT_C && portNumber != PORT_D) {
    return WRONG_PORT;
    }
  // Validate the direction
  if (direction != IN && direction != OUT) {
    return WRONG_DIRECTION;
    }
  switch (portNumber) {
      case PORT_A:
        if (direction == OUT) {
          set_bit(DDRA, pinNumber);
          }
        else {
          clear_bit(DDRA, pinNumber);
          }
        break;
      case PORT_B:
        if (direction == OUT) {
          set_bit(DDRB, pinNumber);
          }
        else {
          clear_bit(DDRB, pinNumber);
          }
        break;
      case PORT_C:
        if (direction == OUT) {
          set_bit(DDRC, pinNumber);
          }
        else {
          clear_bit(DDRC, pinNumber);
          }
        break;
      case PORT_D:
        if (direction == OUT) {
          set_bit(DDRD, pinNumber);
          }
        else {
          clear_bit(DDRD, pinNumber);
          }
        break;
    }
  return DIO_OK;
  }

// Write a value to a pin
EN_dioError_t DIO_write(uint8_t pinNumber, uint8_t portNumber, uint8_t state) {
  // Validate the pin number
  if (pinNumber > 7) {
    return WRONG_PIN;
    }
  // Validate the port number
  if (portNumber != PORT_A && portNumber != PORT_B && portNumber != PORT_C && portNumber != PORT_D) {
    return WRONG_PORT;
    }
  // Validate the pin state
  if (state != HIGH && state != LOW) {
    return WRONG_STATE;
    }
  switch (portNumber) {
      case PORT_A:
        if (state == HIGH) {
          set_bit(PORTA, pinNumber);
          }
        else {
          clear_bit(PORTA, pinNumber);
          }
        break;
      case PORT_B:
        if (state == HIGH) {
          set_bit(PORTB, pinNumber);
          }
        else {
          clear_bit(PORTB, pinNumber);
          }
        break;
      case PORT_C:
        if (state == HIGH) {
          set_bit(PORTC, pinNumber);
          }
        else {
          clear_bit(PORTC, pinNumber);
          }
        break;
      case PORT_D:
        if (state == HIGH) {
          set_bit(PORTD, pinNumber);
          }
        else {
          clear_bit(PORTD, pinNumber);
          }
        break;
    }
  return DIO_OK;
  }

// Toggle a pin
EN_dioError_t DIO_toggle(uint8_t pinNumber, uint8_t portNumber) {
  // Validate the pin number
  if (pinNumber > 7) {
    return WRONG_PIN;
    }
  // Validate the port number
  if (portNumber != PORT_A && portNumber != PORT_B && portNumber != PORT_C && portNumber != PORT_D) {
    return WRONG_PORT;
    }
  switch (portNumber) {
      case PORT_A:
          toggle_bit(PORTA, pinNumber);
        break;
      case PORT_B:
          toggle_bit(PORTB, pinNumber);
        break;
      case PORT_C:
          toggle_bit(PORTC, pinNumber);
        break;
      case PORT_D:
          toggle_bit(PORTD, pinNumber);
        break;
    }
  return DIO_OK;
  }
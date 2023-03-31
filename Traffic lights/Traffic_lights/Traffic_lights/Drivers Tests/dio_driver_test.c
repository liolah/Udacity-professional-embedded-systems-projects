/*
 * dio_driver_test.c
 *
 * Created: 12/26/2022 5:33:40 PM
 *  Author: Hesham Hany
 */ 

#include "dio_driver_test.h"

#define CORRECT_PIN 1
#define CORRECT_PORT 'A'
#define CORRECT_DIRECTION 1
#define CORRECT_STATE 1

#define WRONG__PIN 10
#define WRONG__PORT 'X'
#define WRONG__DIRECTION 2
#define WRONG__STATE 3


// Contains tests for the dio driver
void DIO_test(void) {
  // response1 should be 0 (DIO_OK)
  uint8_t response1 = DIO_init(CORRECT_PIN, CORRECT_PORT, CORRECT_DIRECTION);
  // response2 should be 0 (DIO_OK)
  uint8_t response2 = DIO_write(CORRECT_PIN, CORRECT_PORT, CORRECT_STATE);
  // response3 should be 0 (DIO_OK)
  uint8_t response3 = DIO_toggle(CORRECT_PIN, CORRECT_PORT);
  // --------------------------------------------------------------- Error Codes ------------------------------------------------------
  // response4 should be 1 (WRONG_PIN)
  uint8_t response4 = DIO_init(WRONG__PIN, CORRECT_PORT, CORRECT_DIRECTION);
  // response5 should be 2 (WRONG_PORT)
  uint8_t response5 = DIO_init(CORRECT_PIN, WRONG__PORT, CORRECT_DIRECTION);
  // response6 should be 3 (WRONG_DIRECTION)
  uint8_t response6 = DIO_init(CORRECT_PIN, CORRECT_PORT, WRONG__DIRECTION);
  // response7 should be 1 (WRONG_PIN)
  uint8_t response7 = DIO_write(WRONG__PIN, CORRECT_PORT, CORRECT_DIRECTION);
  // response8 should be 2 (WRONG_PORT)
  uint8_t response8 = DIO_write(CORRECT_PIN, WRONG__PORT, CORRECT_DIRECTION);
  // response9 should be 4 (WRONG_STATE)
  uint8_t response9 = DIO_write(CORRECT_PIN, CORRECT_PORT, WRONG__STATE);
  // response10 should be 1 (WRONG_PIN)
  uint8_t response10 = DIO_toggle(WRONG__PIN, CORRECT_PORT);
  // response11 should be 2 (WRONG_PORT)
  uint8_t response11 = DIO_toggle(CORRECT_PIN, WRONG__PORT);

  // Must be 11
  uint8_t numberOfCorrectResponses = (response1 == DIO_OK) + (response2 == DIO_OK) + (response3 == DIO_OK) + (response4 == WRONG_PIN) + (response5 == WRONG_PORT) + (response6 == WRONG_DIRECTION) + (response7 == WRONG_PIN) + (response8 == WRONG_PORT) + (response9 == WRONG_STATE) + (response10 == WRONG_PIN) + (response11 == WRONG_PORT);

  // Show the number of correct test cases as the value in DDRB :). If I don't use this line the compiler will optimize the code along with the unused variables. 
  // And will not be able to get the memory locations or the values of the variables. 
  DDRB = numberOfCorrectResponses;
  }
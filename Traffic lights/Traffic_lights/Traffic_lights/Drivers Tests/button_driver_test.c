/*
 * button_driver_test.c
 *
 * Created: 12/26/2022 5:33:07 PM
 *  Author: Hesham Hany
 */

#include "button_driver_test.h"

#define CORRECT_PIN 1
#define CORRECT_PORT 'A'

#define WRONG__PIN 10

 // Contains tests for the button driver
void BUTTON_test(void) {
  // response1 should be 0 (BUTTON_OK)
  uint8_t response1 = BUTTON_init(CORRECT_PORT, CORRECT_PIN);
  // response2 should be 1 (BUTTON_ERROR_INIT)
  uint8_t response2 = BUTTON_init(CORRECT_PORT, WRONG__PIN);

  // Must be 2
  uint8_t numberOfCorrectResponses = (response1 == BUTTON_OK) + (response2 == BUTTON_ERROR_INIT);

  // Show the number of correct test cases as the value in DDRB :). If I don't use this line the compiler will optimize the code along with the unused variables. 
  // And will not be able to get the memory locations or the values of the variables. 
  DDRB = numberOfCorrectResponses;
  }
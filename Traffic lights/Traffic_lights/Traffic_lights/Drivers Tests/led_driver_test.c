/*
 * led_driver_test.c
 *
 * Created: 12/26/2022 5:31:59 PM
 *  Author: Hesham Hany
 */

#include "led_driver_test.h"

#define CORRECT_PIN 1
#define CORRECT_PORT 'A'

#define WRONG__PORT 'X'

 // Contains tests for the led driver
void LED_test(void) {
  // response1 should be 0 (LED_OK)
  uint8_t response1 = LED_init(CORRECT_PORT, CORRECT_PIN);
  // response2 should be 0 (LED_OK)
  uint8_t response2 = LED_on(CORRECT_PORT, CORRECT_PIN);
  // response3 should be 0 (LED_OK)
  uint8_t response3 = LED_off(CORRECT_PORT, CORRECT_PIN);
  // response4 should be 0 (LED_OK)
  uint8_t response4 = LED_toggle(CORRECT_PORT, CORRECT_PIN);
  // --------------------------------------------------------------- Error Codes ------------------------------------------------------
  // response5 should be 2 (LED_ERROR_INIT)
  uint8_t response5 = LED_init(WRONG__PORT, CORRECT_PIN);
  // response6 should be 3 (LED_ERROR_ON)
  uint8_t response6 = LED_on(WRONG__PORT, CORRECT_PIN);
  // response7 should be 1 (LED_ERROR_OFF)
  uint8_t response7 = LED_off(WRONG__PORT, CORRECT_PIN);
  // response8 should be 2 (LED_ERROR_TOGGLE)
  uint8_t response8 = LED_toggle(WRONG__PORT, CORRECT_PIN);

  // Must be 8
  uint8_t numberOfCorrectResponses = (response1 == LED_OK) + (response2 == LED_OK) + (response3 == LED_OK) + (response4 == LED_OK) + (response5 == LED_ERROR_INIT) + (response6 == LED_ERROR_ON) + (response7 == LED_ERROR_OFF) + (response8 == LED_ERROR_TOGGLE);

  // Show the number of correct test cases as the value in DDRB :). If I don't use this line the compiler will optimize the code along with the unused variables. 
  // And will not be able to get the memory locations or the values of the variables. 
  DDRB = numberOfCorrectResponses;
  }
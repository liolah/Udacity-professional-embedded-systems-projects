/*
 * timer_driver_test.c
 *
 * Created: 12/26/2022 5:34:01 PM
 *  Author: Hesham Hany
 */

#include "timer_driver_test.h"

#define CORRECT_TIMER_NUMBER 1
#define CORRECT_COMPARE_VALUE 250

#define WRONG_TIMER_NUMBER 5
#define WRONG_COMPARE_VALUE 2500

bool test_temp = false;

// Contains tests for the timer driver
void TIMER_test(void) {
  // response1 should be 0 (TIMER_OK)
  uint8_t response1 = TIMERn_CTC_init(CORRECT_TIMER_NUMBER, CORRECT_COMPARE_VALUE);
  // response2 should be 0 (TIMER_OK)
  uint8_t response2 = TIMERn_start(CORRECT_TIMER_NUMBER);
  // response3 should be 0 (TIMER_OK)
  uint8_t response3 = TIMERn_stop(CORRECT_TIMER_NUMBER);
  // response4 should be 0 (TIMER_OK)
  uint8_t response4 = TIMERn_reset(CORRECT_TIMER_NUMBER);
  // response5 should be 0 (TIMER_OK)
  uint8_t response5 = TIMERn_read_and_reset_OCF(CORRECT_TIMER_NUMBER, &test_temp);
  // --------------------------------------------------------------- Error Codes ------------------------------------------------------
  // response6 should be 1 (WRONG_TIMER)
  uint8_t response6 = TIMERn_CTC_init(WRONG_TIMER_NUMBER, CORRECT_COMPARE_VALUE);
  // response7 should be 1 (WRONG_TIMER)
  uint8_t response7 = TIMERn_start(WRONG_TIMER_NUMBER);
  // response8 should be 1 (WRONG_TIMER)
  uint8_t response8 = TIMERn_stop(WRONG_TIMER_NUMBER);
  // response9 should be 1 (WRONG_TIMER)
  uint8_t response9 = TIMERn_reset(WRONG_TIMER_NUMBER);
  // response10 should be 1 (WRONG_TIMER)
  uint8_t response10 = TIMERn_read_and_reset_OCF(WRONG_TIMER_NUMBER, &test_temp);
  // response11 should be 2 (ERROR_TIMER_OCR_OVERFLOW)
  uint8_t response11 = TIMERn_CTC_init(CORRECT_TIMER_NUMBER, WRONG_COMPARE_VALUE);

  // Must be 11
  uint8_t numberOfCorrectResponses = (response1 == TIMER_OK) + (response2 == TIMER_OK) + (response3 == TIMER_OK) + (response4 == TIMER_OK) + (response5 == TIMER_OK) + (response6 == WRONG_TIMER) + (response7 == WRONG_TIMER) + (response8 == WRONG_TIMER) + (response9 == WRONG_TIMER) + (response10 == WRONG_TIMER) + (response11 == ERROR_TIMER_OCR_OVERFLOW);

  // Show the number of correct test cases as the value in DDRB :). If I don't use this line the compiler will optimize the code along with the unused variables. 
  // And will not be able to get the memory locations or the values of the variables. 
  DDRB = numberOfCorrectResponses;
  }
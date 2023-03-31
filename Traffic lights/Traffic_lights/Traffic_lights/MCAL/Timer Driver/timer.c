/*
 * timer.c
 *
 * Created: 12/24/2022 1:04:23 AM
 *  Author: Hesham Hany
 */

#include "timer.h"

 // Initialize the timers to start in CTC mode
EN_timerError_t TIMERn_CTC_init(uint8_t timerNumber, uint16_t compareValue) {
  // Validate the timer number
  if (timerNumber != TIMER_0 && timerNumber != TIMER_1 && timerNumber != TIMER_2) {
    return WRONG_TIMER;
    }
  // Check if the compare value is too large for the timer's OCR
  if (timerNumber == TIMER_0 || timerNumber == TIMER_2) {
    if (compareValue > 255)
      return ERROR_TIMER_OCR_OVERFLOW;
    }
  switch (timerNumber) {
      case TIMER_0:
        // Set the timer mode to CTC
        set_bit(TCCR0, WGM01);
        clear_bit(TCCR0, WGM00);
        // Reset the value in TCNT register. It's probably zero but just to make sure.
        TCNT0 = 0;
        // Set the OCR to the calculated value
        OCR0 = (uint8_t)compareValue;
        break;
      case TIMER_1:
        // Set the timer mode to CTC
        clear_bit(TCCR1A, WGM10);
        clear_bit(TCCR1A, WGM11);
        set_bit(TCCR1B, WGM12);
        clear_bit(TCCR1B, WGM13);
        // Reset the value in TCNT register.
        TCNT1 = 0;
        // Set the OCR to the calculated value
        OCR1A = compareValue;
        break;
      case TIMER_2:
        // Set the timer mode to CTC
        set_bit(TCCR2, WGM21);
        clear_bit(TCCR2, WGM20);
        // Reset the value in TCNT register.
        TCNT2 = 0;
        // Set the OCR to the calculated value
        OCR2 = (uint8_t)compareValue;
        break;
    }
  // Everything went well
  return TIMER_OK;
  }

// Start the timer
EN_timerError_t TIMERn_start(uint8_t timerNumber) {
  // Validate the timer number
  if (timerNumber != TIMER_0 && timerNumber != TIMER_1 && timerNumber != TIMER_2) {
    return WRONG_TIMER;
    }
  switch (timerNumber) {
      case TIMER_0:
        // Set the clock source to prescaler: clk/1024 to start the timer 
        set_bit(TCCR0, CS02);
        clear_bit(TCCR0, CS01);
        set_bit(TCCR0, CS00);
        break;
      case TIMER_1:
        // Set the clock source to prescaler: clk/8 to start the timer 
        clear_bit(TCCR1B, CS10);
        set_bit(TCCR1B, CS11);
        clear_bit(TCCR1B, CS12);
        break;
      case TIMER_2:
        // Set the clock source to prescaler: clk/1024 to start the timer 
        set_bit(TCCR2, CS20);
        set_bit(TCCR2, CS21);
        set_bit(TCCR2, CS22);
        break;
    }
  // Everything went well
  return TIMER_OK;
  }

// Stop the timer
EN_timerError_t TIMERn_stop(uint8_t timerNumber) {
  // Validate the timer number
  if (timerNumber != TIMER_0 && timerNumber != TIMER_1 && timerNumber != TIMER_2) {
    return WRONG_TIMER;
    }
  switch (timerNumber) {
      case TIMER_0:
        // Set the clock source to "no clock source" to stop the timer 
        clear_bit(TCCR0, CS02);
        clear_bit(TCCR0, CS01);
        clear_bit(TCCR0, CS00);
        break;
      case TIMER_1:
        // Set the clock source to "no clock source" to stop the timer 
        clear_bit(TCCR1B, CS10);
        clear_bit(TCCR1B, CS11);
        clear_bit(TCCR1B, CS12);
        break;
      case TIMER_2:
        // Set the clock source to "no clock source" to stop the timer 
        clear_bit(TCCR2, CS20);
        clear_bit(TCCR2, CS21);
        clear_bit(TCCR2, CS22);
        break;
    }
  // Everything went well
  return TIMER_OK;
  }

// Reset the timer
// The timers are reset by setting the value of TCNT to zero
EN_timerError_t TIMERn_reset(uint8_t timerNumber) {
  // Validate the timer number
  if (timerNumber != TIMER_0 && timerNumber != TIMER_1 && timerNumber != TIMER_2) {
    return WRONG_TIMER;
    }
  switch (timerNumber) {
      case TIMER_0:
        TCNT0 = 0;
        break;
      case TIMER_1:
        TCNT1 = 0;
        break;
      case TIMER_2:
        TCNT2 = 0;
        break;
    }
  // Everything went well
  return TIMER_OK;
  }

// Check if the timer's OCF is set and reset the flag if set. Returns true if the flag is set.
EN_timerError_t TIMERn_read_and_reset_OCF(uint8_t timerNumber, bool* flag) {
  // Validate the timer number
  if (timerNumber != TIMER_0 && timerNumber != TIMER_1 && timerNumber != TIMER_2) {
    return WRONG_TIMER;
    }
  switch (timerNumber) {
      case TIMER_0:
        // If the OCF bit is set that means a compare match has occurred. 
        if (read_bit(TIFR, OCF0) == 1) {
          // Reset the flag
          set_bit(TIFR, OCF0);
          *flag = true;
          }
        else {
          *flag = false;
          }
        break;
      case TIMER_1:
        if (read_bit(TIFR, OCF1A) == 1) {
          set_bit(TIFR, OCF1A);
          *flag = true;
          }
        else {
          *flag = false;
          }
        break;
      case TIMER_2:
        if (read_bit(TIFR, OCF2) == 1) {
          set_bit(TIFR, OCF2);
          *flag = true;
          }
        else {
          *flag = false;
          }
        break;
    }
  // Everything went well
  return TIMER_OK;
  }
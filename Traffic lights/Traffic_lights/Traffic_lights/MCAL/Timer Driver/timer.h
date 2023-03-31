/*
 * timers.h
 *
 * Created: 12/23/2022 8:39:07 PM
 *  Author: Hesham Hany
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include <stdbool.h>
#include "../../Utilities/types.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"

#define TIMER_0 1
#define TIMER_1 2
#define TIMER_2 3

typedef enum EN_timerError_t
  {
  TIMER_OK, WRONG_TIMER, ERROR_TIMER_OCR_OVERFLOW
  } EN_timerError_t;

// Initialize the timers to start in CTC mode
EN_timerError_t TIMERn_CTC_init(uint8_t timerNumber, uint16_t compareValue);

// Start the timer
EN_timerError_t TIMERn_start(uint8_t timerNumber);

// Stop the timer
EN_timerError_t TIMERn_stop(uint8_t timerNumber);

// Reset the timer
EN_timerError_t TIMERn_reset(uint8_t timerNumber);

// Check if the timer's OCF is set and reset the flag if set
EN_timerError_t TIMERn_read_and_reset_OCF(uint8_t timerNumber, bool* flag);

#endif /* TIMERS_H_ */
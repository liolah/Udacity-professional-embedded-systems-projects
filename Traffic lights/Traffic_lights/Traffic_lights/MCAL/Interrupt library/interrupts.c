/*
 * interrupts.c
 *
 * Created: 12/24/2022 6:02:16 PM
 *  Author: Hesham Hany
 */ 

#include "interrupts.h"

void INT0_init() {
  // Any logical change on INT0 generates an interrupt request
  set_bit(MCUCR, ISC00);
  clear_bit(MCUCR, ISC01);
  // Enabling interrupts on INT0
  set_bit(GICR, INT0);
  }
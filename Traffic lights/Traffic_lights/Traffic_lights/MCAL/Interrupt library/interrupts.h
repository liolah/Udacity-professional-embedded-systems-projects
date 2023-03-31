/*
 * interrupts.h
 *
 * Created: 12/23/2022 12:19:43 AM
 *  Author: Hesham Hany
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"
// *********************************************************
// Interrupt vectors
// *********************************************************
/* External Interrupt Request 0 */
#define INT0_vect __vector_1

#define sei() __asm__ __volatile__ ("sei" ::: "memory")
#define cli() __asm__ __volatile__ ("cli" ::: "memory")

#define ISR(INT_VECT)\
        void INT_VECT(void) __attribute__ ((signal, used));\
        void INT_VECT(void)

void INT0_init();

#endif /* INTERRUPTS_H_ */
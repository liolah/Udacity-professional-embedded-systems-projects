/*
 * bit_manipulation.h
 *
 * Created: 12/23/2022 12:20:27 AM
 *  Author: Hesham Hany
 */ 


#ifndef BIT_MANIPULATION_H_
#define BIT_MANIPULATION_H_

#define set_bit(port, pinNumber) port |= (1 << pinNumber)
#define clear_bit(port, pinNumber)  port &= ~(1 << pinNumber)
#define toggle_bit(port, pinNumber) port ^= (1 << pinNumber)
#define read_bit(port, pinNumber) ((port & (1 << pinNumber)) >> pinNumber)

#endif /* BIT_MANIPULATION_H_ */
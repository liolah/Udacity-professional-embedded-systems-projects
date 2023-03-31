/*
 * application.h
 *
 * Created: 12/22/2022 8:32:04 PM
 *  Author: Hesham Hany
 */


#ifndef APPLICATION_H_
#define APPLICATION_H_

// Headers required for the code to run
#include <stdbool.h>
#include "../ECUAL/LED Driver/led.h"
#include "../ECUAL/Button Driver/button.h"
#include "../MCAL/Timer Driver/timer.h"
#include "../MCAL/Interrupt library/interrupts.h"

// Test modules headers
#include "../Drivers Tests/dio_driver_test.h"
#include "../Drivers Tests/led_driver_test.h"
#include "../Drivers Tests/button_driver_test.h"
#include "../Drivers Tests/timer_driver_test.h"

#define CARS_GREEN_LED_PORT   'A'
#define CARS_GREEN_LED_PIN     0
#define CARS_YELLOW_LED_PORT  'A'
#define CARS_YELLOW_LED_PIN    1
#define CARS_RED_LED_PORT     'A'
#define CARS_RED_LED_PIN       2

#define PEDESTRIANS_GREEN_LED_PORT   'B'
#define PEDESTRIANS_GREEN_LED_PIN     0
#define PEDESTRIANS_YELLOW_LED_PORT  'B'
#define PEDESTRIANS_YELLOW_LED_PIN    1
#define PEDESTRIANS_RED_LED_PORT     'B'
#define PEDESTRIANS_RED_LED_PIN       2

#define BUTTON_PORT     'D'
#define BUTTON_PIN       2

#define LONG_PRESS_TIMER_MAX_COUNT  3
#define LIGHT_PHASE_TIMER_MAX_COUNT 9
#define BLINK_TIMER_MAX_COUNT       1

 // Initialize the entities required in the app
void App_init();

// Start the app
void App_start();

#endif /* APPLICATION_H_ */
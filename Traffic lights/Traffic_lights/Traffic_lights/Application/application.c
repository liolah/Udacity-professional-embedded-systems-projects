/*
 * application.c
 *
 * Created: 12/22/2022 8:32:26 PM
 *  Author: Hesham Hany
 */

#include "application.h"

 // Flag to check wether the active mode is the pedestrian mode or the cars mode
bool pedestrians_mode = false;
// Flag to check for long button presses and ignore them
bool short_press = false;
// Flag to check if the button state changed from pressed to released and vice versa
bool button_pressed = false;
// Counter to set the active lights in both modes
uint8_t light_phase = 0;
// Counters to extend the timer durations 
uint8_t blink_counter = 0;
uint8_t light_phase_counter = 0;
uint8_t long_press_counter = 0;
// Flag to check and toggle the yellow light state in the traffic lights
bool yellow_light_toggle = true;
// Transition flag to indicate the transition from light phase to another
bool light_state_change = true;
// Flag to indicate the end of the pedestrian mode
bool exit_pedestrian_mode = false;
// Variable used to check if the timer's OCF is set
bool OCF_set = false;

// Initialize the entities required in the app
void App_init() {
  // Initialize the LEDS
  // Cars LEDS
  LED_init(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN);
  LED_init(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
  LED_init(CARS_RED_LED_PORT, CARS_RED_LED_PIN);
  // Pedestrians LEDS
  LED_init(PEDESTRIANS_GREEN_LED_PORT, PEDESTRIANS_GREEN_LED_PIN);
  LED_init(PEDESTRIANS_YELLOW_LED_PORT, PEDESTRIANS_YELLOW_LED_PIN);
  LED_init(PEDESTRIANS_RED_LED_PORT, PEDESTRIANS_RED_LED_PIN);
  // Turn on the pedestrians' red led
  LED_on(PEDESTRIANS_RED_LED_PORT, PEDESTRIANS_RED_LED_PIN);

  // Initialize the INT0 pin and the button on it
  INT0_init();
  BUTTON_init(BUTTON_PORT, BUTTON_PIN);

  // Enable global interrupts
  sei();

  // Initialize the timers
  TIMERn_CTC_init(TIMER_0, 163);   // Calls the interrupt to toggle the yellow led in its phase. (with every two counts)
  TIMERn_CTC_init(TIMER_1, 62500);  // .5 Seconds exactly pass with each compare match. 10 matches are needed for 5 seconds. Used to change the light phase
  TIMERn_CTC_init(TIMER_2, 245);   // Used to detect long presses. A press is considered long if it lasts more than one seconds(about 4 counts).  

  // Start timer 1
  TIMERn_start(TIMER_1);
  }

// Start the app
void App_start() {
  // ----------------------------------------------------------------- Timers polling --------------------------------------
  // Check the timers, update the counts, and reset the flags
  // The case of output compare match reached in timer 0
    TIMERn_read_and_reset_OCF(TIMER_0, &OCF_set);
    if (OCF_set) {
    if (blink_counter >= BLINK_TIMER_MAX_COUNT) {
      blink_counter = 0; // Reset the counter
      yellow_light_toggle = true; // Toggle the yellow led blink flag
      }
    else {
      blink_counter++;
      }
    }
  // The case of output compare match reached in timer 1
    TIMERn_read_and_reset_OCF(TIMER_1, &OCF_set);
    if (OCF_set) {
    if (light_phase_counter >= LIGHT_PHASE_TIMER_MAX_COUNT) {
      light_phase_counter = 0; // Reset the counter
      light_phase = (light_phase + 1) % 4; // Move to the next light phase
      light_state_change = true;
      }
    else {
      light_phase_counter++;
      }
    }
  // The case of output compare match reached in timer 2
    TIMERn_read_and_reset_OCF(TIMER_2, &OCF_set);
    if (OCF_set) {
    if (long_press_counter >= LONG_PRESS_TIMER_MAX_COUNT) {
      long_press_counter = 0; // Reset the counter
      short_press = false; // Indicate that the press was longer than it should be
      }
    else {
      long_press_counter++;
      }
    }
  // -------------------------------------------------------------------- Traffic lights logic -------------------------------------------
  // Pedestrians mode active
  if (pedestrians_mode) {
    // disable the global interrupts to ignore multiple button presses
    cli();
    switch (light_phase) {
        case 0:   // The button was pressed while the cars' green light was on
          if (light_state_change) { // The first time the code cycles through this color
            // Turn on the pedestrians' red led and turn off the others
            LED_off(PEDESTRIANS_GREEN_LED_PORT, PEDESTRIANS_GREEN_LED_PIN);
            LED_off(PEDESTRIANS_YELLOW_LED_PORT, PEDESTRIANS_YELLOW_LED_PIN);
            LED_on(PEDESTRIANS_RED_LED_PORT, PEDESTRIANS_RED_LED_PIN);
            // Turn on the cars' green led and turn off the others
            LED_on(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN);
            LED_off(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
            LED_off(CARS_RED_LED_PORT, CARS_RED_LED_PIN);
            light_state_change = false;
            // Stop the yellow led blink timer in case it was the previous phase
            TIMERn_stop(TIMER_0);
            // If the cycle is completed exit the pedestrian mode and reset the flags to go back to normal mode
            if (exit_pedestrian_mode) {
              exit_pedestrian_mode = false;
              pedestrians_mode = false;
              // Enable the global interrupts again before going back to normal mode
              sei();
              }
            }
          break;
        case 1:  // The button was pressed while the cars' yellow light was on
          if (light_state_change) { // The first time the code cycles through this color
            // Turn on the cars' yellow led and turn off the others
            LED_off(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN);
            LED_on(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
            LED_off(CARS_RED_LED_PORT, CARS_RED_LED_PIN);
            // Turn on the pedestrians' yellow led and turn off the others
            LED_off(PEDESTRIANS_GREEN_LED_PORT, PEDESTRIANS_GREEN_LED_PIN);
            LED_on(PEDESTRIANS_YELLOW_LED_PORT, PEDESTRIANS_YELLOW_LED_PIN);
            LED_on(PEDESTRIANS_RED_LED_PORT, PEDESTRIANS_RED_LED_PIN);
            yellow_light_toggle = false;
            light_state_change = false;
            blink_counter = 0;
            TIMERn_reset(TIMER_0);
            TIMERn_start(TIMER_0);
            exit_pedestrian_mode = true;
            }
          else {
            if (yellow_light_toggle) {
              // Toggle the cars and pedestrians' yellow leds
              LED_toggle(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
              LED_toggle(PEDESTRIANS_YELLOW_LED_PORT, PEDESTRIANS_YELLOW_LED_PIN);
              yellow_light_toggle = false;
              }
            }
          break;
        case 3:
          if (light_state_change) { // The first time the code cycles through this color
            // Turn on the cars' yellow led and turn off the others
            LED_off(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN);
            LED_on(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
            LED_off(CARS_RED_LED_PORT, CARS_RED_LED_PIN);
            // Turn on the pedestrians' yellow led and turn off the others
            LED_on(PEDESTRIANS_GREEN_LED_PORT, PEDESTRIANS_GREEN_LED_PIN);
            LED_on(PEDESTRIANS_YELLOW_LED_PORT, PEDESTRIANS_YELLOW_LED_PIN);
            LED_off(PEDESTRIANS_RED_LED_PORT, PEDESTRIANS_RED_LED_PIN);
            yellow_light_toggle = false;
            light_state_change = false;
            blink_counter = 0;
            TIMERn_reset(TIMER_0);
            TIMERn_start(TIMER_0);
            exit_pedestrian_mode = true;
            }
          else {
            if (yellow_light_toggle) {
              // Toggle the cars and pedestrians' yellow leds
              LED_toggle(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
              LED_toggle(PEDESTRIANS_YELLOW_LED_PORT, PEDESTRIANS_YELLOW_LED_PIN);
              yellow_light_toggle = false;
              }
            }
          break;
        case 2: // The button was pressed while the cars' red light was on
          if (light_state_change) { // The first time the code cycles through this color
            // Turn on the cars' red led and turn off the others
            LED_off(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN);
            LED_off(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
            LED_on(CARS_RED_LED_PORT, CARS_RED_LED_PIN);
            // Turn on the pedestrians' green led and turn off the others
            LED_on(PEDESTRIANS_GREEN_LED_PORT, PEDESTRIANS_GREEN_LED_PIN);
            LED_off(PEDESTRIANS_YELLOW_LED_PORT, PEDESTRIANS_YELLOW_LED_PIN);
            LED_off(PEDESTRIANS_RED_LED_PORT, PEDESTRIANS_RED_LED_PIN);
            light_state_change = false;
            TIMERn_stop(TIMER_0);
            }
          break;
      }
    }
  // --------------------------------------- Pedestrians mode end ---------------------------------------------
  else { // Normal mode active
    switch (light_phase) {
        case 0:  // Green light on
          if (light_state_change) { // The first time the code cycles through this color
            LED_on(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN);
            LED_off(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
            LED_off(CARS_RED_LED_PORT, CARS_RED_LED_PIN);
            light_state_change = false;
            TIMERn_stop(TIMER_0);
            }
          break;
        case 1:  // Yellow light on and blinking
        case 3:
          if (light_state_change) { // The first time the code cycles through this color
            LED_off(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN);
            LED_on(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
            LED_off(CARS_RED_LED_PORT, CARS_RED_LED_PIN);
            yellow_light_toggle = false;
            light_state_change = false;
            blink_counter = 0;
            TIMERn_reset(TIMER_0);
            TIMERn_start(TIMER_0);
            }
          else {
            if (yellow_light_toggle) {
              LED_toggle(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
              yellow_light_toggle = false;
              }
            }
          break;
        case 2:  // Red light on
          if (light_state_change) { // The first time the code cycles through this color
            LED_off(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN);
            LED_off(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
            LED_on(CARS_RED_LED_PORT, CARS_RED_LED_PIN);
            light_state_change = false;
            TIMERn_stop(TIMER_0);
            }
          break;
      }
    }
  }

// Button press interrupt handler. Gets called each time the logical state of the button is changed while the global interrupts are active
ISR(INT0_vect) {
  if (button_pressed && short_press) {  // If the button press was short
    pedestrians_mode = true;  // Set the pedestrian mode to start
    // If the cars' led is red or yellow reset the timer and its counter
    if (light_phase == 1 || light_phase == 2 || light_phase == 3) {
      light_phase_counter = 0;
      TIMERn_reset(TIMER_1);
      }
    // Adjust the light phase direction in case of the yellow led on
    if (light_phase == 3) {
      light_phase = 1;
      }
    light_state_change = true;
    // Reset the flags
    button_pressed = false;
    short_press = false;
    // Stop and reset the timer 
    TIMERn_stop(TIMER_2);
    TIMERn_reset(TIMER_2);
    long_press_counter = 0;
    }

  if (button_pressed && !short_press) {  // If the button press was long
    button_pressed = false;
    TIMERn_stop(TIMER_2);
    TIMERn_reset(TIMER_2);
    long_press_counter = 0;
    }

  if (!button_pressed) {  // Positive edge of the button press
    TIMERn_start(TIMER_2);
    button_pressed = true;
    short_press = true;
    }
  }
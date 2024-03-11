/**
 * @file Knowledge-Assessment-Question-2.cpp
 * @brief Button state monitoring with Doxygen comments.
 */

#include <Arduino.h>

#define BUTTON_PIN 2 // Define the pin connected to the button
#define PROTECTED_DURATION 10000 // Define the duration of the PROTECTED state (in milliseconds)

// Enumeration to represent button states
enum ButtonState {
  OFF,       /**< Button is in the OFF state */
  ON,        /**< Button is in the ON state */
  PROTECTED  /**< Button is in the PROTECTED state */
};

volatile ButtonState currentState = OFF; /**< Current state of the button */
volatile unsigned long pressStartTime = 0; /**< Time when button press started */
volatile unsigned long pressEndTime = 0;   /**< Time when button press ended */
volatile unsigned long pressDuration = 0;  /**< Duration of the button press */

/**
 * @brief Setup function.
 * 
 * Configures pin mode and initializes serial communication.
 */
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configure button pin as input with pull-up resistor
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, CHANGE); // Attach interrupt for button pin
  Serial.begin(9600); // Initialize serial communication for debugging
}

/**
 * @brief Main loop function.
 * 
 * Monitors the button state and transitions between states.
 */
void loop() {
  if (currentState == PROTECTED) { //Protection to run only during PROTECTED state

    if (millis() - pressStartTime >= PROTECTED_DURATION) { // Checks during PROTECTED state if it passed 10 seconds after the button was released

      currentState = OFF; // Transition to OFF state after PROTECTED_DURATION
      Serial.println("Button is OFF");
    }
  }
}

/**
 * @brief Button interrupt service routine (ISR).
 * 
 * Handles button press and release events.
 */
void buttonISR() {

  if (digitalRead(BUTTON_PIN) == LOW) { // Button pressed

    currentState = ON; //Change state for ON since the button was pressed
    pressStartTime = millis(); // Record button press start time
    Serial.println("Button is ON");

  } else { // Button released

    if (currentState == ON) { //Protection to run only if the state is ON

      pressEndTime = millis(); // Record the time when the button was released
      pressDuration = pressEndTime - pressStartTime; // Calculates the duration time of the button beign pressed
      Serial.print("Press duration time: ");
      Serial.print(pressDuration); // Print pressDuration as an integer
      Serial.println(" ms");
      Serial.println("Button is in PROTECTED state");
      currentState = PROTECTED; // Transition to PROTECTED state
    }
  }
}

#ifndef Slider_h
#define Slider_h

#include "Arduino.h"
#include "Button.h"
#include "Transition.h"
#include "State.h"

class Slider {
	private:
		// Initialization variables
		int _size; 								// Size of the slider
		int _numByte;							// Number of byte needed for the slider data
		uint8_t* _input; 						// Bytes where slider readings are stored
		Button **_buttons; 						// Slider buttons
		float _delta; 							// Value quantum

		// Pin variables
		uint8_t _latchPin;
		uint8_t _dataPin;
		uint8_t _clockPin;

		// Measurements variables
		bool _pressed = false;
		float _progress = 0; 					// Actual value of the slider
		unsigned long _holdCounter = 0; 		// Current time
		int _holdThreshold = 150; 				// Number of milliseconds that must elapse to accept a change in the progress of the slider

		uint8_t shiftIn(int myDataPin, int myClockPin);

	public:
		/*
 		* Slider has two constructors:
 		* one accepting the array containing digital pins attached to buttons,
		* the other one accepts the pin attacched to a shift register.
 		* Use of the class is the same in both cases
 		*/
		Slider(int size, int digitalPin[]);
		Slider(int size, uint8_t latchPin, uint8_t dataPin, uint8_t clockPin);

		/*
 		* Return if the slider is:
 		* PRESSED(transition between not pressed to pressed), 
 		* RELEASED(transition between pressed to not pressed),
 		* or simply not touched. 
 		*/
		Transition getTransition();

		/*
 		* Return if the slider is:
 		* ON(User is currently pressing the sensor), 
 		* OFF(User is currently not pressing the sensor), 
 		*/
		State getState();

		/*
		* Return current value of slider if pressed or return last progress value if not pressed
		* If an invalid number of button is pressed the function returns -1
		*/
		int getProgress();

		/*
		* Set _holdThresholdValue
		*/
		void setHoldThreshold(int value);

		/*
		* Update slider status getting data from shift registers
		*/
		void updateStatus();
};

#endif
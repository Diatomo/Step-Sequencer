
#include <Arduino.h>
#include "controller.h"

#define ON 1
#define OFF 0
//Macros
#define switchScanner(row)  (0b00000001 << (row))

//Constructor
Controller::Controller(){

}

/*
 *	FxN :: shift
 *
 *		bits outs so buttons can be read
 *
 */
void Controller::shift(){
		digitalWrite(latchWrite, LOW);
		shiftOut(dataWrite, clockPin, MSBFIRST, switchScanner(row)); 
		digitalWrite(latchWrite, HIGH);
}

/*
 *	FxN :: readState
 *
 *		reads corresponding buttons presses
 *
 */
void Controller::readState(){
		digitalWrite(latchRead, HIGH);
		buttonLast[row] = buttonCurrent[row];
		buttonCurrent[row] = shiftIn(dataRead, clockPin, MSBFIRST) >> 1;
		digitalWrite(latchRead, LOW);
}

/*
 *
 *  Fxn :: buttonCheck
 *		Updates button State when a button is pressed
 *
 */
void Controller::updateState(){
	uint8_t comp = 0b00000001;
	if (buttonCurrent[row] != buttonLast[row]){
		for (uint8_t i = 0; i < nCols; i++){
			comp = comp << i;
			if (buttonCurrent[row] & comp){
				boardState[row][i] = ON;
			}
		}
	}
}


/*
 *  FxN :: incrementRow
 *  	internal counter to allow multiple functions to operate on
 *  	one row at a time
 *
 */
void Controller::incrementRow(){
		row = (row + 1) % nRows;
}

}

/*
*============================================================
				Neo Cube
		Author: Charles C. Stevenson

This is code for a neo cube, which is a midi/sampler controller
for pure data scripts. Basically it emulates midi data for
several different modes, send that to a pure data script to play
custom made synthesizers or samples.

*============================================================
*/

#include "controller.h"
#include "communication.h"
#include "alarmclock.h"

//SPI Muxer PinOut
uint8_t const dataWrite = 9;
uint8_t const dataRead = 12;
uint8_t const latchWrite = 8;
uint8_t const latchRead = 11;
uint8_t const clockPin = 10;

//fastLED PinOut
uint8_t const NEOPIN = 23;

//fastLed Configuration
uint8t_ const nLedsPerBoard;
uint32_t const NUMLEDS = NBOARDS * nLedsPerBoard;//16 leds per board
CRGB leds[NUMLEDS];
CHSV hsvLeds[NUMLEDS];
uint8_t hue = 0;
uint8_t colors[NUMCOLORS] = {0,32,64,96,128,160,192,224};// r, o , y, g, b, i , v

//board configuration
uint8_t const nRows = 4;
uint8_t const nCols = 4;

//TODO muxer struct;;
struct board{
	Controller muxer = newController();
	uint8_t id;
	uint32_t neo[nRows][nCols];
};typedef struct board Board;


//alarmClocks
//===============
//prototype
void testSuite();

//timers
uint32_t testTmr = 5000;

//state
bool testState = true;

//alarmClock
alarmClock testClk = alarmClock(testSuite);
alarmClock clocks[nClocks] = {testClk};
bool* states[nClocks] = {testState};
//===============

//objects
Communication comm = new Communication();
FastLED.addLeds<NEOPIXEL, NEOPIN>(leds, NUMLEDS);
Board mux;//TODO turn into a pointer array

/*
*	FxN :: setup
*/ 
void setup(){
	while(!Serial);
-	unsigned int const BAUD_RATE = 9600;
	Serial.begin(BAUD_RATE);
	
	//button Handler
	pinMode(dataWrite, OUTPUT);
	pinMode(latchWrite, OUTPUT);
	pinMode(dataRead, INPUT);
	pinMode(latchRead, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(neoPin, OUTPUT);

	//create board(s)
	mux.id = 0;
	//the order of col then row is important because of board schematic
	for (uint8_t col = 0; col < mux.nCols; col++){
		for (uint8_t row = 0; row < mux.nRows; row++){
			mux.neo[row][col] = mux.id * nLeds;
		}
	}
}


//============================================
//	Color Functions
//============================================

/*
 *
 *	FxN :: fadeIn
 *
 */
void fadeIn(uint8_t row, uint8_t column){
		uint32_t button = neo[int32_t(row)][int32_t(column)];
		if (aesthetic[button].value < MAX-increment){
				aesthetic[button].value += increment;
				hsv2rgb_rainbow(aesthetic[button], leds[button]);
		}
		FastLED.show();
}

/*
 *
 * FxN :: fadeOut
 *
 */
void fadeOut(uint8_t row, uint8_t column){
		uint32_t button = neo[row][column];
		if (aesthetic[button].value > 0){
				aesthetic[button].value -= increment;
				hsv2rgb_rainbow(aesthetic[button], leds[button]);
		}
		FastLED.show();
}

/*
 *
 * FxN :: rainbow
 *
 */
void rainbow(){
	for (uint32_t i = 0; i < NUMLEDS; i++){
		if (aesthetic[i].value == 0) { aesthetic[i].value = MAX; }
		aesthetic[i].hue++;
		hsv2rgb_rainbow(aesthetic[i], leds[i]);
	}
	FastLED.show();
}
//============================================



/*
*
* FxN :: alarmClockRoutines
*   processes states and polling
*   
*   DO NOT TOUCH THIS FUNCTION
*
*
*/
void alarmClockRoutine(){
    for (byte i = 0; i < NUM_CLOCKS; i++){
        if (clocks[i].isSet()){//if clock is set
            if (*(states[i])){//if corresponding state is true
                clocks[i].poll();//poll
            }
            else{
                clocks[i].unSetAlarm();//otherwise;unset alarm
            }
        }
        else if (!clocks[i].isSet()){//if clock is no set
            if (*(states[i])){//if state is true
                clocks[i].setAlarm(timers[i]);//turn on alarm
            }
        }
    }
}


void send(){

	for (uint8_t row = 0; row < mux.nRows; row++){
		for (uint8_t col = 0; col < mux.nCols; col++){
			comm.send(row,col,mux.id,mux.boardState[row][col]);
		}
	}
}

/*
*	FxN :: loop
*		reads buttons
*		then outputs to serial port
*/
void loop(){
	mux.muxer.shift();
	mux.muxer.readstate();
	mux.muxer.updateState();
	mux.muxer.incrementRow();

	send();
	alarmClockRoutine();
}


//Test!!
/*
	Development section to test inputs and functions;
	Functions are called with alarm clocks to throttle 
	the serial output.

	No Unittest (sorry)
*/


void testSuite(){

	testAlphaLoop();
	testMuxerButtonState();
	testLeds();

}

void testAlphaLoop(){
	Serial.println("Running Test")
	Serial.println("==========================================");
	Serial.println();
}

void testMuxerButtonState(){
	Serial.println("MuxerTest");
	Serial.println("Expect 2d arr of bools, should change with button presses");
	Serial.println("==========================================");
	for (uint8_t row = 0; row < mux.nRows; row++){
		for (uint8_t col = 0; col < mux.nCols; col++){
			Serial.print("Row: ");
			Serial.println(row);
			Serial.print(mux.muxer.boardState[row][col])
			Serial.print(" ");
		}
		Serial.println();
	}
	Serial.println();
	Serial.println("Muxer test pass.");
	Serial.println();
}

void testRainbow(){

	Serial.println("RainbowTest");
	Serial.println("Expect Colors to show up on all leds");
	Serial.println("==========================================");
	rainbow();
	Serial.println();
	Serial.println("rainbow test pass.");
	Serial.println();

}

















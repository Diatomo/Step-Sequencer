
#include <Arduino.h>
#include "communication.h"


/*
 *
 *	Class Controller
 *
 */
class Controller{

	private:
		static const uint8_t nRows = 4;
		static const uint8_t nCols = 4;
		static const uint8_t dataWrite = 9;
		static const uint8_t dataRead = 12;
		static const uint8_t latchWrite = 8;
		static const uint8_t latchRead = 11;
		static const uint8_t clockPin = 10;
	
	public:
		Controller();

		//buttonPress functions
		void shift();
		void clear();
		void readState();
		bool updateState();
		void incrementRow();

		uint8_t buttonCurrent[4] 	= {0,0,0,0};//current buffer after debounce
		uint8_t buttonLast[4]		= {0,0,0,0};//last buffer

		bool boardState[4][4] = 
			{
				{0,0,0,0},
				{0,0,0,0},
				{0,0,0,0},
				{0,0,0,0}
			};
		};

		byte row = 0;		
		byte getRow();
};



//buttonPress structures
//uint8_t buttonEvent[4] 		= {0,0,0,0};//event before debounce
//uint8_t buttonState[4] 		= {0,0,0,0};//whats on and whats off
//uint8_t prevState[4] 		= {0,0,0,0};//what was on or off
//uint8_t buttonDebounceCounter[4][4];
#endif

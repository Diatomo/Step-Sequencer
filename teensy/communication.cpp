



//Author : Charles C. Stevenson (Diatomo)
//Date : August 16th, 2017

#include "communication.h"

Communication::Communication(){
		Serial.begin(9600);
		myPacketSerial.setStream(&Serial);		
}

void Communication::send(byte row, byte column, byte toggle, byte boardID){//OPEN SOURCE CONTROLLER SEND PROTOCOL. 
		uint8_t myPackets[4] = {row, column, toggle, boardID};
		myPacketSerial.send(myPackets,4);
}

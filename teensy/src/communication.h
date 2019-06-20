/*
 *	Author :  Charles C. Stevenson (Diatomo)
 *	Date : August, 18th, 2017
 *	pad.h - Library to handle aggregate board objects
 *	for a multi-colored sugarcube (midi pad)
 *
 */

#ifndef communication_h
#define communication_h

#include <Arduino.h>
#include <PacketSerial.h>

/*
 *
 *
 */

class Communication
{

	
	private:
		PacketSerial  myPacketSerial;
					
	public:
		Communication();
		void send(byte, byte, byte, byte);
		
};

#endif

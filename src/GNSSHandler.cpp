/*
 * GNSSHandler.cpp
 *
 *  Created on: Aug 8, 2019
 *      Author: samih
 */

#include "GNSSHandler.h"
#include "USART.h"
#include "ArrayManagement.h"

USART gnss(USART::eUSART3, 9600);
USART debug_gnss(USART::eUSART1, 9600);
// TODO minimize these to save space

// GNSS Message start with ASCII $ and ends to carriage return \r
const char START_BYTE = '$';	// Start of string
const char END_BYTE = '\r';		// End of string

GNSSHandler::GNSSHandler() {
	// TODO Auto-generated constructor stub
	localBufPointer = 0;
}

GNSSHandler::~GNSSHandler() {
	// TODO Auto-generated destructor stub
}

void GNSSHandler::configure() {
	gnss.enable();
	gnss.enableIRQ();
}

void GNSSHandler::read() {

	if(gnss.available()) {
		int size = gnss.getCount();
		char buffer[size];
		gnss.getBuffer(buffer, size);
		// Store buffer to to local buffer
		if(localBufPointer > GNSS_BUFFER_SIZE) {
			localBufPointer = 0;
			for(int i = 0; i < GNSS_BUFFER_SIZE; i++) {
				localBuffer[i] = 0;
			}
		}
		for(int i = 0; i < size; i++) {
			localBuffer[localBufPointer++] = buffer[i];
		}
	}
	// Check if full message received
	parseMessage();
}

void GNSSHandler::parseMessage(void) {
	// Buffer is size of local buffer
	int startBytePointer = -1;
	int endBytePointer = -1;
	int msgSize = -1;

	for (int i = 0; i < localBufPointer; i++) {
		// Find start byte
		if (localBuffer[i] == START_BYTE) {
			startBytePointer = i;
			endBytePointer = -1;	// If we find startByte again, reset end byte
			//debug_gnss.send("GNSS, found start byte", 22);
		} else if(startBytePointer == -1 && i >= localBufPointer) {
			// Don't do unnecessary looping
			return;
		}
		// Start byte and end byte has been found
		if ( (startBytePointer != -1) && localBuffer[i] == END_BYTE) {
			endBytePointer = i;
			// Calculate message size and reset localBuffer
			msgSize = endBytePointer - startBytePointer;
			localBufPointer = 0;
			// Break for loop and start processing
			// Reset local buffer, each GNSS string should be around 70bytes max
			//debug_gnss.send("GNSS, found string\n", 19);
			break;
		}
	}
	if(msgSize < 10) {
		return;
	}
	// Create temporary buffer
	char buffer[msgSize + 1];
	// Initialize buffer
	for (int i = 0; i < (msgSize + 1); i++) {
		buffer[i] = 0;
	}
	// Copy buffer
	for (int i = 0; i < msgSize; i++) {
		buffer[i] = localBuffer[startBytePointer +i];
	}
	debug_gnss.send(buffer, msgSize);
	debug_gnss.send("\n", 1);

	for(int i = 0; i < GNSS_BUFFER_SIZE; i++) {
		localBuffer[i] = 0;
	}

	if( (msgSize > 0) && (startBytePointer != -1) && (endBytePointer > 0) ) {
		ArrayManagement ar;
		// $GPGSV,NoMsg,MsgNo,NoSv,{,sv,elv,az,cno}*cs<CR><LF>
		if( ar.containsChar(buffer, "GPGSV", 4) ) {
			debug_gnss.send("Found GPGSV\n", 12);
			int outputSize = -1;
			// Get current time in UTC
			for (int i = 0; i < 3; i++) {
				satellites[i] = 0;	// Clear time
			}
			// Buffer to search from, output buffer, sperator character, which string to output
			// Returns size of found string
			outputSize = ar.split(buffer, satellites, ',', 3);
			if(outputSize > 2) {
				// No satellites found
				debug_gnss.send("No satellites found\n", 21);
			} else {
			// Debug output
				debug_gnss.send("Satellites: ", 12);
				debug_gnss.send(satellites, outputSize);
				debug_gnss.send("\n",1);
			}
		}
		// Detect which type of message is incoming
		// $GPGGA,hhmmss.ss,Latitude,N,Longitude,E,FS,NoSV,HDOP,msl,m,Altref,m,DiffAge,DiffStation*cs<CR><LF>
		// $GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,1.01,499.6,M,48.0,M,,0*5B
		// Compare current buffer to GPGGA if GPGGA is found and all 5 characters matches in row process the message
		if( ar.containsChar(buffer, "GPGGA", 4) ) {
			int outputSize = -1;
			// Get current time in UTC
			for (int i = 0; i < 15; i++) {
				currentTime[i] = 0;	// Clear time
			}
			// Buffer to search from, output buffer, sperator character, which string to output
			// Returns size of found string
			outputSize = ar.split(buffer, currentTime, ',', 1);
			// Debug output
			debug_gnss.send(currentTime, outputSize);
			// Get Latitude

			// Get Longitude

			// Get Altitude

			// Get connected satellites

		}
	}
}


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
		//debug_gnss.send(buffer, size);
		// Store buffer to to local buffer
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
		} else if(startBytePointer == -1) {
			// Don't do unnecessary looping
			return;
		}
		// Start byte and end byte has been found
		if ( (startBytePointer != -1) && localBuffer[i] == END_BYTE) {
			endBytePointer = i;
			// Calculate message size and reset localBuffer
			msgSize = endBytePointer - startBytePointer;
			// Break for loop and start processing
			// Reset local buffer, each GNSS string should be around 70bytes max
			for(int i = 0; i < GNSS_BUFFER_SIZE; i++) {
				localBuffer[i] = 0;
			}
			break;
		}
	}
	// Create temporary buffer
	char buffer[msgSize + 1];
	// Initialize buffer
	for (int i = 0; i < (msgSize + 1); i++) {
		buffer[i] = 0;
	}
	if( (msgSize > 0) && (startBytePointer != -1) && (endBytePointer > 0) ) {
		ArrayManagement ar;
		// Detect which type of message is incoming
		// $GPGGA,hhmmss.ss,Latitude,N,Longitude,E,FS,NoSV,HDOP,msl,m,Altref,m,DiffAge,DiffStation*cs<CR><LF>
		// $GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,1.01,499.6,M,48.0,M,,0*5B
		// Compare current buffer to GPGGA if GPGGA is found and all 5 characters matches in row process the message
		if(ar.containsChar("GPGGA", buffer, 5)) {
			// Get current time in UTC

			// Get Latitude

			// Get Longitude

			// Get Altitude

			// Get connected satellites

		}
	}
}


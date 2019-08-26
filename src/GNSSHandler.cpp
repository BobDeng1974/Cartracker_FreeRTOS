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
// Data Tables
char Buffer[512];
char GPGGA[70]; // Time, Position and Fix related data
char GPGSA[70]; // Receifer operating mode, Satellites used, and DOP values.
char GPRMC[70]; // Time, Date, Position, Course and Speed data
char GPGSV[70]; // Number of satellites in view, Satellite ID numbers,
                // Elevation, Azimuth, and SNR value

// Reference data
const unsigned char GPGGA_REF[7] = {"$GPGGA"}; // Used to determine where specific data
const unsigned char GPGSA_REF[7] = {"$GPGSA"}; // string starts
const unsigned char GPRMC_REF[7] = {"$GPRMC"};
const unsigned char GPGSV_REF[7] = {"$GPGSV"};
// GNSS Message start with ASCII $ and ends to carriage return \r
const char START_BYTE = '$';	// Start of string
const char END_BYTE ='\r'; /	/ End of string

// Comma Search
 // GPGGA
char GPGGA_POS[15]; // used for searchin information inside the data
 // GPGSA                  // string
char GPGSA_POS[15];
 // GPRMC
char GPRMC_POS[15];
 // GPGSV
char GPGSV_POS[15];

 // Syntaxes

 // GPGGA
 unsigned int check1 = 0, i1 = 0;

 // Misc
 unsigned int x = 0, gps_test = 0;
 int test = 0; // test control
 char choose = 1;
 char position = 0;
 char gps_fail[5];
 char salaa;
 char check=0;

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
		// Detect which type of message is incoming
		// GPGGA
	}
}


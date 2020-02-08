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
// GNSS Message start with ASCII $ and ends to carriage return \r
const char START_BYTE = '$';	// Start of string
const char END_BYTE = '\r';		// End of string

GNSSHandler::GNSSHandler() {
	// TODO Auto-generated constructor stub
	localBufPointer = 0;
	lockedSatellites = 0;
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
		for(int i = 0; i < size; i++) {
			// double make sure no crash happens
			if(localBufPointer >= GNSS_BUFFER_SIZE) localBufPointer = 0;
			localBuffer[localBufPointer++] = buffer[i];
			// make sure localBufPointer never exceeds size of array
			if(localBufPointer >= GNSS_BUFFER_SIZE -1) {
				debug_gnss.send("GNSSHandler::read() Buffer\n",27);
				debug_gnss.send(localBuffer,localBufPointer);
				debug_gnss.send("\n\n",2);
				parseMessage();
				localBufPointer = 0;
			}
		}
	}
}

void GNSSHandler::parseMessage(void) {

	findGPGSV(); // Gets stuck here, must be because of memory leak
	// If satellite count is less than 3, no point parsing rest
	if(lockedSatellites < 3) return;
	parseGPGGA();
	parseGPRMC();
}

void GNSSHandler::findGPGSV() {
	ArrayManagement ar;
	int startByte = 0, endByte = 0, count = 0;
	char buffer[100];
	debug_gnss.send("GNSSHandler::findGPGSV()\n", 26);

	while(1) {
		startByte = ar.findStringFrom(localBuffer, "$GPGSV", startByte, GNSS_BUFFER_SIZE, 6);
		if(startByte < 0) break;
		debug_gnss.send("GNSSHandler::findGPGSV() Found\n", 32);
		if (startByte > 0) endByte = ar.findChar(localBuffer, startByte, '*', GNSS_BUFFER_SIZE);
		if ( (endByte - startByte) > 29) count = ar.copyFromUntilFind(localBuffer, buffer, startByte, GNSS_BUFFER_SIZE, 100, '*');
		if ( (count > 20) && ar.countChars(buffer, ',', count) >= 6) {
			debug_gnss.send("GNSSHandler::findGPGSV() Starting to parse\n", 43);
			lockedSatellites = findSatelliteCount(buffer, count);
		}
		count = 0;
		startByte = startByte + 4;
	}
}

int GNSSHandler::findSatelliteCount(char *buffer, int bufferSize) {
	ArrayManagement ar;
	int satelliteCount = -1;
	debug_gnss.send("GNSSHandler::findSatelliteCount()\n", 34);
	int outputSize = -1;
	for (int i = 0; i < 3; i++) satellites[i] = 0;	// Clear time
	outputSize = ar.getMidArray(buffer, bufferSize, satellites, ',', 3); // Crashes
	if(outputSize > 2 || outputSize < 1) {
		debug_gnss.send("No satellites found\n", 20);
	} else {
		debug_gnss.send("Satellites: ", 12);
		debug_gnss.send(satellites, outputSize);
		debug_gnss.send("\n",1);
		satelliteCount = (int)ar.toInteger(satellites, outputSize); // Crashes
		if(satelliteCount == 11) debug_gnss.send("Locked satellites 11\n", 21);
	}
	return satelliteCount;
}

// $GPGGA,hhmmss.ss,Latitude,N,Longitude,E,FS,NoSV,HDOP,msl,m,Altref,m,DiffAge,DiffStation*cs<CR><LF>
// $GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,1.01,499.6,M,48.0,M,,0*5B
// Compare current buffer to GPGGA if GPGGA is found and all 5 characters matches in row process the message
void GNSSHandler::parseGPGGA()
{
	ArrayManagement ar;
	int startByte = ar.findString(localBuffer, "$GPGGA",GNSS_BUFFER_SIZE, 5);
	if(startByte != -1 ) {
		char buffer[50];
		int size = ar.copyFromUntilFind(localBuffer, buffer, startByte, GNSS_BUFFER_SIZE, 50,  '*');
		if(size == -1) return;
		// Find count of commas. If comma count is less than 5 then it's not valid data
		if(ar.countChars(buffer, ',', size) >= 6) {
			debug_gnss.send(buffer, size);
			debug_gnss.send("\n", 1);
		}
	}
}

void GNSSHandler::parseGPRMC() {
	ArrayManagement ar;
	int startByte = ar.findString(localBuffer, "$GPRMC", GNSS_BUFFER_SIZE, 5);
	if(startByte != -1 ) {
		char buffer[50];
		int size = ar.copyFromUntilFind(localBuffer, buffer, startByte, GNSS_BUFFER_SIZE, 50,  '*');
		if(size == -1) return;
		// Find count of commas. If comma count is less than 5 then it's not valid data
		if(ar.countChars(buffer, ',', size) >= 6) {
			debug_gnss.send(buffer, size);
			debug_gnss.send("\n", 1);
		}
	}
}

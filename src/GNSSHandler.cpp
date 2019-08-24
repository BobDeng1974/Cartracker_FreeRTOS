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

void GNSSHandler::parseMessage() {
	ArrayManagemnt ar;
	// Loop through buffer searching for dollar or <CR><LF>

	// $xxGGA,time,lat,NS,lon,EW,quality,numSV,HDOP,alt,altUnit,sep,sepUnit,diffAge,diffStation*cs<CR><LF>
	// $GPGGA,092725.00,4717.11399,N,00833.91590,E,1,08,1.01,499.6,M,48.0,M,,*5B
	// ! ends to <CR><LF> and starts from $
	if(ar.containsCharAdv(gnssBuffer, "GPGGA")) {

	}

}

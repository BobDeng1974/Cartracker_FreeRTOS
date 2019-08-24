/*
 * GNSSHandler.cpp
 *
 *  Created on: Aug 8, 2019
 *      Author: samih
 */

#include "GNSSHandler.h"
#include "USART.h"
//USART gnss(USART::eUSART3, 9600);
//USART debug_gnss(USART::eUSART1, 9600);


GNSSHandler::GNSSHandler() {
	// TODO Auto-generated constructor stub

}

GNSSHandler::~GNSSHandler() {
	// TODO Auto-generated destructor stub
}

void GNSSHandler::configure() {
	//gnss.enable();
	//gnss.enableIRQ();
}

void GNSSHandler::read() {
	/*debug_gnss.send("HELLO", 5);
	if(gnss.available()) {
		debug_gnss.send("USART3", 5);
		int size = gnss.getCount();
		char buffer[size];
		gnss.getBuffer(buffer, size);
		debug_gnss.send(buffer, size);
	}*/
}

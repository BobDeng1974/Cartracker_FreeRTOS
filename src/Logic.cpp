/*
 * Logic.cpp
 *
 *  Created on: Aug 2, 2019
 *      Author: samih
 */

#include <Hardware/USART.h>
#include "Logic.h"
#include "defines.h"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

USART debugLogic(USART::eUSART1, 9600);

Logic::Logic() {
	// TODO Auto-generated constructor stub
	xStream = NULL;
	xNextChar = 0;
	xReceiveLength = 0;
	xStartIndex = 0;
	xStringLength = 0;
	msgFlag = false;
	msgSize = 0;

}

Logic::~Logic() {
	// TODO Auto-generated destructor stub
}

void Logic::run() {
	messageReceive();
	messageParse();
	// Check if message received

};

void Logic::setStreamBuffer(StreamBufferHandle_t xStreamBuffer) {
	xStream = xStreamBuffer;
	const char *msg = "Logic::setStreamBuffer\n";
	debugLogic.send(msg, strlen(msg));
}

/* Expects to receive the pc54ByteString over and over again. Sends and receives are not blocking so will interleave. */
void Logic::messageReceive() {
	// Check that Stream buffer has been initialized
	/* Attempt to receive as many bytes as possible, up to the limit of the Rx buffer size. */
	for(int i = 0; i < (int)strlen(rxBuffer); i++) {
		rxBuffer[i] = 0;
	}
	xReceiveLength = xStreamBufferReceive( xStream, ( void * ) rxBuffer, sizeof( rxBuffer ), sbDONT_BLOCK );
	if( xReceiveLength > 0 ) {
		msgSize = xReceiveLength;
		msgFlag = true;
		// Convert to structure
		memcpy(&receivedMessage, rxBuffer,(msgSize * sizeof(char)));
	}

}

bool Logic::messageParse()
{
	if(!msgFlag) return false;
	msgFlag = false;
	switch(receivedMessage.type) {
	case MessageProtocol::MSG_BLE:
		debugLogic.send(receivedMessage.message, receivedMessage.size);
		break;
	case MessageProtocol::MSG_GNSS:
		break;
	case MessageProtocol::MSG_IMU:
		break;
	}
	return false;
}

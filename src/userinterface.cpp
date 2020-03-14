/*
 * userinterface.cpp
 *
 *  Created on: Aug 2, 2019
 *      Author: samih
 */

#include <Handlers/CommunicationHandler.h>
#include "defines.h"
#include <cstring>
#include <stdlib.h>     /* malloc, free, rand */

USART ble(USART::eUSART1, 9600);
static BaseType_t xErrorStatus;

CommunicationHandler::CommunicationHandler() {
	// TODO Auto-generated constructor stub
	ble.enable();
	ble.enableIRQ();
	queue = NULL;
	xStreamBuffer = NULL;
	xErrorStatus = pdPASS;
	xBytesActuallySent = 0;
	xStringLength = 0;
	xNextChar = 0;
	xBytesToSend = 0;
}

CommunicationHandler::~CommunicationHandler() {
	// TODO Auto-generated destructor stub
}

void CommunicationHandler::run() {
	if(ble.available()) {
		MessageProtocol::InterTaskMessage message;
		//MessageProtocol::InterTaskMessage messageConverted;

		message.type = MessageProtocol::MSG_BLE;
		message.size = ble.getCount();
		ble.getBuffer(message.message, ble.getCount());
		//ble.send(message.message, message.size);
		// Convert structure to char array
		char buffer[sizeof(message)];
		// Copy block of memory, copies the values of num bytes from the location pointed to by source directly to the memory pointed by destination
		memcpy(buffer, (const unsigned char*)&message, sizeof(message));
		//memcpy(&messageConverted, buffer, sizeof(buffer));
		//ble.send(messageConverted.message, messageConverted.size);
		send(buffer, sizeof(message));
	}
}

void CommunicationHandler::setQueue(QueueHandle_t q) {
	queue = q;
}

void CommunicationHandler::setStreamBuffer(StreamBufferHandle_t xStream) {
	xStreamBuffer = xStream;
}

/* Keep sending the string to the stream buffer as many bytes as possible in each go.  Doesn't block so calls can interleave with the non-blocking
 * receives performed by prvNonBlockingReceiverTask(). */
void CommunicationHandler::send(const char *msg, int size) {
	// Check that Stream buffer has been initialized
	if(xStreamBuffer == NULL) return;
	xStringLength = size;
	/* The whole string cannot be sent at once, so xNextChar is an index to the position within the string that has been sent so far.  How many
	bytes are there left to send before the end of the string? */
	xBytesToSend = xStringLength - xNextChar;
	/* Attempt to send right up to the end of the string. */
	xBytesActuallySent = xStreamBufferSend( xStreamBuffer, ( const void * ) &( msg[ xNextChar ] ), xBytesToSend, sbDONT_BLOCK );
	prvCheckExpectedState( xBytesActuallySent <= xBytesToSend );

	/* Move the index up the string to the next character to be sent, wrapping if the end of the string has been reached. */
	xNextChar += xBytesActuallySent;
	prvCheckExpectedState( xNextChar <= xStringLength );

	if( xNextChar == xStringLength ) {
		xNextChar = 0;
		xBytesActuallySent = 0;
		xBytesToSend = 0;
	}
}

void CommunicationHandler::prvCheckExpectedState( BaseType_t xState ) {
	configASSERT( xState );
	if( xState == pdFAIL ) {
		xErrorStatus = pdFAIL;
	}
}

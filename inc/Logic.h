/*
 * Logic.h
 *
 *  Created on: Aug 2, 2019
 *      Author: samih
 */

#ifndef LOGIC_H_
#define LOGIC_H_
#include "MessageProtocol.h"
#include "WBUS.h"
extern "C" {
	#include "../FreeRTOS/inc/FreeRTOS.h"
	#include "../FreeRTOS/inc/stream_buffer.h"
	#include "../FreeRTOS/inc/task.h"
}

class Logic {
public:
	Logic();
	virtual ~Logic();
	// Run logic process
	void run();
	void setStreamBuffer(StreamBufferHandle_t xStreamBuffer);
	;
private:
	// Steam buffer variables & functions
	StreamBufferHandle_t xStream;
	int xNextChar;
	int xReceiveLength;
	int xStartIndex;

	// Define max string length
	int xStringLength;
	BaseType_t xNonBlockingReceiveError = pdFALSE;
	char rxBuffer[100];
	int msgSize;
	bool msgFlag;
	MessageProtocol::InterTaskMessage receivedMessage;
	void messageReceive();
	bool messageParse();
	WBUS webasto;

	int wbusTemp = 0;
};

#endif /* LOGIC_H_ */

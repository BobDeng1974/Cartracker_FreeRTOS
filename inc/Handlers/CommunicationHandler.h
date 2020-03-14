/*
 * userinterface.h
 *
 *  Created on: Aug 2, 2019
 *      Author: samih
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "Hardware/USART.h"
#include "Protocols/MessageProtocol.h"

extern "C" {
	#include "../FreeRTOS/inc/FreeRTOS.h"
	#include "../FreeRTOS/inc/stream_buffer.h"
	#include "../FreeRTOS/inc/task.h"
	#include "../FreeRTOS/inc/semphr.h"
}

class CommunicationHandler {
public:
	CommunicationHandler();
	virtual ~CommunicationHandler();

	void run();
	void setQueue(QueueHandle_t q);
	void setStreamBuffer(StreamBufferHandle_t xStream);

private:
	QueueHandle_t queue;
	StreamBufferHandle_t xStreamBuffer;

	// Communication between tasks
	void send(const char *msg, int size);
	void prvCheckExpectedState(BaseType_t xState);

	static int xBytesActuayllySent;
	int xBytesToSend;
	int xStringLength;
	int xBytesActuallySent;
	int xNextChar;
};

#endif /* USERINTERFACE_H_ */

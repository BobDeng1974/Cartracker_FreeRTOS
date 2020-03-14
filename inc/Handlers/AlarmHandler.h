/*
 * AlarmHandler.h
 *
 *  Created on: Aug 2, 2019
 *      Author: samih
 */

#ifndef ALARMHANDLER_H_
#define ALARMHANDLER_H_

extern "C" {
	#include "../FreeRTOS/inc/FreeRTOS.h"
	#include "../FreeRTOS/inc/task.h"
	#include "../FreeRTOS/inc/semphr.h"
}

class AlarmHandler {
public:
	AlarmHandler();
	virtual ~AlarmHandler();

	void run();
	void setQueue(QueueHandle_t q);
private:
	QueueHandle_t queue;
};


#endif /* ALARMHANDLER_H_ */

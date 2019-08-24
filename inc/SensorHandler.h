/*
 * SensorHandler.h
 *
 *  Created on: Aug 2, 2019
 *      Author: samih
 */

#ifndef SENSORHANDLER_H_
#define SENSORHANDLER_H_

#include "GNSSHandler.h"
extern "C" {
	#include "../FreeRTOS/inc/FreeRTOS.h"
	#include "../FreeRTOS/inc/task.h"
	#include "../FreeRTOS/inc/semphr.h"
}

class SensorHandler {
public:
	SensorHandler();
	virtual ~SensorHandler();

	void run();
	void setQueue(QueueHandle_t q);
	void initialize();
private:
	QueueHandle_t queue;
	GNSSHandler handler;
};


#endif /* SENSORHANDLER_H_ */

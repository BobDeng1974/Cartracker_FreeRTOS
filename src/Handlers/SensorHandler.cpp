/*
 * SensorHandler.cpp
 *
 *  Created on: Aug 2, 2019
 *      Author: samih
 */

#include <Handlers/SensorHandler.h>

SensorHandler::SensorHandler() {
	// TODO Auto-generated constructor stub
	queue = NULL;

}

SensorHandler::~SensorHandler() {
	// TODO Auto-generated destructor stub
}

void SensorHandler::initialize()
{
	handler.configure();
}
void SensorHandler::run() {
	handler.read();
}

void SensorHandler::setQueue(QueueHandle_t q) {
	queue = q;
}


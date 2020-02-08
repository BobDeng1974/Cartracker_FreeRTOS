/**
  ******************************************************************************
  * @file    main.cpp
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#include <CommunicationHandler.h>
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "GPIO.h"
#include "Logic.h"
#include "SensorHandler.h"
#include "AlarmHandler.h"
#include "USART.h"
#include <stdlib.h>
#include <cstring>
#include "MessageProtocol.h"

extern "C" {
	#include "../FreeRTOS/inc/FreeRTOS.h"
	#include "../FreeRTOS/inc/task.h"
	#include "../FreeRTOS/inc/semphr.h"
	#include "../FreeRTOS/inc/stream_buffer.h"
}

TaskHandle_t TaskSensors;
TaskHandle_t TaskUI;
TaskHandle_t TaskLogic;
TaskHandle_t TaskAlarm;

GPIO gpio;
Logic logic;
SensorHandler sensorsHandler;
AlarmHandler alarmHandler;
CommunicationHandler communicationHandler;


QueueHandle_t queue;
// Need to be initialized in main, otherwise doesn't work in subclasses
USART debug(USART::eUSART1, 9600);

void init() {
	SystemCoreClockUpdate();
	//SysTick_Config(SystemCoreClock / 1000);	// Brakes GPIO reading
	gpio.initPin(GPIO::PIN_PA0, GPIO::PIN_OUTPUT);
	gpio.initPin(GPIO::PIN_PA1, GPIO::PIN_INPUT);
	gpio.setPin(GPIO::PIN_PA0, GPIO::PIN_LOW);
	//RCC_Configuration();
	// Create a queue for inter-task communication
	queue = xQueueCreate(3, sizeof(int));
}

void static taskLogic(void *pvParameter) {
	// Receiver task
	// Pass Stream buffer to class
	logic.setStreamBuffer((StreamBufferHandle_t) pvParameter);
	while(1) {
		vTaskDelay(TASK_LOGIC_DELAY);
		logic.run();
	}
}

void static taskCommunication(void *pvParameter) {
	// Sender task
	communicationHandler.setStreamBuffer((StreamBufferHandle_t) pvParameter);
	while(1) {
		vTaskDelay(TASK_COMMUNICATION_DELAY);
		communicationHandler.run();
	}
}

void static taskSensors(void *pvParameter) {
	sensorsHandler.initialize();

	while(1) {
		sensorsHandler.run();
		vTaskDelay(TASK_SENSORS_DELAY);
	}
}

void static taskAlarm(void *pvParameter) {
	alarmHandler.setQueue(queue);
	while(1) {
		alarmHandler.run();
		vTaskDelay(TASK_ALARM_DELAY);
	}
}

// Lowest priority, indicates system is on
void blinkled(void *pvParameter) {
	int qPointer;
	while(1) {
		xQueueReceive(queue, &qPointer, 0);
		if(qPointer == 1) {
			gpio.setPin(GPIO::PIN_PA0, GPIO::PIN_HIGH);
		//	int count = debug.getCount();
		//	char point[count + 1];
		//	debug.getBuffer(point, debug.getCount());
			//debug.send(point, count);
			qPointer = 0;
		} else {
			gpio.setPin(GPIO::PIN_PA0, GPIO::PIN_HIGH);
			vTaskDelay(300);
			gpio.setPin(GPIO::PIN_PA0, GPIO::PIN_LOW);
		}
		vTaskDelay(300);
	}
}

int main(void)
{
	 /* SysTick end of count event each 10ms */
	StreamBufferHandle_t xStreamBuffer;
	MessageProtocol protocol;
	// Initialize stream buffer for logic and communication, set size of buffer to size of MessageProtocol struct interTaskMessage
	xStreamBuffer = xStreamBufferCreate(sbSTREAM_BUFFER_LENGTH_BYTES, sbTRIGGER_LEVEL_1 );

	init();
	debug.enable();
	debug.enableIRQ();

	debug.send("Starting system\n", 16);
	// Very high priority
	xTaskCreate(taskAlarm, (const char*)"AlarmTask", configMINIMAL_STACK_SIZE, NULL, alarm_TASK_PRIORITY, NULL);
	// High priority, Configure as sending task
	xTaskCreate(taskCommunication, (const char*)"Communication", configMINIMAL_STACK_SIZE, xStreamBuffer, communication_TASK_PRIORITY, NULL);
	// Normal priority
	xTaskCreate(taskLogic, (const char*)"Logic", configMINIMAL_STACK_SIZE, xStreamBuffer, logic_TASK_PRIORITY, NULL);
	xTaskCreate(taskSensors, (const char*)"Sensors", configMINIMAL_STACK_SIZE, NULL, sensors_TASK_PRIORITY, NULL);
	//Low priority
	xTaskCreate(blinkled, (const char*)"Led", configMINIMAL_STACK_SIZE, NULL, blinkLed_TASK_PRIORITY, NULL);
	 /* Start the scheduler. */
	 vTaskStartScheduler();
	    /* Will only get here if there was insufficient heap to start the scheduler. */
	 while(1) {
		 if(gpio.getPin(GPIO::PIN_PA1) == GPIO::PIN_HIGH) {
			 gpio.setPin(GPIO::PIN_PA0, GPIO::PIN_HIGH);
		 } else {
			 gpio.setPin(GPIO::PIN_PA0, GPIO::PIN_LOW);
		 }
	 };
	 return 0;
}

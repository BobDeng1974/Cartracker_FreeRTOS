/*
 * NEOWAYM590.h
 *
 *  Created on: Jul 29, 2019
 *      Author: samih
 */

#ifndef NEOWAYM590_H_
#define NEOWAYM590_H_

#include "Hardware/GPIO.h"
#include "Hardware/USART.h"



class NEOWAY_M590 {
public:
	NEOWAY_M590(GPIO::enumPin pinPwr, GPIO::enumPin pinRing);
	virtual ~NEOWAY_M590();

	void init();
	void setPower(bool state);
	void sendMsg(const char *number, const char *msg, const int lenNumber, const int lenMsg);
	void initGPRS();
	void connectToServer(const char *address);
	void closeConnection();

	bool USART_AVAILABLE();
	int USART_COUNT();
	void USART_BUFFER(char *output, int maxLen);


private:
	char gsmBuffer[100];
	void clearBuffer();
	void configure();
	GPIO gpio;
	const int messageDelay = 100;
	GPIO::enumPin GPIO_PWR;
	GPIO::enumPin GPIO_RING;
};

#endif /* NEOWAYM590_H_ */

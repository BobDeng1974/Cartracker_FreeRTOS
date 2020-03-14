/*
 * NEOWAYM590.cpp
 *
 *  Created on: Jul 29, 2019
 *      Author: samih
 */

#include <Hardware/delay.h>
#include "defines.h"
#include "../../inc/Drivers/NEOWAYM590.h"
#include "Strings.h"
#include "Hardware/USART.h"

const char end_byte = (char)0x0D;
USART usartGSM(USART::eUSART2, 115200);

NEOWAY_M590::NEOWAY_M590(GPIO::enumPin pwrPin, GPIO::enumPin ringPin) {
	// TODO Auto-generated constructor stub
	GPIO_PWR = pwrPin;
	GPIO_RING = ringPin;
	//DelayInit();
	usartGSM.enable();
	usartGSM.enableIRQ();
}

NEOWAY_M590::~NEOWAY_M590() {
	// TODO Auto-generated destructor stub
}

void NEOWAY_M590::init() {
	clearBuffer();
	gpio.initPin(GPIO_PWR, GPIO::PIN_OUTPUT);
	gpio.initPin(GPIO_RING, GPIO::PIN_OUTPUT);
	configure();
}

void NEOWAY_M590::configure() {
	// Set power on
	setPower(true);
	usartGSM.send("AT+CLIP=1", 9);
	//debugGSM.send("AT+CLIP", 7);
	usartGSM.send(&end_byte, 1);
	DelayMs(messageDelay);

	usartGSM.send("AT+CMGF=1", 9);	// Set modem to text mode
	//debugGSM.send("AT+CMGF=1", 9);
	usartGSM.send(&end_byte, 1);
	DelayMs(messageDelay);
	// Set modem character set to GSM
	usartGSM.send("AT+CSCS=\"GSM\"", 13);
	//debugGSM.send("AT+CSCS=\"GSM\"", 13);
	usartGSM.send(&end_byte, 1);
	DelayMs(messageDelay);
}

void NEOWAY_M590::setPower(bool state) {
	if(state) {
		gpio.setPin(GPIO_PWR, GPIO::PIN_HIGH);
		gpio.setPin(GPIO_RING, GPIO::PIN_LOW);
		DelayMs(300);
		gpio.setPin(GPIO_PWR, GPIO::PIN_LOW);
		DelayMs(100);
	} else {
		gpio.setPin(GPIO_PWR, GPIO::PIN_HIGH);
	}
}

void NEOWAY_M590::sendMsg(const char *number, const char *msg, const int lenNumber, const int lenMsg) {
	char message[50];
	char end = 26;
	makeString("AT+CMGS=\"", message, 9);
	appendString(number, message, 9, lenNumber);
	appendString("\"", message, (9 + lenNumber), 1);
	usartGSM.send(message, (9 + lenNumber + 1));
	usartGSM.send(&end_byte, 1);
	DelayMs(messageDelay);
	makeString(msg, message, lenMsg);
	usartGSM.send(message, lenMsg);
	usartGSM.send(&end, 1);
}

/* GPRS Example
 * 	at+xisp=0
	at+cgdcont=1,"IP","your APN"
	at+xiic=1
	at+tcpsetup=1,server-address,port
	at+tcpsend=1,number of chars
	> --- when this prompt comes up, you can send the data.
	GET /test.html HTTP1.1
	HOST:server-address,port
	Connection:keep-alive
	CTRL+Z ---once the data is loaded..send termination command to send data
	at+tcpclose=1  --- disconnect IP connection
	AT+CGATT=0  --- disconnect GPRS connection
 *
 *
 */
void NEOWAY_M590::initGPRS() {
	// Select the internal protocol stack of the modem
	usartGSM.send("AT+XISP=0", 9);
	usartGSM.send(&end_byte, 1);
	DelayMs(messageDelay);
	// ELISA APN, Internet
	usartGSM.send("AT+CGDCONT=1,\"IP\",\"Internet\"", 9);
	usartGSM.send(&end_byte, 1);
	DelayMs(messageDelay);
	// Establish PPP link, Point-to-Point protocol
	usartGSM.send("AT+XIIC=1", 9);
	usartGSM.send(&end_byte, 1);
	DelayMs(messageDelay);
	// Establish tcp connection with server
	usartGSM.send("AT+TCPSETUP=1,www.google.com,80", 9);
	usartGSM.send(&end_byte, 1);
	DelayMs(messageDelay);
	// Send data,
	usartGSM.send("AT+TCPSEND=0,136", 9);
	usartGSM.send(&end_byte, 1);
	DelayMs(messageDelay);
	// Send message http://ec2-35-180-242-178.eu-west-3.compute.amazonaws.com:8000/user/create/
	// https://tttapa.github.io/ESP8266/Chap09%20-%20Web%20Server.html
	// https://www.esp8266.com/viewtopic.php?f=32&t=8859
	usartGSM.send("GET HTTP/1.1\r\n", 9);
	usartGSM.send(&end_byte, 1);
	DelayMs(messageDelay);

	usartGSM.send("AT+TCPCLOSE=0", 9);
	usartGSM.send(&end_byte, 1);
	DelayMs(messageDelay);

}

void NEOWAY_M590::connectToServer(const char *address) {

}

void NEOWAY_M590::closeConnection() {

}

// Private functions
void NEOWAY_M590::clearBuffer() {
	for(int i = 0; i <= 256; i++) {
		gsmBuffer[i] = 0;
	}
}

bool NEOWAY_M590::USART_AVAILABLE() {
	return usartGSM.available();
}

int NEOWAY_M590::USART_COUNT() {
	return usartGSM.getCount();
}

void NEOWAY_M590::USART_BUFFER(char *output, int maxLen) {
	usartGSM.getBuffer(output, maxLen);
}



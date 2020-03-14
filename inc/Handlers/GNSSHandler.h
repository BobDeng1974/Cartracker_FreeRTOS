/*
 * GNSSHandler.h
 *
 *  Created on: Aug 8, 2019
 *      Author: samih
 *      NEO6MV2 - Datasheet: https://www.openimpulse.com/blog/wp-content/uploads/wpsc/downloadables/GY-NEO6MV2-GPS-Module-Datasheet.pdf
 *      u-blox GNSS Protocol: https://www.u-blox.com/sites/default/files/products/documents/u-blox8-M8_ReceiverDescrProtSpec_%28UBX-13003221%29_Public.pdf
 *      	- Page 119 for Standard messages examples.
 */

#ifndef GNSSHANDLER_H_
#define GNSSHANDLER_H_

#define GNSS_BUFFER_SIZE 200
/* NEO6MV2
 * Default baud 9600
 *
 */

class GNSSHandler {

public:
	GNSSHandler();
	virtual ~GNSSHandler();
	void read();
	void configure();

private:
	char currentTime[15];
	char satellites[3];
	int lockedSatellites;
	// Checks if full message received, if yes parse message correctly and set gnss message flag high
	void parseMessage(void);
	// Set static buffer, limited amount of memory. Dynamic could exceed heap.
	char localBuffer[GNSS_BUFFER_SIZE];
	int localBufPointer;

	void parseGPGGA();
	void parseGPGSV();
	void parseGPRMC();

};

#endif /* GNSSHANDLER_H_ */

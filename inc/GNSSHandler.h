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
	// Informs if filtered message is available from GNSS
	void parsedMessageAvailable();
	void process();

private:
	char dateg[15];
	char timeg[15];

	char Latitude[15];
	double Latitude_f;
	char Latitude_direction[15];

	char Longitude[15];
	double Longitude_f;
	char Longitude_direction[15];
	char Satellites[15];
	char Altitude[15];
	// Checks if full message received, if yes parse message correctly and set gnss message flag high
	void parseMessage();
	// Set static buffer, limited amount of memory. Dynamic could exceed heap.
	static char localBuffer[100];
	int localBufPointer;

	void getline();
	void data_extractor(); // 33-40 comma locations
	void data_positions();
	void receive_data();

	void time();
	void date();
	void cordinates();
	void satellites();
	void printdata();
	void float_conversion();

};

#endif /* GNSSHANDLER_H_ */

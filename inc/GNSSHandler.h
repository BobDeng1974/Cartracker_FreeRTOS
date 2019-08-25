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
	// TODO this is not very memory saving favorable, see if this can be more compact.
	// Contains latest date data
	char dateg[15];
	// Contains latest time data
	char timeg[15];
	// Contains latest latitude
	char Latitude[15];
	// Contains latest latitude in float type
	double Latitude_f;
	// Contains latest latitude direction
	char Latitude_direction[15];
	// Contains latest longitude data
	char Longitude[15];
	// Contains latest longitude as float
	double Longitude_f;
	// Contains latest longitude direction
	char Longitude_direction[15];
	// Contains amoun of satellites
	char Satellites[15];
	// Contains latest altitude data
	char Altitude[15];
	// Checks if full message received, if yes parse message correctly and set gnss message flag high
	void parseMessage();
	// Set static buffer, limited amount of memory. Dynamic could exceed heap.
	static char localBuffer[100];
	int localBufPointer;
	// read line from buffer
	void getline();
	// Extract meaningful data from received GNSS message
	void data_extractor(); // 33-40 comma locations
	// Find data locations
	void data_positions();
	// Receive data from GNSS module
	void receive_data();

	// Print time
	void time();
	// Print date
	void date();
	// Print coordinates
	void cordinates();
	// Print satellites
	void satellites();
	// Print all data
	void printdata();
	void float_conversion();

};

#endif /* GNSSHANDLER_H_ */

/*
 * GNSSHandler.h
 *
 *  Created on: Aug 8, 2019
 *      Author: samih
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
private:
	void parseMessage();
};

#endif /* GNSSHANDLER_H_ */

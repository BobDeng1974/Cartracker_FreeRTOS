/*
 * MessageProtocol.h
 *
 *  Created on: Aug 8, 2019
 *      Author: samih
 */

#ifndef MESSAGEPROTOCOL_H_
#define MESSAGEPROTOCOL_H_

class MessageProtocol {

public:
	enum eMessageType {
		MSG_BLE,
		MSG_IMU,
		MSG_GNSS
	};

	struct InterTaskMessage {
		eMessageType type;
		char message[30];
		int size;
	};

	MessageProtocol();
	virtual ~MessageProtocol();
};


#endif /* MESSAGEPROTOCOL_H_ */

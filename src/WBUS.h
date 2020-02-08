/*
 * WBUS.h
 *
 *  Created on: 8 Feb 2020
 *      Author: sami
 */
// Reference https://github.com/Moki38/wbus-arduino/blob/master/src/Wbus.cpp

#ifndef WBUS_H_
#define WBUS_H_

class WBUS {
public:
	WBUS();
	virtual ~WBUS();

	void initialize();
	unsigned char checksum(unsigned char *buf, unsigned char len, unsigned char chk);
	void combine(unsigned char val);
	void start(int val);
	void stop();
	void loop();
	void gather(int val);
	void parse(unsigned char *buf, unsigned char len);
	void version();
	void status();
	const char* printState(unsigned char state);

private:

	// Webasto configuration
	struct webastoSetup {
		unsigned char heaterType;
		bool timerActive;
	};

	// Webasto timer parameters
	struct webastoTimer {
		unsigned char sun;
		unsigned char sunHourOn;
		unsigned char sunHourOff;
		unsigned char sunMinOff;
	};

	bool keepalive;
	bool on;
	bool timer;
	unsigned char temp;             // Set TEMP
	unsigned char mode;             // 1 ECO, 2 Normal. 3 Boost 4 Vent

	unsigned char status_caf;       // Combustion Fan
	unsigned char status_fp;        // Fuel Pump
	unsigned char status_gp;        // Glow Plug
	unsigned char status_cp;        // Circulation Pump
	unsigned char status_vfr;       // Vehicle Fan Relays
	unsigned char status_nsh;       // Nozzle stock heating
	unsigned char status_fi;        // Flame indicator
	unsigned char status_ms;        // Main switch
	unsigned char status_shr;       // Suplemental heater request

	unsigned char status_os;        // Operating state
	char status_os_long[30]; 		// Operating state Text

	unsigned char status_temp;      // Temperature with  50 C offset (20 C is value=70)
	float status_mvolt;    			// Voltage in mili Volt
	unsigned char status_fd;        // Flame detector (set 0x01, not set 0x00)
	float status_hp;       			// Heating power in watts, big endian
	float status_fdr;      			// Flame detector resistance in mili Ohm, big endian

	unsigned char status_wh;        // Working hours
	unsigned char status_wm;        // Working minutes
	unsigned char status_oh;        // Operating hours
	unsigned char status_om;        // Operating minutes
	unsigned char status_sc;        // Start counter

	unsigned char status_gpp;       // Glow plug power in percent *2
	unsigned char status_fpf;       // Fuel pump pulse frequency in Hz *2
	unsigned char status_afp;       // Combustion air fan in percent*2

	unsigned char info_version;     // Version
	unsigned char info_devname;     // Device name
	unsigned char info_wbuscode;    // WBUS Code
	unsigned char info_wbusvers;    // WBUS version

	unsigned char pos;
	unsigned char len = 0;
	unsigned char buffer[20];
	int version_run = 0;
	int status_run = 0;
};

#endif /* WBUS_H_ */

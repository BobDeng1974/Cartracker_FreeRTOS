/*
 * GNSSHandler.cpp
 *
 *  Created on: Aug 8, 2019
 *      Author: samih
 */

#include "GNSSHandler.h"
#include "USART.h"
#include "ArrayManagement.h"

USART gnss(USART::eUSART3, 9600);
USART debug_gnss(USART::eUSART1, 9600);
// TODO minimize these to save space
// Data Tables
char Buffer[512];
char GPGGA[70]; // Time, Position and Fix related data
char GPGSA[70]; // Receifer operating mode, Satellites used, and DOP values.
char GPRMC[70]; // Time, Date, Position, Course and Speed data
char GPGSV[70]; // Number of satellites in view, Satellite ID numbers,
                // Elevation, Azimuth, and SNR value

// Reference data
const unsigned char GPGGA_REF[7] = {"$GPGGA"}; // Used to determine where specific data
const unsigned char GPGSA_REF[7] = {"$GPGSA"}; // string starts
const unsigned char GPRMC_REF[7] = {"$GPRMC"};
const unsigned char GPGSV_REF[7] = {"$GPGSV"};
const char STAR_REF ='\r'; // used for ending gps strings

// Comma Search
 // GPGGA
char GPGGA_POS[15]; // used for searchin information inside the data
 // GPGSA                  // string
char GPGSA_POS[15];
 // GPRMC
char GPRMC_POS[15];
 // GPGSV
char GPGSV_POS[15];

 // Syntaxes

 // GPGGA
 unsigned int check1 = 0, i1 = 0;

 // Misc
 unsigned int x = 0, gps_test = 0;
 int test = 0; // test control
 char choose = 1;
 char position = 0;
 char gps_fail[5];
 char salaa;
 char check=0;

GNSSHandler::GNSSHandler() {
	// TODO Auto-generated constructor stub
	localBufPointer = 0;
}

GNSSHandler::~GNSSHandler() {
	// TODO Auto-generated destructor stub
}

void GNSSHandler::configure() {
	gnss.enable();
	gnss.enableIRQ();
}

void GNSSHandler::read() {

	if(gnss.available()) {
		int size = gnss.getCount();
		char buffer[size];
		gnss.getBuffer(buffer, size);
		//debug_gnss.send(buffer, size);
		// Store buffer to to local buffer
		for(int i = 0; i < size; i++) {
			localBuffer[localBufPointer++] = buffer[i];
		}
	}
	// Check if full message received
	parseMessage();
}


void GNSSHandler::data_extractor() {
	if( gps_test == 1){
		gps_fail[2] = 0;
		gps_test = 0;
	}

	// Time
	check = 0;
	for (int i= 1 + GPRMC_POS[0]; i <= GPRMC_POS[1] - 1; i++) {
		timeg[check++]=GPRMC[i];
	};

	check = 0;
	for (int i = (1 + GPRMC_POS[8]); i <= (GPRMC_POS[9] - 1); i++) {
		dateg[check++]=GPRMC[i];
	};

	// latitude
	check = 0;
	for (int i=1+GPRMC_POS[2]; i<=GPRMC_POS[3]-1; i++) {
		Latitude[check++]=GPRMC[i];
	};

	check = 0;
	for (int i=1+GPRMC_POS[3]; i<=GPRMC_POS[4]-1; i++) {
		Latitude_direction[check++]=GPRMC[i];
	};

	// Longitude
	check=0;
	for (int i=1+GPRMC_POS[4]; i<=GPRMC_POS[5]-1; i++) {
		Longitude[check++]=GPRMC[i];
	};

	check=0;
	for (int i=1+GPRMC_POS[5]; i<=GPRMC_POS[6]-1; i++) {
		Longitude_direction[check++]=GPRMC[i];
	};

	// Altitude
	check=0;
	for (int i=GPGGA_POS[8]; i<=GPGGA_POS[9]; i++) {
		Altitude[check++]=GPGGA[i];
	};

	// Satellites
	check=0;
	for (int i=GPGSV_POS[2]; i<=GPGSV_POS[3]; i++) {
		Satellites[check++]=GPGSV[i];
	};
 }

void GNSSHandler::data_positions()
{
    if(gps_test == 1){
    	debug_gnss.printf("\n\rGPS test: data positions");
    	gps_fail[1] = 0;
    }
    // GPGGA
    position = 0;
    for(int i = 0; i <= 69; i++) {
    	if(GPGGA[i] == ',') {
    		GPGGA_POS[position++] = i;
    	}
    }; // i increase by one and every time GPGGA equal to "," i value is stored to comma array

    // GPGSA
    position = 0;
    for(int i=0; i<=69; i++) {
    	if( GPGSA[i] == ',') {
    		GPGSA_POS[position++] = i;
    	}
    }; // i increase by one and every time GPGGA equal to "," i value is stored to comma array

    // GPRMC
    position = 0;
    for(int i = 0; i <= 69; i++) {
    	if( GPRMC[i] == ',') {
    		GPRMC_POS[position++] = i;
    	}
    }; // i increase by one and every time GPGGA equal to "," i value is stored to comma array

    // GPGSV
    position = 0;
    for(int i = 0; i <= 69; i++) {
    	if( GPGSV[i] == ',') {
    		GPGSV_POS[position++] = i;
    	}
    }; // i increase by one and every time GPGGA equal to "," i value is stored to comma array
}

/********************************************'****/
/* Function to receife the data from GPS */
void GNSSHandler::getline()
{
    while(_gps.getc() != '$');    // wait for the start of a line
          for(int i=0; i<512; i++) {
              Buffer[i] = _gps.getc();
              }
              return;
}

void GNSSHandler::process()
{
    receive_data();
    data_positions();
    data_extractor();
    float_conversion();
    printdata();
}

void  GNSSHandler::receive_data()
{
	if(gps_test == 1) {
		for(int i = 0; i <= 5; i++) {
			gps_fail[i] = 0;
		}
	gps_fail[0] = 1;
	}
	getline();
	for(int i=0; i<512; i++) {
		// GPGGA
		if(x==1 && check==1) {
			x=0;
			check=0;
			for(int i=0; i<69; i++) {
				GPGGA[i] = ' ';
			}
		}

       GPGGA[check]=Buffer[i];
       if(check<6) {
           if(GPGGA[check] != GPGGA_REF[check]) {
        	   check = 0;
        	   GPGGA[check]= ' ';
           }
        }
       if(check > 7) {
    	   if(GPGGA[check] == STAR_REF) {// star is used for ending the string
               GPGGA[check] = ' ';
               check = 0;
               x = 1;
               test = 1;
               choose = 2;
               if(test==1) {
            	   debug_gnss.printf("\r\n");
               }
               break;
             }
         }
     check++;
	} // end for loop
	for(int i = 0; i < 512; i++) {
		// GPGSA
		if(x==1 && check==1) {
			x = 0;
			check = 0;
			for(int i = 0; i < 69; i++) {
				GPGSA[i] = ' ';
			}
		}
        GPGSA[check]=Buffer[i];
        if(check < 6) {
        	if(GPGSA[check] != GPGSA_REF[check]) {
        		check = 0;
        		GPGSA[check] = ' ';
        	}
         }

         if(check > 7) {
        	 if(GPGSA[check] == STAR_REF) { // star is used for ending the string
        		 GPGSA[check]=' ';
                 check = 0;
                 x = 0;
                 test = 1;
                 if(test == 1) {
                	 debug_gnss.printf("\r\n");
                 }
                 break;
              }
         }
         check++;
    } // end for loop
  /******************* GPRMC******************************/
    for(int i = 0; i < 512; i++) {

         if(x==1 && check==1) {
        	 x = 0;
        	 check = 0;
        	 for(int i = 0; i < 69; i++) {
        		 GPRMC[i] = ' ';
        	 }
         }
         GPRMC[check] = Buffer[i];
         if(check<6) {
             if(GPRMC[check] != GPRMC_REF[check]) {
            	 check = 0;
            	 GPRMC[check] = ' ';
             }
          }

         if(check > 7) {
             if(GPRMC[check] == STAR_REF) { // star is used for ending the string
            	 GPRMC[check]=' ';
                 check = 0;
                 x = 0;
                 test = 1;
                 if(test == 1) {
                	 debug_gnss.printf("\r\n");
                 }
                 break;
             }
         }
    } // end for loop

    for(int i = 0; i < 512; i++) {
    	// GPGSV

         if(x==1 && check==1) {
        	 x = 0;
        	 check = 0;
        	 for(int i = 0; i < 69; i++) {
        		 GPGSV[i] = ' ';
        	 }
         }

         GPGSV[check]=Buffer[i];

         if(check<6) {
             if(GPGSV[check] != GPGSV_REF[check]) {
            	 check=0;
            	 GPGSV[check]= ' ';
             }
          }

         if(check>7) {
             if(GPGSV[check] == STAR_REF) {// star is used for ending the string
            	 GPGSV[check]=' ';
                 check=0;
                 x=0;
                 test=1;
                 break;
              }
         }
            check++;
    } // end for loop
 } // end function

 void GNSSHandler::time()
 {
	 for(int i = 1; i <= ((GPRMC_POS[1] - GPRMC_POS[0]) - 1); i++) {
		 debug_gnss.printf("%c", timeg[i]);
		 if( i==2 || i==4 ) {
			 debug_gnss.printf(":");
		 }
	 }
 }

 void GNSSHandler::date()
 {
    debug_gnss.printf("\n\rDate: ");
    for(int i = 1; i <= ((GPRMC_POS[9] - GPRMC_POS[8]) - 1); i++) {
    	debug_gnss.printf("%c", dateg[i]);
    	if( i==2 || i==4 ) {
    		debug_gnss.printf(".");
    	}
    }

 }

 void GNSSHandler::cordinates()
 {
 // Latitude
	 for(int i = 1; i <= ((GPRMC_POS[3] - GPRMC_POS[2]) - 1); i++) {
		 debug_gnss.printf("%c", Latitude[i]);
	 }
     for(int i = 1; i <= ((GPRMC_POS[4] - GPRMC_POS[3]) - 1); i++) {
    	 debug_gnss.printf("%c", Latitude_direction[i]);
     }

    // Longitude
    for(int i = 1; i <= ((GPRMC_POS[5] - GPRMC_POS[4]) - 1); i++) {
    	debug_gnss.printf("%c", Longitude[i]);
    }
    debug_gnss.printf(" : ");
    for(int i = 1; i <= ((GPRMC_POS[6] - GPRMC_POS[5]) - 1); i++) {
    	debug_gnss.printf("%c", Longitude_direction[i]);
    }

    // Altitude
    debug_gnss.printf("\n\r");
    debug_gnss.printf("Altitude : ");
    for(int i = 1; i <= ((GPGGA_POS[9] - GPGGA_POS[8]) - 1); i++) {
    	debug_gnss.printf("%c", Altitude[i]);
    }
 }

 void GNSSHandler::satellites()
 {
	 for(int i = 1; i <= ((GPGSV_POS[3] - GPGSV_POS[2]) - 1); i++) {
		 debug_gnss.printf("%c", Satellites[i]);
	 }
 }
 void GNSSHandler::printdata()
 {
    debug_gnss.printf("Raw data:\n\r");
    for(int i = 0; i <= 69; i++) {
    	debug_gnss.putc(GPGGA[i]);
    } // print out GPGSA
    debug_gnss.printf("\n\r");
    for(int i = 0; i <= 69; i++) {
    	debug_gnss.putc(GPGSA[i]);
    } // print out GPGSA
    debug_gnss.printf("\n\r");
    for(int i = 0; i <= 69; i++) {
    	debug_gnss.putc(GPRMC[i]);
    } // print out GPGSA
    debug_gnss.printf("\n\r");
    for(int i = 0; i <= 69; i++) {
    	debug_gnss.putc(GPGSV[i]);
    } // print out GPGSA
    debug_gnss.printf("\n\r");
    debug_gnss.printf("\n\r");
    debug_gnss.printf("Extracted data");
    debug_gnss.printf("\n\r");
    // Time
    debug_gnss.printf("Time: ");
    for(int i = 0; i <= ((GPRMC_POS[1] - GPRMC_POS[0]) - 1); i++) {
    	debug_gnss.printf("%c", timeg[i]);
    	if( i==2 || i==4 ) {
    		debug_gnss.printf(":");
    	}
    }
    debug_gnss.printf("\n\r");
    // Date
    debug_gnss.printf("Date: ");
    for(int i = 0; i <= ((GPRMC_POS[9] - GPRMC_POS[8]) - 1); i++) {
    	debug_gnss.printf("%c", dateg[i]);
    	if( i==2 || i==4 ) {
    		debug_gnss.printf(".");
    	}
    }
    debug_gnss.printf("\n\r");
    // Latitude
    debug_gnss.printf("Latitude : ");
    for(int i = 0; i <= ((GPRMC_POS[3] - GPRMC_POS[2]) - 1); i++) {
    	debug_gnss.printf("%c", Latitude[i]);
    }
    debug_gnss.printf(" : ");
    for(int i = 0; i <= ((GPRMC_POS[4] - GPRMC_POS[3]) - 1); i++) {
    	debug_gnss.printf("%c", Latitude_direction[i]);
    }
    debug_gnss.printf("\n\r");
    // Longitude
    debug_gnss.printf("Longitude : ");
    for(int i = 0; i <= ((GPRMC_POS[5] - GPRMC_POS[4]) - 1); i++) {
    	debug_gnss.printf("%c", Longitude[i]);
    }
    debug_gnss.printf(" : ");
    for(int i = 0; i <= ((GPRMC_POS[6] - GPRMC_POS[5]) - 1); i++) {
    	debug_gnss.printf("%c", Longitude_direction[i]);
    }
    debug_gnss.printf("\n\r");
    // Altitude
    debug_gnss.printf("Altitude : ");
    for(int i = 0; i <= ((GPGGA_POS[9] - GPGGA_POS[8]) - 1); i++) {
    	debug_gnss.printf("%c", Altitude[i]);
    }
    debug_gnss.printf("\n\r");
    // Satellites
    debug_gnss.printf("Satellites : ");
    for(int i = 0; i <= ((GPGSV_POS[3] - GPGSV_POS[2]) - 1); i++) {
    	debug_gnss.printf("%c", Satellites[i]);
    }
    debug_gnss.printf("\n\r");
    debug_gnss.printf("end");
 }

 void GNSSHandler::float_conversion()
 {
   char dummy1[]="453.7";
   char dummy2[]="1234.07";

   //debug_gnss.printf("\n\r Float Values\n\r ");
   Latitude_f=atof(dummy1);// debug_gnss.printf("float latitude: %f", Latitude_f);
   Longitude_f=atof(dummy2);// debug_gnss.printf("float Longitude: %f", Longitude_f);
 }

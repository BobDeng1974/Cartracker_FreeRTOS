/*
 * Strings.cpp
 *
 *  Created on: Jul 29, 2019
 *      Author: samih
 */

#include "Strings.h"

StringHelper::StringHelper() {
	// TODO Auto-generated constructor stub

}

StringHelper::~StringHelper() {
	// TODO Auto-generated destructor stub
}

void makeString(const char input[], char *output, const int len) {
	for (int i = 0; i < len; i++) {
		output[i] = input[i];
	}
}

void appendString(const char input[], char *output, const int start, const int len) {
	for (int i = 0; i < len; i++) {
		output[start + i] = input[i];
	}
}


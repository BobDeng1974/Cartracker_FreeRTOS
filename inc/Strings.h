/*
 * Strings.h
 *
 *  Created on: Jul 29, 2019
 *      Author: samih
 */

#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#ifdef __cplusplus
extern "C" {
#endif
	void makeString(const char input[], char *output, const int len);
	void appendString(const char input[], char *output, const int start, const int len);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
class StringHelper {
public:
	StringHelper();
	virtual ~StringHelper();
	// Make a string

};
#endif
#endif /* STRINGS_H_ */

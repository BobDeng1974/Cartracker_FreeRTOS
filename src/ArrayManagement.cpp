/* Copyright of Massive Timing
 *  
 */

#include "ArrayManagement.h"
#include "defines.h"
#include <cmath>
#include <cstring>

ArrayManagement::ArrayManagement() 
{

}

bool ArrayManagement::containsChar(char *cmp1, const char *cmp2, int len) // Compares received string to reference string
{
  
  bool correct = false;
  int x = 0;
  
  // start loop
  for(int i = 0; i <= sizeof(cmp1); i++) {
    if(cmp1[i] != cmp2[x]) {
      x = 0;
    } else {
      x++;
      if(x >= len) {
        correct = true;
        break;
      }
    }
  }
  return(correct);
}

int ArrayManagement::containsCharAdv(char *cmp1, const char *cmp2, int len1, int len2) // Compares received string to reference string
{
  bool correct = false;
  bool startFlag = false;
  int startIndex = -1;
  int x = 0;
  // start loop
  for(int i = 0; i <= len1; i++) {
    if(cmp1[i] != cmp2[x]) {
      x = 0;
      startFlag = false;
    } else {
    	if(!startFlag) {
    		startIndex = i;
    		startFlag = true;
    	}
    	x++;
    	if(x >= len2) {
    		correct = true;
        break;
      }
    }
  }
  return startIndex;
}

long ArrayManagement::toInteger(char* array) 
{
  int Storage[20];
  for(int i = 0; i < 20; i++) {
    Storage[i] = 0;
  }
  long Real = 0;
  int count = sizeof(array);
  
  int n3 = 0;
  
  for (int n = 0; n <= count; n++) {
    if (array[n] == '*') {
      break;
    }
    if (array[n] == '0' || array[n] == '1' || array[n] == '2' || array[n] == '3' || array[n] == '4' || array[n] == '5' || array[n] == '6' || array[n] == '7' || array[n] == '8' || array[n] == '9') {
      Storage[n3] = (array[n] - '0');
      n3++;
    }
  }
  
  int Multiplier = 0;
  
  for (int n2 = 0; n2 <= (n3 - 1); n2++) {
   if (Storage[(n3 - 1) - n2] >= 0 && Storage[(n3 - 1) - n2] <= 9) {
      if (Storage[(n3 - 1) - n2] == 0) {
        Multiplier++;
      }
      else {
        Real = Real + (Storage[(n3 - 1) - n2] * pow(10, Multiplier));
        Multiplier++;
      }
    }
  }
  return Real;
}

void ArrayManagement::toBinary(int toConvert, char *output)
{
  for (int i = 7; i >= 0; --i) {
    output[i] = ( (toConvert & (1 << i)) ? '1' : '0');
  }
}


int ArrayManagement::avarage(int *array, int count) 
{
  long value = 0;
  for(int i = 0; i <= count; i++) {
    value = (value + (long)array[i]);
  }
  int calculated = ((int)value/count);
  return calculated;
}

int ArrayManagement::percentage(int scaleMin, int scaleMax, int val)
{
  if (scaleMin > val) return int(0);
  if (scaleMax < val) return int(100); 
  float numerator = (val - scaleMin);
  float denominator = (scaleMax - scaleMin);
  
   int calculatedPercentage = (int)( ( numerator/ denominator ) * (float)(100));
   return calculatedPercentage;
}

void ArrayManagement::makeString(char *input, char *output, int inputLen)
{
  for(int i = 0; i < inputLen; ++i) {
    output[i] = input[i];
  }
  output[inputLen] = '\0';
}

bool ArrayManagement::addArrayToArray(char *input, char *output, int inputLen, int outputStart)
{
  for(int i = 0; i < inputLen; ++i) {
    output[outputStart + i] = input[i]; 
  }
  return true;
}

int ArrayManagement::integerToArray(int toConvert, char *output, int maxLen)
{
  int len = 0;
  while (toConvert) { // loop till there's nothing left
    if(maxLen == len) return len;
    output[len++] = '0' + toConvert % 10; // assign the last digit
    toConvert /= 10; // "right shift" the number
  }
  return len;
}

int getLengthInteger(int input)
{
  int len = 0;
  while(input) {
    len++;
    input /= 10;
  }
  return len;
}

void ArrayManagement::clearArray(char *input, int len)
{
   for(int i = 0; i < len; ++i) {
      input[i] = 0x00;
  }
}

void ArrayManagement::copyArray(char *copyFrom, char *copyTo, int len )
{
  for(int i = 0; i < len; ++i) {
    copyTo[i] = copyFrom[i];
  }
}

int ArrayManagement::copyFromUntilFind(char *toParse, char *output, int startIndex, int sizeOfInput, int sizeOfOutput, char byteToFind) {
	int len = 0;
	for(int i = 0; i < sizeOfOutput; i++) {
		if(i >= sizeOfInput) return -1;
		output[i] = toParse[startIndex + i];
		len++;
		if(output[i] == byteToFind) {
			return len;
		}
	}
	return -1;
}
int ArrayManagement::splitCount(char *toParse, char *output, char seperator)
{
  int i = 0;
  int lenParse = strlen(toParse);
  int seperatorCount = 0;

  // Count amount of seperators
  for (i = 0; i < lenParse; i++) {
    if(toParse[i] == seperator) {
      seperatorCount++;
    }
  }
  return seperatorCount;
}

int ArrayManagement::split(char *toParse, char *output, char seperator, int selection)
{
  int i = 0;
  int y = 0;
  int lenParse = strlen(toParse);
  int lenOutput = strlen(output);
  int seperatorCount = 0;
  int seperatorLocations[30]; // Contains where is start and end point
  int startLoc = 0;
  int endLoc = 0;
  // Init seperatoLocations Array
  for (i = 0; i < 30; i++) {
    seperatorLocations[i] = 0;
  }
  // Count amount of seperators
  for (i = 0; i < lenParse; i++) {
    if(toParse[i] == seperator) {
      seperatorLocations[seperatorCount] = i;
      seperatorCount++;
    }
  }
  if(seperatorCount < 1) return 0;
  if (selection > (seperatorCount + 1)) {
    return 0;
  } else if ( selection < 0) {
    return 0;
  }
  // start seperating
  
  if( selection == 0) {
    startLoc = 0;
  } else if (selection > 0) {
    startLoc = (seperatorLocations[selection - 1] + 1);
  }

  if ( selection >= seperatorCount && startLoc < lenParse) {
    // check if we have more characters after last seperator
    endLoc = (lenParse + 1);
  } else {
    endLoc = (seperatorLocations[selection]);
  }
  y = 0;
  for (i = startLoc; i < endLoc; i++) {
    output[y] = toParse[i];
    y++;
  }
  return y;
}

int ArrayManagement::countChars(char *buffer, char toFind, int sizeOfBuffer) {
	int count = 0;
	for(int i = 0; i < sizeOfBuffer; i++) {
		if(buffer[i] == toFind) count++;
	}
	return count;
}



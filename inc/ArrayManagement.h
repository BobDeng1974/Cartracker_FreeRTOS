/* Copyright of Reski
 *  
 */
 
#include "Arduino.h"

class ArrayManagement{
  public:
    ArrayManagement();
    bool containsString(String toCompare, String comparedTo);
    bool containsChar(char *cmp1, const char *cmp2, int len);
    bool containsCharAdv(char *cmp1, const char *cmp2, int len1, int len2);
    /*! \brief turns number in array format to integer
     * \param CHAR*
     * \return INTEGER
     */
    long toInteger(char* array);
    int integerToArray(int toConvert, char *output, int maxLen);

    int getArrayLength(char *input);
    void clearArray(char *input, int len);
    void copyArray(char *copyFrom, char *copyTo, int len );
    long stringToLong(String value);
    void toBinary( int toConvert, char *output);
    String convertMsToClockFormat(long mSeconds);
    int avarage(int *array, int count);
    /*! \brief convert value to percentage
     *  \return INTEGER, 0 - 100
     */
    int percentage(int scaleMin, int scaleMax, int val);
    String strtohex(String data);
    bool addArrayToArray(char *input, char *output, int inputLen, int outputStart);
    void makeString(char *input, char *output, int inputLen);

    // Split functions
    int splitCount(char *toParse, char *output, char seperator);
    
    /*! \brief Split array by seperator. Splits array into pieces based on seperator.
     * \param CHAR *, toParse -> array to split
     * \param CHAR *, output -> output array
     * \param CHAR, seperator seperates arrays
     * \param INTEGER, selection which splitted array to output
     * \return INTEGER, Length of output array
     */
    int split(char *toParse, char *output, char seperator, int choice);
    
  private:
  
};
















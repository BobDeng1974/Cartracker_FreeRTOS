class ArrayManagement{
  public:
    ArrayManagement();

    /*!\brief Compares cmp1 to cmp2.
     * \param cmp1 is pointer to compared char array.
     * \param cmp2 is pointer to compared char array.
     * \param len is integer and determines how many characters have to match to be true.
     * \return boolean. If success return true.
     */
    bool containsChar(char *cmp1, const char *cmp2, int len);

    /*!\brief Compares cmp1 to cmp2.
     * \param cmp1 is pointer to compared char array.
     * \param cmp2 is pointer to compared char array.
     * \param len is integer and determines how many characters have to match to be true.
     * \param startIndex returns first index of where string was found
     * \return boolean. If success return true.
     */
    int findString(char *cmp1, const char *cmp2, int len1, int len2);

    /*!\brief Compares cmp1 to cmp2.
     * \param cmp1 is pointer to compared char array.
     * \param cmp2 is pointer to compared char array.
     * \param startForm is integer and determines where to start searching
     * \param len is integer and determines how many characters have to match to be true.
     * \param startIndex returns first index of where string was found
     * \return boolean. If success return true.
     */
    int findStringFrom(char *cmp1, const char *cmp2, int startFrom, int len1, int len2);

    /*! \brief turns number in array format to integer
     * \param CHAR*
     * \return INTEGER
     */
    long toInteger(char* array, int count);

    /*! \brief turns number in array format to integer
     * \param toConvert is the integer to be converted
     * \param output is pointer to output buffer where to store data
     * \param maxLen is integer and determines maximum length of output buffer
     * \return results as integer
     */
    int integerToArray(int toConvert, char *output, int maxLen);

    /*! \brief counts length of array
     * \param input is the char array to count
     * \return length of array as integer
     */
    int getArrayLength(char *input);

    /*! \brief clears array
     * \param input is the char array to be cleared
     * \param lent is integer that determines length
     */
    void clearArray(char *input, int len);

    /*! \brief Copies array
     * \param copyFrom is pointer to char array to copy from
     * \param copyTo is pointer to char array to copy
     * \param len in integer and states max length to copy
     */
    void copyArray(char *copyFrom, char *copyTo, int len );

    /*! \brief Converts integer value to binary char array
     * \param toConvert integer is the converted value
     * \param output is the pointer to char array to store conversion
     */
    void toBinary( int toConvert, char *output);

    /*! \brief Calculates average value from integer array
     * \param array is integer pointer to array of samples
     * \param count is integer stating length of sample array
     * \return results as in integer
     */
    int avarage(int *array, int count);

    /*! \brief convert value to percentage
     * \param scaleMin determines min value
     * \param scaleMax determines max value
     * \param val is the value to convert into percentage
     * \return INTEGER, 0 - 100
     */
    int percentage(int scaleMin, int scaleMax, int val);

    /*! \brief Appends array to existing array
     * \param input is pointer to char array to be appended
     * \param output is pointer to char array where to append input
     * \param inputLen is integer which determines max size for inputLen
     * \param outputStart is integer which determines where to start appending
     * \return BOOLEAN if all ok true
     */
    bool addArrayToArray(char *input, char *output, int inputLen, int outputStart);

    /*! \brief Creates a string ending into \0 which acts as end of string
     * \param input is pointer to char array where to create the string
     * \param output is pointer to char array where to store the string
     * \param inputLen is integer which determines max size for inputLen
     */
    void makeString(char *input, char *output, int inputLen);

    /*! \brief Creates a string ending into \0 which acts as end of string
     * \param input is pointer to char array where to create the string
     * \param output is pointer to char array where to store the string
     * \param inputLen is integer which determines max size for inputLen
     */
    int splitCount(char *toParse, char *output, char seperator);
    
    /*! \brief Split array by seperator. Splits array into pieces based on seperator.
     * \param CHAR *, toParse -> array to split
     * \param CHAR *, output -> output array
     * \param CHAR, seperator seperates arrays
     * \param INTEGER, selection which splitted array to output
     * \return INTEGER, Length of output array
     */
    int getMidArray(char *toParse, int parseBufferSize, char *output, char seperator, int selection);

    /*! \brief Copies from input array to output. Start copying from defined start index and ends when specific byte has been found
     * \param toParse is pointer to char array where from to find and copy
     * \param output is pointer to char array where to store copied characters
     * \param startIndex is integer which defines where to start parsing
     * \param sizeOfInput is integer defining max size of input array
     * \param sizeOfOutput is integer defining max size for output array
     * \param byteToFind is char being searched for
     * \return INTEGER, Length of output array
     */
    int copyFromUntilFind(char *toParse, char *output, int startIndex, int sizeOfInput, int sizeOfOutput, char byteToFind);

    /*! \brief Get count of toFind chars in buffer
     * \param buffer is pointer to char array to be searched from
     * \param toFind is a char to find
     * \param sizeOfBuffer is integer determining size of buffer
     * \return count as integer
     */
    int countChars(char *buffer, char toFind, int sizeOfBuffer);
    
    /*! \brief Find byte
     * \param buffer is pointer to char array to be searched from
     * \param startFrom is integer. Determines where to start searching
     * \param toFind is a char to find
     * \param sizeOfBuffer is integer determining size of buffer
     * \return index as integer
     */
    int findChar(char *buffer, int startFrom, char toFind, int sizeOfBuffer);

    /*! \brief Split array by seperator. Splits array into pieces based on seperator.
     * \param CHAR *, toParse -> array to split
     * \param CHAR *, output -> output array
     * \param CHAR, seperator seperates arrays
     * \param INTEGER, selection which splitted array to output
     * \return INTEGER, Length of output array
     */
    int splitArray(char *copyFrom, int sizeOfBufferFrom, char *copyTo, int sizeOfBufferTo, char seperator, int select);
};

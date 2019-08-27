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
    int containsCharAdv(char *cmp1, const char *cmp2, int len1, int len2);

    /*! \brief turns number in array format to integer
     * \param CHAR*
     * \return INTEGER
     */
    long toInteger(char* array);

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
     * \param scaleMin determines min value
     * \param scaleMax determines max value
     * \param val is the value to convert into percentage
     * \return INTEGER, 0 - 100
     */
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
    int copyFromUntilFind(char *toParse, char *output, int startIndex, int sizeOfInput, int sizeOfOutput, char byteToFind);
    int countChars(char *buffer, char toFind, int sizeOfBuffer);
    
  private:
  
};
















/* Copyright of Reski
 *  
 */
 

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
    int integerToArray(int toConvert, char *output, int maxLen);

    int getArrayLength(char *input);
    void clearArray(char *input, int len);
    void copyArray(char *copyFrom, char *copyTo, int len );
    void toBinary( int toConvert, char *output);
    int avarage(int *array, int count);
    /*! \brief convert value to percentage
     *  \return INTEGER, 0 - 100
     */
    int percentage(int scaleMin, int scaleMax, int val);
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
















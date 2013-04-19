#ifndef CSVREADER_H
#define CSVREADER_H

#include <sstream>  // std::stringstream
#include <fstream>  // std::ifstream
#include <string>   // std::string
#include <typeinfo>

using namespace std;

#include "Parser.h"

class CSVReader
{
    public:
        /**
         * Constructs a CSVReader and reset all data members
         */
        CSVReader();
        /**
         * Constructs a CSVReader, resets all data members, and open file 'file'
         */
        CSVReader(const char* file);

        ~CSVReader(){};

        /**
         * Opens a CSV file. Loads the CSV file to the ifstream
         * @returns true if the file is open
         */
        void openFile(const char* file);

        /**
         * Resets everything to initial state
         */
        void reset();

        /**
         * Reads the next line of the CSV file
         */
        void readLine();

        /**
         * Reads the next field of the current line
         */
        void readField();

        /**
         * Gets the current line. If isEof, do nothing
         */
        string getLine();

        /**
         * Gets the current field. If isEol, do nothing
         */
        template <class T>
        T getField(){
            T t;
            if (curField.empty())
                return 0;
            stringstream ss(curField);
            ss >> t;
            return t;
        };

        string getCurField();

        /**
         * Returns the number of fields of current file
         */
        int getFieldSize();

        /**
         * Returns the index of the current field you're on
         */
        int getFieldIndex();

        /**
         * Used to determine if at the End of CSV Line
         * @returns my_ss.eof()
         */
        bool isEol();

        /**
         * Used to determine if at the End of CSV File
         * @returns my_ifs.eof()
         */
        bool isEof();

        /**
         * Used to determine if a CSV file is open
         * @returns true if it's open; otherwise, false
         */
        bool isOpen();

    private:
        /**
         * Counts the number of fields are in the file
         */
         void countFields();


        ifstream        my_ifs;     // file to parse
        stringstream    my_ss;      // stringstream for tokenizing current line

        string          curLine;    // last line we read
        string          curField;   // last field we got read
        int             fSize;      // the number of fields the CSV file has
        int             fIndex;     // the current field you're on
};

#endif // CSVREADER_H

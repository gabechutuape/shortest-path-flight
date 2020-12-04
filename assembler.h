#include <fstream>
#include <vector>


#ifndef ASSEMBLER_H
#define ASSEMBLER_H

/*
BUILDUP/BREAKDOWN
--------------------------------------------------------------------------------------
Probably have some form of constructor 
Probably have a default constructor as well just to be safe
Probably have some form of destructor
--------------------------------------------------------------------------------------
FUNCTIONS
--------------------------------------------------------------------------------------
P1: DATA PROCESSING
-Have something that reads the file data
-Have something that puts it in a format we can use (Hashing?)
P2: ACTUAL STUFF
-Algorithm stuff. Will theorize later. Right now lets just get first two parts done
-------------------------------------------------------------------------------------
*/

class Assembler{
    public:
        /**
         * Constructor for Assembler
         * Takes in file paths as strings for the three required files
         */ 
        Assembler(const std::string& airport_file, const std::string& airline_file, const std::string& route_file);

        /**
         * Destructor
         */ 
        ~Assembler();

        /**
         * Copy constructor
         */ 
        Assembler(const Assembler& other);

        /**
         * Copy assignment
         */ 
        Assembler& operator=(const Assembler& other);

    private:
        void Copy(const Assembler& other);
        void Delete();

        std::string airport_file_;
        std::string airline_file_;
        std::string route_file_;
};

#endif //ASSEMBLER_H
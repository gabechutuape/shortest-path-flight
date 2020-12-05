#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <map>

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

        std::unordered_map<int, std::string> airline_ID_to_name_;
        std::map<int, node> airport_map_;
        std::unordered_map<std::string, int> airport_code_to_ID_;


        /**
         * Function for parsing elements from line in CSV file.
         * Returns a vector with each comma separated value as a string as elements.
         */
        std::vector<std::string> ParseLine(const std::string &line);

        /**
         * Function calculates and returns distance from 2 latitude and longitudes
         * Uses haversine formula
         * 
         * @param lat1 airport 1's latitude
         * @param long1 airpot 1's longitude
         * @param lat2 airport 2's latitude
         * @param long2 airport 2's longitude
         * @return the distance in miles
         */ 
        double GetDistance(double lat1, double long1, double lat2, double long2);

        /**
         * Populates the hash table of airline id's to airline names
         * Uses airline_file_ to insert into airline_ID_to_name_
         */ 
        void PopulateIdToName();

        /**
         * Populates map of airport IDs to airport nodes
         * Populates hash map of airport codes to IDs
         * Reads from airport_file_ and updates airport_map_ and airport_code_to_ID_
         */ 
        void PopulateAirportMapAndCodeToID();
};

struct node{
    int id;
    std::string name;
    double latitude;
    double longitude;
    std::string airport_code;
};

struct edge{
    int start_id;
    int end_id;
    double distance;
};

#endif //ASSEMBLER_H
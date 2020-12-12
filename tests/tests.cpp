#include "../cs225/catch/catch.hpp"
#include "../helper.h"
#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <map>
#include <queue>
#include <unordered_set>
#include <iostream>

#ifdef WINDOWS
#include <stdio.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define EPSILON 0.0001

/**
 * 
 * rchaud9, gfc2, dimitar3
 * Dec 2020
 * 
 * tests.cpp holds all 10 test cases used for our project. We have test cases for
 * the private functions that are used in assembler.cpp/assembler.h, and two test cases
 * for our algorithms running properly. There is no code implemented for testing the output
 * of our project. Additionally, some of the tests are more extraneous than others, such as those
 * that work to test the population of a data structure. Within the /tests/ folder, there are many
 * .dat files. These are used for testing and parsing data for the rest of our functions.
 * 
 */

std::string GetCurrentWorkingDir(){
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}

// Directory for holding test CSV files
// ./tests/

/**
 * Test case for helper function ParseLine.
 * This is a basic test that confirms ParseLine is capable of populating a vector of strings with the comma separated values
 * of a data file. LineElements is manually prepared with the numbers 1-9, and testLineElements attempts to produce the same
 * vector by reading the file csv1.dat. Of important note regarding ParseLine, is that if the final element of the line
 * does not have a comma following it, it wil not be parsed. In the data files for our project, the last element of the line is
 * not used. This is a corner-cut of the ParseLine function, and is intended.
 */

TEST_CASE("ParseLine parses lines with basic values separated by commas", "[weight=1]"){
    
    // Manual assignment
    std::vector<std::string> LineElements;
    for(int i = 1; i < 10; i++){
        LineElements.push_back(std::to_string(i));
    }

    // Helper function code to be tested
    std::ifstream inputfile;
    inputfile.open("./tests/csv1.dat");

    REQUIRE( inputfile.is_open() );

    std::string line;
    std::vector<std::string> testLineElements;
    while(getline(inputfile, line)){
        testLineElements = ParseLine(line);
    }

    inputfile.close();
    REQUIRE( LineElements == testLineElements );
}

/**
 * Test case for helper function ParseLine.
 * This test case manually populates a vector containing strings called LineElements with the elements "1", "2", and "3,4".
 * That last element has a comma in it, but is wrapped in quotation marks. The quotation marks signify that whatever is within
 * those quotation marks is an element altogether, despite there being a comma. The purpose of this test is to confirm that our
 * helper function is capable of discerning a comma that separates values and a comma within an element.
 */

TEST_CASE("ParseLine parses lines with strings containing commas", "[weight=1]"){

    // Manual assignment
    std::vector<std::string> LineElements;
    LineElements.push_back("1");
    LineElements.push_back("2");
    LineElements.push_back("3,4");

    // Helper function code to be tested
    std::ifstream inputfile;
    inputfile.open("./tests/csv2.dat");

    REQUIRE( inputfile.is_open() );

    std::string line;
    std::vector<std::string> testLineElements;
    while(getline(inputfile, line)){
        testLineElements = ParseLine(line);
    }

    inputfile.close();
    REQUIRE( LineElements == testLineElements );
}

/**
 * Test case for helper function ParseLine.
 * This test case manually populates a vector containings strings called LineElements with the first line of airports.dat, which we use in our
 * actual program. Afterwards, it opens a file containing just the first line of airports.dat, and attempts to populate a
 * vector containing strings called testLineElements with the information that it reads from the data file. If the output is equal,
 * then the function successfully grabs information from a CSV line. The point of this test is to detect any anomalies with taking in
 * numbers and words within the same line.
 */

TEST_CASE("ParseLine parses sample airport data", "[weight=1]"){
    
    // Manual assignment (is there a better way to do this?)
    std::vector<std::string> LineElements;
    LineElements.push_back("1");
    LineElements.push_back("Goroka Airport");
    LineElements.push_back("Goroka");
    LineElements.push_back("Papua New Guinea");
    LineElements.push_back("GKA");
    LineElements.push_back("AYGA");
    LineElements.push_back("-6.081689834590001");
    LineElements.push_back("145.391998291");
    LineElements.push_back("5282");
    LineElements.push_back("10");
    LineElements.push_back("U");
    LineElements.push_back("Pacific/Port_Moresby");
    LineElements.push_back("airport");

    //Helper function code to be tested
    std::ifstream inputfile;
    inputfile.open("./tests/csv3.dat");

    REQUIRE( inputfile.is_open() );

    std::string line;
    std::vector<std::string> testLineElements;
    while(getline(inputfile, line)){
        testLineElements = ParseLine(line);
    }

    inputfile.close();
    REQUIRE( LineElements == testLineElements );
}

// Equality checker helper function, used in GetDistance
bool equal(float a, float b, float epsilon)
{
    if( fabs(a) > fabs(b) ){
        return fabs(b) >= fabs(a-b);
    }
    else{
        return fabs(a) * EPSILON >= fabs(a-b);
    }
}

/**
 * Test case for helper function GetDistance.
 * This tests the calculation ability of GetDistance, between an origin of some latitude and longitude, and a destination different latitude and longitude.
 * Our radius of the Earth used is 3958.8mi. I found a website online that uses this formula with the radius as 3961mi. I ran our calculation
 * using 3961 to confirm that our formula found the same output as a website. So, the validity of this test case fringes upon whether or not that
 * website correctly implemeneted the formula.
 */

TEST_CASE("GetDistance acquires a roughly correct distance in miles between two different points"){
    
    // Manual assignment
    double truedist = 876.9361411138;

    // Helper function code to be tested
    double calc = GetDistance(1, 1, 10, 10);
    bool essentiallyEqual = equal(truedist, calc, EPSILON);
    REQUIRE( essentiallyEqual == true );
}

/**
 * Test case for helper function GetDistance.
 * This tests an edge case of GetDistance, that being an origin and destination being the same point.
 * truedist holds the distance between the same point, which is 0 miles. We run GetDistance with two of the same point, 
 * to confirm the calculation correctly finds the distance is 0.
 */

TEST_CASE("GetDistance acquires the correct distance in miles between the same point twice"){

    // Manual assignment
    double truedist = 0;

    // Helper function code to be tested
    double calc = GetDistance(1, 1, 1, 1);
    REQUIRE( truedist == calc );
}

/**
 * Test case for helper function PopulateIdToName.
 * Note: this test case does not actually call PopulateIdToName, because I couldn't figure out how to pass an input file as an argument in a function.
 * So, this test from while(getline(inputfile, line)){} to inputfile.close(); is the code for PopulateIdToName that you can see in assembler.cpp.
 * This is literally code that has been copied over from assembler.cpp. If you look for a function "PopulateIdToName" being called here, you won't find it.
 * truemap is an unordered_map that holds strings. It is supposed to hold the OpenFlights ID number of an airport as an int, and the airport name as a string.
 * truemap is manually loaded with the correct values. We compare it against algmap, which uses the logic of ParseLine to fill an unordered map.
 */

TEST_CASE("PopulateIdToName properly generates a map that follows the correct format"){
    
    // Manual assignment
    std::unordered_map<int, std::string> truemap;
    truemap[1] = "Goroka Airport";
    truemap[2] = "Madang Airport";
    truemap[3] = "Mount Hagen Kagamuga Airport";
    truemap[4] = "Nadzab Airport";

    // Helper function code to be tested
    std::ifstream inputfile;
    inputfile.open("./tests/csv4.dat");

    REQUIRE( inputfile.is_open() );

    std::unordered_map<int, std::string> algmap;
    std::string line;

    while(getline(inputfile, line)){

        std::vector<std::string> parsed_line = ParseLine(line); //Line of CSV turns into vector of parsed strings

        algmap.insert(std::pair<int, std::string>(std::stoi(parsed_line[0]), parsed_line[1])); //1st element should be id, 2nd the name

    }

    inputfile.close();
    REQUIRE( truemap == algmap );
}

/**
 * Test case for helper function PopulateAirportMapAndCodeToID.
 * The purpose of PopulateAirportMapAndCodeToID is threefold. It creates a node object for each airport, which holds
 * the OpenFlights ID of the airport, the name of the airport, the latitude and longitude of the airport, and
 * the 3-digit IATA code which identifies the airport. Next, it fills a map which uses an airport's ID as an index and
 * the airport node itself as a node. This is essentially the first part of construction of our graph.
 * Lastly, it fills an unordered map that contains airport codes as an index and airport ID's as values.
 * This is so we can translate between airport codes and ID's. This test hopes to confirm that the code
 * in this helper function properly accomplishes those three things by manually creating two airport nodes,
 * and then populating the airport map and airport code to ID map with information from those airport nodes.
 * It then compares the contents.
 */

TEST_CASE("PopulateAirportMapAndCodeToID properly fills a node, airport map, and airport code to ID map"){
    
    // Manual assignment. You can replace the node information, but if you do, replace info in csv5.dat.
    node true_node1;
    true_node1.id = 1;
    true_node1.name = "Goroka Airport";
    true_node1.latitude = -6.081689834590001;
    true_node1.longitude = 145.391998291;
    true_node1.airport_code = "GKA";

    node true_node2;
    true_node2.id = 2;
    true_node2.name = "Madang Airport";
    true_node2.latitude = -5.20707988739;
    true_node2.longitude = 145.789001465;
    true_node2.airport_code = "MAG";

    std::map<int, node> true_map_;
    true_map_.insert(std::pair<int, node>(true_node1.id, true_node1));
    true_map_.insert(std::pair<int, node>(true_node2.id, true_node2));

    std::unordered_map<std::string, int> true_code_to_ID_;
    true_code_to_ID_.insert(std::pair<std::string, int>(true_node1.airport_code, true_node1.id));
    true_code_to_ID_.insert(std::pair<std::string, int>(true_node2.airport_code, true_node2.id));

    // Helper function code to be tested
    std::ifstream inputfile;
    inputfile.open("./tests/csv5.dat");

    REQUIRE( inputfile.is_open() );

    std::string line;
    std::map<int, node> airport_map_;
    std::unordered_map<std::string, int> airport_code_to_ID_;

    enum airport_file{ //corresponds to the CSV file entries
        ID = 0,
        NAME = 1,
        CODE = 4,
        LATITUDE = 6,
        LONGITUDE = 7
    };

    while(getline(inputfile, line)){
        std::vector<std::string> parsed_line = ParseLine(line);

        node airport_node;
        
        airport_node.id = stoi(parsed_line[ID]);
        airport_node.name = parsed_line[NAME];
        airport_node.latitude = stod(parsed_line[LATITUDE]);
        airport_node.longitude = stod(parsed_line[LONGITUDE]);
        airport_node.airport_code = parsed_line[CODE];

        airport_map_.insert(std::pair<int, node>(airport_node.id, airport_node));
        airport_code_to_ID_.insert(std::pair<std::string, int>(airport_node.airport_code, airport_node.id));
    }

    inputfile.close();
    // Testing the contents of the map. There's probably a better way to do this.
    REQUIRE( true_map_.at(true_node1.id).id == airport_map_.at(true_node1.id).id );
    REQUIRE( true_map_.at(true_node1.id).name == airport_map_.at(true_node1.id).name );
    REQUIRE( true_map_.at(true_node1.id).latitude == airport_map_.at(true_node1.id).latitude );
    REQUIRE( true_map_.at(true_node1.id).longitude == airport_map_.at(true_node1.id).longitude );
    REQUIRE( true_map_.at(true_node1.id).airport_code == airport_map_.at(true_node1.id).airport_code );
    REQUIRE( true_map_.at(true_node2.id).id == airport_map_.at(true_node2.id).id );
    REQUIRE( true_map_.at(true_node2.id).name == airport_map_.at(true_node2.id).name );
    REQUIRE( true_map_.at(true_node2.id).latitude == airport_map_.at(true_node2.id).latitude );
    REQUIRE( true_map_.at(true_node2.id).longitude == airport_map_.at(true_node2.id).longitude );
    REQUIRE( true_map_.at(true_node2.id).airport_code == airport_map_.at(true_node2.id).airport_code );

    // Testing the contents of the unordered map.
    REQUIRE( true_code_to_ID_ == airport_code_to_ID_ );

}

/**
 * This is a test case to match the code in our program in PopulateRouteMap.
 * There aren't any helper functions within this function that populates an unordered map that we haven't
 * tested already, so we're just testing to see if our struct called edge properly contains information.
 * In theory, this implementation matches how the process populates the entire route map, which is several thousands
 * more data points than in this test case. So if this works, that should work.
 */

TEST_CASE("Edge works properly as a struct to hold data required for project specification"){
    std::string line;
    
    //code to test
    std::ifstream inputfile;
    inputfile.open("./tests/csv6.dat");

    enum route_file{ //corresponds to the CSV file entries
        AIRLINE_ID = 1,
        SOURCE_ID = 3,
        DESTINATION_IATA = 4,
        DESTINATION_ID = 5
    };

    edge trueedge;
    trueedge.start_id = 2965;
    trueedge.end_id = 2990;
    
    edge realedge;

    while(getline(inputfile, line)){
        std::vector<std::string> parsed_line = ParseLine(line);
        
        realedge.start_id = stoi(parsed_line[SOURCE_ID]);
        realedge.end_id = stoi(parsed_line[DESTINATION_ID]);
    }


    inputfile.close();

    REQUIRE(trueedge.start_id == realedge.start_id);
    REQUIRE(trueedge.end_id == realedge.end_id);
    
}

/**
 * Test case for public function FindShortestPath.
 * This test case utilizes our copied class, TestAssembler, which is literally just Assembler from assembler.cpp/assembler.h.
 * The reason it is copied over into a new class is for ease in testing. The goal of this test is to produce a double-ended queue of
 * integers that represent the airports that you visit in order to get from airport A to airport B. In the project code, FindShortestPath
 * returns a vector of strings which is an itinerary of flights to take in readable format. In this test code, we simply want to prove
 * that the algorithm returns the airports that you have to visit, in the form of their IDs. The case we use is from ORD (O'Hare) to MNL (Manila).
 * To come up with our dataset, we used four airports: ORD (O'Hare), NRT (Narita International), PVG (Shanghai), and MNL (Manila). We know that
 * it takes less time to go from ORD -> NRT -> MNL, so if we put PVG into the dataset, the algorithm should detect that the shortest path
 * is from ORD -> NRT -> MNL. truepath holds the airport ID codes of those airports, and FindShortestPath should return the same three airport ID codes.
 */

TEST_CASE("FindShortestPath properly finds the shortest path"){

    // Manual assignment
    std::deque<int> truepath = {3830, 2279, 2397};

    // Code to be tested
    TestAssembler testasm("./tests/airport.dat", "./tests/airline.dat", "./tests/route.dat");
    std::deque<int> algpath = testasm.FindShortestPath("ORD", "MNL");
    REQUIRE( truepath == algpath );
}

/**
 * Test case for public function FindLandMarkPath.
 * This test case uses FindShortestPath twice to find the shortest path from A to B given an intermediate destination.
 * We know that to get from ORD (O'Hare) to MNL (Manila), you can visit either NRT (Narita) or PVG (Shanghai). PVG is longer
 * in terms of distance, so FindShortestPath will always choose to go to NRT. Therefore, if we choose PVG as the intermediate
 * destination, then FindLandMarkPath will produce the path ORD -> PVG -> MNL. In our algorithm for FindLandMarkPath,
 * the airport code of the intermediate destination is in the double ended queue twice, because we're simply running
 * FindShortestPath twice, and it has to have a start, which is in this case, the end of the previous FindShortestPath.
 * Therefore, truepath holds the airport ID code for ORD, PVG, PVG, MNL. If the test case passes, FindLandMarkPath reproduces
 * that set of integers.
 */

TEST_CASE("FindLandmarkPath properly finds the shortest path based on intermediate destination"){
    
    // Manual assignment
    std::deque<int> truepath = {3830, 3406, 3406, 2397};

    // Code to be tested
    TestAssembler testasm("./tests/airport.dat", "./tests/airline.dat", "./tests/route.dat");
    std::deque<int> algpath = testasm.FindLandMarkPath("ORD", "PVG", "MNL");
    REQUIRE( truepath == algpath );

}
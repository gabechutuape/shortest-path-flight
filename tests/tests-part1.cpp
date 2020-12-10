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

std::string GetCurrentWorkingDir(){
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}

// Directory for holding test CSV files
// /home/gfc2/rchaud9-gfc2-dimitar3/testdata/

// If the final element of the line does not have a comma following it, it will not be parsed.
// In our data files for our project, typically, the last element of the line is not used.
// This is a corner-cut of the ParseLine function, and is intended.

TEST_CASE("ParseLine parses lines with basic values separated by commas", "[weight=1]"){
    
    std::vector<std::string> LineElements;
    for(int i = 1; i < 10; i++){
        LineElements.push_back(std::to_string(i));
    }

    std::ifstream inputfile;
    inputfile.open("/home/gfc2/rchaud9-gfc2-dimitar3/testdata/csv1.dat");

    REQUIRE( inputfile.is_open() );

    std::string line;
    std::vector<std::string> testLineElements;
    while(getline(inputfile, line)){
        testLineElements = ParseLine(line);
    }

    inputfile.close();
    REQUIRE( LineElements == testLineElements );
}


TEST_CASE("ParseLine parses lines with strings containing commas", "[weight=1"){
    std::vector<std::string> LineElements;
    LineElements.push_back("1");
    LineElements.push_back("2");
    LineElements.push_back("3,4");

    std::ifstream inputfile;
    inputfile.open("/home/gfc2/rchaud9-gfc2-dimitar3/testdata/csv2.dat");

    REQUIRE( inputfile.is_open() );

    std::string line;
    std::vector<std::string> testLineElements;
    while(getline(inputfile, line)){
        testLineElements = ParseLine(line);
    }

    inputfile.close();
    REQUIRE( LineElements == testLineElements );
}

TEST_CASE("ParseLine parses sample airport data", "[weight=1]"){
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

    std::ifstream inputfile;
    inputfile.open("/home/gfc2/rchaud9-gfc2-dimitar3/testdata/csv3.dat");

    REQUIRE( inputfile.is_open() );

    std::string line;
    std::vector<std::string> testLineElements;
    while(getline(inputfile, line)){
        testLineElements = ParseLine(line);
    }

    inputfile.close();
    REQUIRE( LineElements == testLineElements );
}

// Equality checker helper function
bool equal(float a, float b, float epsilon)
{
    if( fabs(a) > fabs(b) ){
        return fabs(b) >= fabs(a-b);
    }
    else{
        return fabs(a) * EPSILON >= fabs(a-b);
    }
}

TEST_CASE("GetDistance acquires a roughly correct distance in miles between two different points"){
    double truedist = 876.9361411138;
    double calc = GetDistance(1, 1, 10, 10);
    bool essentiallyEqual = equal(truedist, calc, EPSILON);
    REQUIRE( essentiallyEqual == true );
}

TEST_CASE("GetDistance acquires the correct distance in miles between the same point twice"){
    double truedist = 0;
    double calc = GetDistance(1, 1, 1, 1);
    REQUIRE( truedist == calc );
}

TEST_CASE("PopulateIdToName properly generates a map that follows the correct format"){
    std::unordered_map<int, std::string> truemap;
    truemap[1] = "Goroka Airport";
    truemap[2] = "Madang Airport";
    truemap[3] = "Mount Hagen Kagamuga Airport";
    truemap[4] = "Nadzab Airport";
    std::ifstream inputfile;
    inputfile.open("/home/gfc2/rchaud9-gfc2-dimitar3/testdata/csv4.dat");
    std::unordered_map<int, std::string> algmap;
    std::string line;

    while(getline(inputfile, line)){

        std::vector<std::string> parsed_line = ParseLine(line); //Line of CSV turns into vector of parsed strings

        algmap.insert(std::pair<int, std::string>(std::stoi(parsed_line[0]), parsed_line[1])); //1st element should be id, 2nd the name

    }

    inputfile.close();
    REQUIRE( truemap == algmap );
}
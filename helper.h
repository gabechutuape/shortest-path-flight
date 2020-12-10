#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <map>
#include <queue>
#include <unordered_set>

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
* Traverse graph and uses Dijkstra's algo to find shortest path between two airports
* @return vector of strings corresponding to airport id's in the path
*/ 
std::vector<std::string> FindShortestPath(const std::string& begin, const std::string& end);

/**
* Edge of graph
*/
struct edge{
    int start_id; //source - unique openflights identifier
    int end_id; //destination - unique openflights identifier
    double distance;
    std::string airport_code;
    int airline_id;
    std::string airline_name;

    friend bool operator<(const edge& a, const edge& b){
        return a.distance < b.distance;
    }
    friend bool operator>(const edge& a, const edge& b){
        return a.distance > b.distance;
    }
};

/**
* Function generates an unordered map that contains an ID and a name of an airport, theoretically
*/
std::unordered_map<int, std::string> PopulateIdToName(std::fstream& airline_file_);
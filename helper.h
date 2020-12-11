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
 * Node of graph
 */
struct node{
    int id;
    std::string name;
    double latitude;
    double longitude;
    std::string airport_code;
};

/**
* Function generates an unordered map that contains an ID and a name of an airport, theoretically
*/
std::unordered_map<int, std::string> PopulateIdToName(std::fstream& airline_file_);

std::vector<std::string> FindShortestPath(const std::string& begin, const std::string& end);

enum ERRORS{
    NO_ROUTE,
    START_NOT_FOUND,
    END_NOT_FOUND,
    START_AND_END_EQUAL
};

class TestAssembler{
    public:
        /**
         * Constructor for Assembler
         * Takes in file paths as strings for the three required files
         */ 
        TestAssembler(const std::string& airport_file, const std::string& airline_file, const std::string& route_file);

        /**
         * Destructor
         */ 
        ~TestAssembler();

        /**
         * Copy constructor
         */ 
        TestAssembler(const TestAssembler& other);

        /**
         * Copy assignment
         */ 
        TestAssembler& operator=(const TestAssembler& other);

        /**
         * Traverse graph and uses Dijkstra's algo to find shortest path between two airports
         * @return vector of strings corresponding to airport id's in the path
         */ 
        std::deque<int> FindShortestPath(const std::string& begin, const std::string& end);

        /**
         * Finds all airlines (edges) between two airports(nodes)
         */ 
        std::vector<edge> FindEdges(int first_id, int second_id);

        /**
         * Finds the shortest path between 3 points
         * Uses FindShortestPath twice and concatenates the resulting vector
         */ 
        std::deque<int> FindLandMarkPath(const std::string& begin, const std::string& mid, const std::string& end);

    private:
        void Copy(const TestAssembler& other);
        void Delete();

        std::string airport_file_;
        std::string airline_file_;
        std::string route_file_;

        std::unordered_map<int, std::string> airline_ID_to_name_;
        std::map<int, node> airport_map_;
        std::unordered_map<std::string, int> airport_code_to_ID_;
        std::unordered_map<int, std::vector<edge>> route_map_;


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

        /**
         * Populates hash map of airport id's to edges
         * Reads from route_file_ and writes to route_map_;
         */
        void PopulateRouteMap();

};
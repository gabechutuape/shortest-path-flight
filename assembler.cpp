#include "assembler.h"

using namespace std;

Assembler::Assembler(const std::string& airport_file, const std::string& airline_file, const std::string& route_file){
    airport_file_ = airport_file;
    airline_file_ = airline_file;
    route_file_ = route_file;
    //Add functions for constructing graph
    PopulateIdToName();
}

Assembler::~Assembler(){
    Delete();
}

Assembler::Assembler(const Assembler& other){
    Copy(other);
}

Assembler& Assembler::operator=(const Assembler& other){
    if (this != &other)
    {
        Delete();
        Copy(other);
    }
    return *this;
}

vector<string> Assembler::ParseLine(const string &line){
    char current_character;
    string current_string;
    bool quotation_flag = false;
    vector<string> line_elements;

    // Loop through all characters of line
    for(size_t i = 0; i < line.size(); ++i){
        current_character = line[i]; 

        // If the previous character is a quotation mark,
        if(quotation_flag){
            if( current_character == '"' && i+1 < line.size() ){
                if( line[i+1] == '"' ){
                    current_string += '"';
                    ++i;
                }
                else {
                    quotation_flag = false;
                }
            }
            else {
                current_string += current_character;
            }
        }
        // If the previous character is not a quotation mark:
        else{
            if( current_character == '"' ){
                quotation_flag = true;
            }
            else if( current_character == ',' ){
                line_elements.push_back(current_string);
                current_string.clear();
            }
            else {
                current_string += current_character;
            }
        }
    }
    return line_elements;
}
double Assembler::GetDistance(double lat1, double long1, double lat2, double long2){
    double latitude_1 = lat1 * M_PI / 180.;
    double longitude_1 = long1 * M_PI / 180.;
    double latitude_2 = lat2 * M_PI / 180.;
    double longitude_2 = long2 * M_PI / 180.;

    double difLat = abs(latitude_1 - latitude_2);
    double difLong = abs(longitude_1 - longitude_2);

    double a = pow(sin(difLat / 2), 2) + (cos(latitude_1) * cos(latitude_2) * pow(sin(difLong / 2), 2)); //square of half the chord length 

    double c = 2 * atan2(sqrt(a), sqrt(1-a)); //angular distance in radians

    const double kEarthRadius = 3958.8; //in miles

    double distance = c * kEarthRadius;

    return distance;
}

void Assembler::PopulateIdToName(){
    ifstream inputFile(airline_file_);
    string line;

    while(getline(inputFile, line)){

        vector<string> parsed_line = ParseLine(line); //Line of CSV turns into vector of parsed strings

        airline_ID_to_name_.insert(pair<int, string>(stoi(parsed_line[0]), parsed_line[1])); //1st element should be id, 2nd the name
    }

    inputFile.close();
}

void Assembler::PopulateAirportMapAndCodeToID(){
    ifstream inputFile(airport_file_);
    string line;

    enum airport_file{ //corresponds to the CSV file entries
        ID = 0,
        NAME = 1,
        CODE = 4,
        LATITUDE = 6,
        LONGITUDE = 7
    };

    while(getline(inputFile, line)){
        vector<string> parsed_line = ParseLine(line);

        node airport_node;
        
        airport_node.id = stoi(parsed_line[ID]);
        airport_node.name = parsed_line[NAME];
        airport_node.latitude = stoi(parsed_line[LATITUDE]);
        airport_node.longitude = stoi(parsed_line[LONGITUDE]);
        airport_node.airport_code = parsed_line[CODE];

        airport_map_.insert(pair<int, node>(airport_node.id, airport_node));
        airport_code_to_ID_.insert(pair<string, int>(airport_node.airport_code, airport_node.id));
    }

    inputFile.close();
}
void Assembler::PopulateRouteMap(){
    ifstream inputFile(airport_file_);
    string line;

    enum route_file{ //corresponds to the CSV file entries
        AIRLINE_ID = 1,
        SOURCE_ID = 3,
        DESTINATION_IATA = 4,
        DESTINATION_ID = 5
    };

    while(getline(inputFile, line)){
        vector<string> parsed_line = ParseLine(line);

        int source_id = stoi(parsed_line[SOURCE_ID]);
        int dest_id = stoi(parsed_line[DESTINATION_ID]);

        //If source and destination exist: add to route_map_
        if (airport_map_.find(source_id) != airport_map_.end() && 
        airport_map_.find(dest_id) != airport_map_.end())
        {
            edge route;

            //Creates blank entry if a previous one didn't exist
            if (route_map_.find(source_id) == route_map_.end())
            {
                route_map_.insert(pair<int, vector<edge>>(source_id, vector<edge>()));
            }

            route.start_id = source_id;
            route.end_id = dest_id;
            route.airport_code = parsed_line[DESTINATION_IATA];
            route.airline_id = stoi(parsed_line[AIRLINE_ID]);

            //Check if airport exists
            if (airline_ID_to_name_.find(route.airline_id) != airline_ID_to_name_.end())
            {
                route.airline_name = airline_ID_to_name_[route.airline_id];
            }
            else{
                route.airline_name = "Unknown Airline";
            }

            route.distance = GetDistance(airport_map_[source_id].latitude, airport_map_[source_id].longitude,
             airport_map_[dest_id].latitude, airport_map_[dest_id].longitude);

            route_map_[source_id].push_back(route); //places route in proper edge vector
        }
    }
    inputFile.close();
}

void Assembler::Delete(){
    airport_file_.clear();
    airline_file_.clear();
    route_file_.clear();
    //add more to delete graph
}
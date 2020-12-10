#include "helper.h"
#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <map>
#include <queue>
#include <unordered_set>
#include <iostream>

using namespace std;

vector<string> ParseLine(const string &line){
    char current;
    bool isQuote = false;
    string builtStr = "";
    vector<string> outputStrings;

    // Cycle through all characters
    for(size_t i = 0; i < line.size(); ++i) {
        current = line[i];

        // Pushes string into vector when comma found
        if(!isQuote) {
            if(current == ',') {
                outputStrings.push_back(builtStr);
                builtStr = string();
            }
            else if(current == '"')
                isQuote = true;
            else
                builtStr += current;
        }

        // Checks for matching quotation marks and removes from output
        else {
            if(current == '"' && i+1 < line.size()) {
                if(line[i+1] == '"') {
                    builtStr += '"';
                    ++i;
                }
                else
                    isQuote = false;
            }
            else
                builtStr += current;
        }
    }
    return outputStrings;
}

double GetDistance(double lat1, double long1, double lat2, double long2){
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

/*
vector<string> FindShortestPath(const std::string& begin, const std::string& end){
    //Existence checks
    if (airport_code_to_ID_.find(begin) == airport_code_to_ID_.end())
    {
        throw "Beginning not found";
    }
    if (airport_code_to_ID_.find(end) == airport_code_to_ID_.end())
    {
        throw "End not found";
    }
    if (begin == end)
    {
        throw "Beginning and End are the same";
    }
    
    int start_id = airport_code_to_ID_[begin];
    int end_id = airport_code_to_ID_[end];
    
    priority_queue<pair<double, edge>> prior_queue;
    unordered_set<int> traversed;
    unordered_map<int, int> parent_id;
    
    vector<edge> connecting_edges = route_map_[start_id];
    traversed.insert(start_id);

    //initial case
    for (size_t i = 0; i < connecting_edges.size(); i++)
    {
        prior_queue.push(pair<double, edge>(-1.0 * connecting_edges[i].distance, connecting_edges[i]));
    }
    
    int next_id = -1;
    double next_distance;

    while (!prior_queue.empty() && next_id != end_id)
    {
        next_distance = prior_queue.top().first;
        next_id = prior_queue.top().second.end_id;
        edge temp = prior_queue.top().second;
        prior_queue.pop();

        if (traversed.find(next_id) == traversed.end())
        {
            parent_id.insert(pair<int,int>(temp.end_id, temp.start_id));
            connecting_edges = route_map_[next_id];
            for (size_t i = 0; i < connecting_edges.size(); i++)
            {
                prior_queue.push(pair<double, edge>(-1 * connecting_edges[i].distance + next_distance, connecting_edges[i]));
            }
            traversed.insert(next_id);
        }
    }
    //If no possible route
    if (prior_queue.empty() && next_id != end_id)
    {
        throw "No possible route";
    }
    deque<int> path;
    int parent = end_id;
    while (parent != start_id)
    {
        path.push_front(parent);
        parent = parent_id[parent];
    }
    path.push_front(parent);

    vector<string> trip;
    PopulateTrip(path, trip);
    return trip;
}
*/
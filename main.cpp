#include <iostream>
#include "assembler.h"
#include <algorithm>

using namespace std;

/**
 * Prototypes
 */ 
void FindStartAndEnd(string& start_code, string& end_code); //Find start and end airport codes and sets entered strings equal to user input
bool IsValidCode(const string& code); //checks if user inputted code is of valid format
void PrintTrip(const vector<string>& trip); //Prints the trip in user friendly manner
void FindStartMidAndEnd(string& start_code, string& mid_code, string& end_code); //Finds start, mid and end airport codes
bool IsLandMark(); //If user inputs "Y" or "y" for an intermediate destination
void ToUpper(string& text); //Capitalizes strings entered

int main()
{
    Assembler assembler("airports.dat", "airlines.dat", "routes.dat");
    string start_code;
    string mid_code;
    string end_code;

    try
    {
        if (IsLandMark())
        {
            FindStartMidAndEnd(start_code, mid_code, end_code);

            ToUpper(start_code);
            ToUpper(mid_code);
            ToUpper(end_code);

            PrintTrip(assembler.FindLandMarkPath(start_code, mid_code, end_code));
        }
        else
        {
            FindStartAndEnd(start_code, end_code);

            ToUpper(start_code);
            ToUpper(end_code);

            PrintTrip(assembler.FindShortestPath(start_code, end_code));
        }
    }
    catch(ERRORS e)
    {
        cout << "ERROR: ";
        if (e == NO_ROUTE)
        {
            cout << "No route found" << endl;
        }
        else if (e == START_NOT_FOUND)
        {
            cout << "Starting airport not found" << endl;
        }
        else if (e == END_NOT_FOUND)
        {
            cout << "Ending airport not found" << endl;
        }
        else if (e == START_AND_END_EQUAL)
        {
            cout << "Starting and stopping points cannot be the same" << endl;
        }
    }
}

bool IsLandMark(){
    cout<<"Do you wish to make a stop somewhere? (Y/N) ";
    string input;
    cin >> input;
    
    while (input != "Y" && input != "y" && input != "N" &&input != "n")
    {
        cout << "Enter either Y or N :";
        cin >> input;
    }
    if (input == "Y" || input == "y")
    {
        return true;
    }
    return false;

}

void FindStartAndEnd(string& start_code, string& end_code){
    cout << "Enter IATA code of starting airport: ";
    cin >> start_code;
    while (!IsValidCode(start_code))
    {
        cout << "Incorrect format. Try Again: ";
        cin >> start_code;
    }

    cout << "Enter IATA code of destination airport: ";
    cin >> end_code;
    while (!IsValidCode(end_code))
    {
        cout << "Incorrect format. Try Again: ";
        cin >> end_code;
    }
}

void FindStartMidAndEnd(string& start_code, string& mid_code, string& end_code){
    cout << "Enter IATA code of starting airport: ";
    cin >> start_code;
    while (!IsValidCode(start_code))
    {
        cout << "Incorrect format. Try Again: ";
        cin >> start_code;
    }

    cout<< "Enter IATA code of intermediate destination: ";
    cin >> mid_code;
    while (!IsValidCode(mid_code))
    {
        cout << "Incorrect format. Try Again: ";
        cin >> mid_code;
    }
    
    cout << "Enter IATA code of destination airport: ";
    cin >> end_code;
    while (!IsValidCode(end_code))
    {
        cout << "Incorrect format. Try Again: ";
        cin >> end_code;
    }
}

bool IsValidCode(const string& code){
    if (code.size() != 3)
    {
        return false;
    }

    for (size_t i = 0; i < 3; i++)
    {
        if (!isalpha(code[i]))
        {
            return false;
        }
    }
    return true;
}

void PrintTrip(const vector<string>& trip){
    cout << endl << "TRIP"<< endl;
    for (size_t i = 0; i < trip.size(); i++)
    {
        cout<<trip[i] << endl << endl;
    }
    cout << endl;
}

void ToUpper(string& text){
    transform(text.begin(), text.end(), text.begin(), ::toupper);
}
#include <iostream>
#include "assembler.h"

using namespace std;


void FindStartAndEnd(string& start_code, string& end_code);
bool IsValidCode(const string& code);
void PrintTrip(const vector<string>& trip);


int main()
{
    Assembler assembler("airports.dat", "airlines.dat", "routes.dat");
    string start_code;
    string end_code;

    try
    {
        FindStartAndEnd(start_code, end_code);
        PrintTrip(assembler.FindShortestPath(start_code, end_code));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

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
        cout<<trip[i] << endl;
    }
    cout << endl;
}
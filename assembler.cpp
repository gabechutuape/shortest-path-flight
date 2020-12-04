#include "assembler.h"

using namespace std;

Assembler::Assembler(const std::string& airport_file, const std::string& airline_file, const std::string& route_file){
    airport_file_ = airport_file;
    airline_file_ = airline_file;
    route_file_ = route_file;
    //Add a function for constructing graph
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

void Assembler::Delete(){
    airport_file_.clear();
    airline_file_.clear();
    route_file_.clear();
    //add more to delete graph
}
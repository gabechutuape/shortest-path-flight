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

void Assembler::Delete(){
    airport_file_.clear();
    airline_file_.clear();
    route_file_.clear();
    //add more to delete graph
}
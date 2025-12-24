#include "../include/ExpenseCategory.h"
#include "iomanip"
using namespace std;

ExpenseCategory::ExpenseCategory(int id, string name): id(id), name(name){}

int ExpenseCategory::getId()const{
    return id;
}

string ExpenseCategory::getName()const{
    return name;
}

void ExpenseCategory::setName(const string& newname){
    name = newname;
}

void ExpenseCategory::write2Binary(ofstream& out)const{
    out.write((char*)&id, sizeof(id));
    size_t sz = name.size();
    out.write((char*)&sz, sizeof(sz));
    out.write(name.c_str(), sz);
}

void ExpenseCategory::readFromBinary(ifstream& in){
    in.read((char*)&id, sizeof(id));
    size_t sz;
    in.read((char*)&sz, sizeof(sz));
    name.resize(sz);
    in.read(&name[0], sz);
}

void ExpenseCategory::display() const {
    cout << left << setw(10) << id 
         << setw(30) << name << endl;
}
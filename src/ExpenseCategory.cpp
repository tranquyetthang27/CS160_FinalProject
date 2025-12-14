#include "../include/ExpenseCategory.h"
#include "iostream"
#include "string"
#include "iomanip"

#include<string>
#include<fstream>

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

void ExpenseCategory::display()const{
    cout << '| ' << setw(5) << left << id << " | " << setw(20) << left << name << "\n";
}

void ExpenseCategory::write2Binary(ofstream &out) const
{
    out.write((char*)&id, sizeof(id));

    size_t sz = name.size();
    out.write((char*)&sz, sizeof(sz));
    out.write(name.c_str(), sz);
}

void ExpenseCategory::readFromBinary(ifstream &inp)
{
    inp.read((char*)&id, sizeof(id));

    int sz = 0;
    inp.read((char*)&sz, sizeof(sz));
    name.resize(sz);
    inp.read(&name[0], sz);
}

#include "../include/IncomeSource.h"

#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

IncomeSource::IncomeSource(int id, string name): id(id), name(name) {}

int IncomeSource::getID() const
{
    return id;
}

string IncomeSource::getName() const
{
    return name;
}

void IncomeSource::setName(const string &newName)
{
    name = newName;
}

void IncomeSource::Display() const
{
    cout << "| " << setw(5) << left << id << " | " << setw(20) << left << name << '\n';
}

void IncomeSource::write2Binary(ofstream &out) const
{
    out.write((char*)&id, sizeof(id));
    size_t sz = name.size();
    out.write((char*)&sz, sizeof(sz));
    out.write(name.c_str(), sz);
}

void IncomeSource::readFromBinary(ifstream &inp)
{
    inp.read((char*)&id, sizeof(id));
    size_t sz = 0;
    inp.read((char*)&sz, sizeof(sz));
    name.resize(sz);
    inp.read(&name[0], sz);
}

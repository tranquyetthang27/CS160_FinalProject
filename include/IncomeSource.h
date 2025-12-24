#ifndef INCOMESOURCE_H
#define INCOMESOURCE_H

#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

class IncomeSource
{
private:
    int id;
    string name;

public:
    IncomeSource(int id, string name);
    IncomeSource(): id(0), name("") {}

    int getID() const;
    string getName() const;
    void setName(const string &newName);
    void Display() const;

    void write2Binary(ofstream &out) const;
    void readFromBinary(ifstream &inp);
    void display() const {
    cout << left << setw(10) << id 
         << setw(30) << name << endl;
    }
};

#endif // INCOMESOURCE_H

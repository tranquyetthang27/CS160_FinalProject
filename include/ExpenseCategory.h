#ifndef EXPENSECATEGORY_H
#define EXPENSECATEGORY_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ExpenseCategory{
private:
    int id;
    string name;

public:
    ExpenseCategory(): id(0), name("") {}
    ExpenseCategory(int id, string name);
    int getId() const;
    string getName() const;
    void setName(const string& newname);
    void display()const;

    void write2Binary(ofstream &out) const;
    void readFromBinary(ifstream &inp);
};

#endif EXPENSECATEGORY_H

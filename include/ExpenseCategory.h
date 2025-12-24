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
    void write2Binary(ofstream& out)const;
    void readFromBinary(ifstream& in);
    ExpenseCategory() = default;
    ExpenseCategory(int id, string name);
    int getId() const;
    string getName() const;
    void setName(const string& newname);
    void display()const;


};

#endif 
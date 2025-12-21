#ifndef EXPENSECATEGORY_H
#define EXPENSECATEGORY_H
#include <iostream>
#include <string>
using namespace std;

class ExpenseCategory{
private:
    int id;
    string name;

public:
    ExpenseCategory() = default;
    ExpenseCategory(int id, string name);
    int getId() const;
    string getName() const;
    void setName(const string& newname);
    
};

#endif 
#include "../include/ExpenseCategory.h"
#include "iostream"
#include "string"
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

void ExpenseCategory::display()const{
    cout << '| ' << setw(5) << left << id << " | " << setw(20) << left << name << "\n"; 
}
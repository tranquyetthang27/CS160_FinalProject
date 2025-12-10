#include "../include/Expense.h"
#include <string>
#include "DynamicArray.h"
#include "Date.h"
#include <iomanip> 
//#include "Wallet.h"
using namespace std;

Expense:: Expense(const Date& date, const long long& amount, const int& wid, const int& cid, const string& decs)
    : date(date), amount(amount), walletId(wid), categoryId(cid), description(decs){}

Date Expense::getDate()const{return date;}

long long Expense::getAmount()const{return amount;}

int Expense::getWalletId()const{return walletId;}

int Expense::getCategoryId()const{return categoryId;}

string Expense::getDescription()const{return description;}

void Expense::addExpense(/*Wallet& wallet,*/ DynamicArray<Expense>&list){
    list.push_back(*this);
    //wallet.adjustBalance(-amount);
}

string Expense::getDescription()const{
    cout << '|';
    date.toString();
    cout << " | " << setw(15) << right << amount << "VND | " << setw(5) << right <<walletId <<" | " << setw(5) << right << categoryId
    <<" | " << setw(30) << left << description << "\n";
}


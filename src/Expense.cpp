#include "../include/Expense.h"
#include <string>
#include "../include/DynamicArray.h"
#include "../include/Date.h"
#include <iomanip> 
#include "../include/Wallet.h"
using namespace std;

Expense:: Expense(const Date& date, const long long& amount, const int& wid, const int& cid, const string& decs)
    : date(date), amount(amount), walletId(wid), categoryId(cid), description(decs){}

Date Expense::getDate()const{return date;}

long long Expense::getAmount()const{return amount;}

int Expense::getWalletId()const{return walletId;}

int Expense::getCategoryId()const{return categoryId;}


void Expense::addExpense(Wallet& wallet, DynamicArray<Expense>&list){
    list.push_back(*this);
    wallet.adjustBalance(-amount);
}

void Expense::getDescription()const{
    cout << '|';
    date.toString();
    cout << " | " << setw(15) << right << amount << "VND | " << setw(5) << right <<walletId <<" | " << setw(5) << right << categoryId
    <<" | " << setw(30) << left << description << "\n";
}


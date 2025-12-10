#ifndef EXPENSE_H
#define EXPENSE_H
#include <string>
#include "Date.h"
#include "DynamicArray.h"
using namespace std;

class Expense{
private:
    Date date;
    long long amount;
    int walletId;
    int categoryId;
    string description;
public:
    Expense(const Date& date,const long long& amount, const int& wid, const int& cid, const string& desc = "");
    Date getDate()const;
    long long getAmount()const;
    int getWalletId()const;
    int getCategoryId()const;
    string getDescription()const;
    void addExpense(/*Wallet& wallet,*/ DynamicArray<Expense>&list);
};


#endif
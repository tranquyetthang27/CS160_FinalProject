#ifndef EXPENSE_H
#define EXPENSE_H
#include <string>
#include "Date.h"
#include "DynamicArray.h"
#include "Wallet.h"
using namespace std;

class Expense{
private:
    Date date;
    long long amount;
    int walletId;
    int categoryId;
    string description;
public:
    void write2Binary(ofstream& out)const;
    void readFromBinary(ifstream& in);
    Expense(const Date& date,const long long& amount, const int& wid, const int& cid, const string& desc = "");
    Expense() = default;
    Date getDate()const;
    long long getAmount()const;
    int getWalletId()const;
    int getCategoryId()const;
    void addExpense(Wallet& wallet, DynamicArray<Expense>&list);
};


#endif
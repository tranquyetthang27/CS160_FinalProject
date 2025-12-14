#ifndef INCOME_H
#define INCOME_H

#include<string>
#include<fstream>

#include "Date.h"
#include "DynamicArray.h"
#include "Wallet.h"

using namespace std;

class Income
{
private:
    Date date;
    long long amount;
    int walletID;
    int sourceID;
    string description;

public:
    Income(): date(1, 1, 2000), amount(0), walletID(0), sourceID(0), description("") {}

    Income(const Date& date, const long long &amount, const int &walletID, const int &sourceID, const string &description);

    Date getDate() const;
    long long getAmount() const;
    int getWalletID() const;
    int getSourceID() const;
    void getDescription() const;

    void AddIncome(Wallet &wallet, DynamicArray<Income> &list);

    void write2Binary(ofstream &out) const;
    void readFromBinary(ifstream &inp);
};

#endif // INCOME_H

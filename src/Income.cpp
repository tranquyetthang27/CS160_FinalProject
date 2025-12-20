#include "../include/Income.h"
#include "../include/DynamicArray.h"
#include "../include/Date.h"
#include "../include/Wallet.h"

#include<string>
#include<iomanip>

using namespace std;

Income::Income(const Date& date, const long long &amount, const int &walletID, const int &sourceID, const string &description)
             : date(date), amount(amount), walletID(walletID), sourceID(sourceID), description(description) {}

Date Income::getDate() const
{
    return date;
}

long long Income::getAmount() const
{
    return amount;
}

int Income::getWalletID() const
{
    return walletID;
}

int Income::getSourceID() const
{
    return sourceID;
}

void Income::getDescription() const
{
    cout << "|";
    date.toString();
    cout << " | " << setw(15) << right << amount << "VND | ";
    cout << setw(5) << right << walletID << " | ";
    cout << setw(5) << right << sourceID << " | ";
    cout << setw(30) << left << description << '\n';
}

void Income::AddIncome(Wallet &wallet, DynamicArray<Income> &list)
{
    list.push_back(*this);
    wallet.adjustBalance(amount);
}

void Income::write2Binary(ofstream &out) const
{
    date.write2Binary(out);

    out.write((char*)&amount, sizeof(amount));
    out.write((char*)&walletID, sizeof(walletID));
    out.write((char*)&sourceID, sizeof(sourceID));

    size_t sz = description.size();
    out.write((char*)&sz, sizeof(sz));
    out.write(description.c_str(), sz);
}

void Income::readFromBinary(ifstream &inp)
{
    date.readFromBinary(inp);

    inp.read((char*)&amount, sizeof(amount));
    inp.read((char*)&walletID, sizeof(walletID));
    inp.read((char*)&sourceID, sizeof(sourceID));

    int sz = 0;
    inp.read((char*)&sz, sizeof(sz));
    description.resize(sz);
    inp.read(&description[0], sz);
}

#include "../include/Expense.h"
#include <string>
#include "../include/DynamicArray.h"
#include "../include/Date.h"
#include <iomanip>
#include "../include/Wallet.h"
using namespace std;

Expense::Expense()
    : date(1, 1, 2000), amount(0), walletId(0), categoryId(0), description("") {}

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

void Expense::write2Binary(ofstream &out) const
{
    date.write2Binary(out);

    out.write((char*)&amount, sizeof(amount));
    out.write((char*)&walletId, sizeof(walletId));
    out.write((char*)&categoryId, sizeof(categoryId));

    size_t sz = description.size();
    out.write((char*)&sz, sizeof(sz));
    out.write(description.c_str(), sz);
}

void Expense::readFromBinary(ifstream &inp)
{
    date.readFromBinary(inp);

    inp.read((char*)&amount, sizeof(amount));
    inp.read((char*)&walletId, sizeof(walletId));
    inp.read((char*)&categoryId, sizeof(categoryId));

    int sz = 0;
    inp.read((char*)&sz, sizeof(sz));
    description.resize(sz);
    inp.read(&description[0], sz);
}

#include "../include/Expense.h"
#include <iomanip> 
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

void Expense::write2Binary(ofstream& out)const{
    date.write2Binary(out);
    out.write((char*)&amount, sizeof(long long));
    out.write((char*)&walletId, sizeof(int));
    out.write((char*)&categoryId, sizeof(int));
    size_t sz = description.size();
    out.write((char*)&sz, sizeof(sz));
    out.write(description.c_str(), sz);
}

void Expense::readFromBinary(ifstream& in){
    date.readFromBinary(in);
    in.read((char*)&amount, sizeof(long long));
    in.read((char*)&walletId, sizeof(int));
    in.read((char*)&categoryId, sizeof(int));
    size_t sz;
    in.read((char*)&sz, sizeof(sz));
    description.resize(sz);
    in.read(&description[0], sz);
}


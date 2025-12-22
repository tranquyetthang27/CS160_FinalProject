#include "../include/RecurringExpense.h"
#include <iomanip> 
using namespace std;


RecurringExpense::RecurringExpense(int id, const Date& startDate, RecurrencePeriod period, const long long& amount, const int& wid, const int& cid, const string& decs)
    : id(id), startDate(startDate), period(period), amount(amount), walletId(wid), categoryId(cid), description(decs){}

Date RecurringExpense::getStartDate()const{return startDate;}

int RecurringExpense::getId()const{return id;}

long long RecurringExpense::getAmount()const{return amount;}

int RecurringExpense::getWalletId()const{return walletId;}

int RecurringExpense::getCategoryId()const{return categoryId;}

RecurrencePeriod RecurringExpense::getPeriod()const{return period;}

Expense RecurringExpense::createExpense(const Date& date){
    return {date, amount, walletId, categoryId, description };
}

string RecurringExpense::getDescription()const{
    return description;
}

void RecurringExpense::setStartDay(const Date& date){startDate.changeDate(date);};

void RecurringExpense::write2Binary(ofstream& out)const{
    out.write((char*)&id, sizeof(id));
    startDate.write2Binary(out);
    int periodVal = static_cast<int>(period);
    out.write((char*)&periodVal, sizeof(periodVal));
    out.write((char*)&amount, sizeof(amount));
    out.write((char*)&walletId, sizeof(walletId));
    out.write((char*)&categoryId, sizeof(categoryId));
    size_t sz = description.size();
    out.write((char*)&sz, sizeof(sz));
    out.write(description.c_str(), sz);
}

void RecurringExpense::readFromBinary(ifstream& in){
    in.read((char*)&id, sizeof(id));
    startDate.readFromBinary(in);
    int periodVal;
    in.read((char*)&periodVal, sizeof(periodVal));
    period = static_cast<RecurrencePeriod>(periodVal);
    in.read((char*)&amount, sizeof(amount));
    in.read((char*)&walletId, sizeof(walletId));
    in.read((char*)&categoryId, sizeof(categoryId));
    size_t sz;
    in.read((char*)&sz, sizeof(sz));
    description.resize(sz);
    in.read(&description[0], sz);
}
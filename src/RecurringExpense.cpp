#include "../include/RecurringExpense.h"
#include <iomanip>
using namespace std;

RecurringExpense::RecurringExpense()
    : id(0), startDate(1, 1, 2000), period(Monthly), amount(0), walletId(0), categoryId(0), description("") {}

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

void RecurringExpense::write2Binary(ofstream &out) const
{
    out.write((char*)&id, sizeof(id));
    startDate.write2Binary(out);
    out.write((char*)&period, sizeof(period));
    out.write((char*)&amount, sizeof(amount));
    out.write((char*)&walletId, sizeof(walletId));
    out.write((char*)&categoryId, sizeof(categoryId));

    size_t sz = description.size();
    out.write((char*)&sz, sizeof(sz));
    out.write(description.c_str(), sz);
}

void RecurringExpense::readFromBinary(ifstream &inp)
{
    inp.read((char*)&id, sizeof(id));
    startDate.readFromBinary(inp);
    inp.read((char*)&period, sizeof(period));
    inp.read((char*)&amount, sizeof(amount));
    inp.read((char*)&walletId, sizeof(walletId));
    inp.read((char*)&categoryId, sizeof(categoryId));

    int sz = 0;
    inp.read((char*)&sz, sizeof(sz));
    description.resize(sz);
    inp.read(&description[0], sz);
}

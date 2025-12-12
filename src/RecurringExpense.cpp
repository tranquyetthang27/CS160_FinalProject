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

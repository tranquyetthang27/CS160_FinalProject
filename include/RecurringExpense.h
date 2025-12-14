#ifndef RECURRINGEXPENSE_H
#define RECURRINGEXPENSE_H
#include <string>
#include "Date.h"
#include "DynamicArray.h"
#include "Wallet.h"
#include "Expense.h"
using namespace std;

enum RecurrencePeriod{
    Daily = 1,
    Weekly = 2,
    Monthly = 3,
    Annually = 4
};

class RecurringExpense{
private:
    int id;
    Date startDate;
    RecurrencePeriod period;
    long long amount;
    int walletId;
    int categoryId;
    string description;
public:
    RecurringExpense();
    RecurringExpense(int id, const Date& startdate,RecurrencePeriod period,const long long& amount, const int& wid, const int& cid, const string& desc = "");
    int getId() const;
    Date getStartDate()const;
    RecurrencePeriod getPeriod()const;
    long long getAmount()const;
    int getWalletId()const;
    int getCategoryId()const;
    string getDescription()const;
    Expense createExpense(const Date& date);
    void setStartDay(const Date& date);

    void write2Binary(ofstream &out) const;
    void readFromBinary(ifstream &inp);
};


#endif

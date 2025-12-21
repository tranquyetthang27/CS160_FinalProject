#ifndef STATISTICS_H
#define STATISTICS_H
#include "Date.h"
#include "Expense.h"
#include "DynamicArray.h"
#include "ExpenseCategory.h"
#include "Income.h"
using namespace std;

class Statistics{
public:
    Statistics() = default;
    long long calcNetBalance(const Date& start, const Date& end, const DynamicArray<Income>& in, const DynamicArray<Expense>& ex);
    void reportByWallet(const DynamicArray<Wallet>& wallets, const DynamicArray<Expense>& Expenses);
    void reportAnnualOverview(const int& year, const DynamicArray<Income>& in, const DynamicArray<Expense>& ex);
    void groupDataByCategory(const DynamicArray<ExpenseCategory>& ExCate, const DynamicArray<Expense>& ex);
};

#endif 
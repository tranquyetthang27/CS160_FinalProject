#ifndef FILEHANDLER_H
#define FILDHANDLER_H

#include<string>
#include<iostream>
#include "DynamicArray.h"
#include "RecurringExpense.h"

using namespace std;

class Wallet;
class Expense;
class Income;
class ExpenseCategory;
class IncomeSource;

class FileHandler
{
private:
    const string m_dataFilePath = "data.json";

public:
    FileHandler() = default;

    bool saveData(
        const DynamicArray<Wallet> &wallets,
        const DynamicArray<ExpenseCategory> &expenseCategories,
        const DynamicArray<IncomeSource> &incomeSources,
        const DynamicArray<Expense> &expenses,
        const DynamicArray<Income> &incomes,
        const DynamicArray<RecurringExpense>& recurringList
    );

    bool loadData(
        DynamicArray<Wallet> &wallets,
        DynamicArray<ExpenseCategory> &expenseCategories,
        DynamicArray<IncomeSource> &incomeSources,
        DynamicArray<Expense> &expenses,
        DynamicArray<Income> &incomes,
        DynamicArray<RecurringExpense>& recurringLists
    );
};

#endif

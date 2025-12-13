#ifndef FILEHANDLER_H
#define FILDHANDLER_H

#include<string>
#include<iostream>
#include "DynamicArray.h"

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
    FileHander() = default;

    bool saveData(
        const DynamicArray<Wallet> &wallets,
        const DynamicArray<ExpenseCategory> &expenseCategories,
        const DynamicArray<IncomeSource> &incomeSources,
        const DynamicArray<Expense> &expenses,
        const DynamicArray<Income> &incomes
    );

    bool loadData(
        DynamicArray<Wallet> &wallets,
        DynamicArray<ExpenseCategory> &expenseCategories,
        DynamicArray<IncomeSource> &incomeSources,
        DynamicArray<Expense> &expenses,
        DynamicArray<Income> &incomes
    );
};

#endif

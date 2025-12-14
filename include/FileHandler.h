#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include<string>
#include<iostream>
#include<fstream>

#include "DynamicArray.h"

using namespace std;

class Wallet;
class Expense;
class Income;
class ExpenseCategory;
class IncomeSource;
class RecurringManager;

///-----TEMPLATE-----

template<typename T>
void writeArray2Binary(const DynamicArray<T> &arr, ofstream &out)
{
    int sz = arr.getSize();
    out.write((char*)&sz, sizeof(sz));
    for (int i = 0; i < sz; ++i)
    {
        arr[i].write2Binary(out);
    }
}

template<typename T>
void readArrayFromBinary(DynamicArray<T> &arr, ifstream &inp)
{
    arr.clear();
    int sz = 0;

    inp.read((char*)&sz, sizeof(sz));
    for (int i = 0; i < sz; ++i)
    {
        T tmp;
        tmp.readFromBinary(inp);
        arr.push_back(tmp);
    }
}

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
        const DynamicArray<RecurringManager> &recurringManager
    );

    bool loadData(
        DynamicArray<Wallet> &wallets,
        DynamicArray<ExpenseCategory> &expenseCategories,
        DynamicArray<IncomeSource> &incomeSources,
        DynamicArray<Expense> &expenses,
        DynamicArray<Income> &incomes,
        DynamicArray<RecurringManager> &recurringManager
    );
};

#endif

#include "../include/FileHandler.h"
#include "../include/Wallet.h"
#include "../include/Expense.h"
#include "../include/Income.h"
#include "../include/ExpenseCategory.h"
#include "../include/IncomeSource.h"
#include "../include/RecurringManager.h"
#include<fstream>

using namespace std;

///--------IMPLEMENTATION---------

bool FileHandler::saveData(
    const DynamicArray<Wallet> &wallets,
    const DynamicArray<ExpenseCategory> &expenseCategories,
    const DynamicArray<IncomeSource> &incomeSources,
    const DynamicArray<Expense> &expenses,
    const DynamicArray<Income> &incomes,
    const DynamicArray<RecurringManager> &recurringManager)
{
    ofstream out(m_dataFilePath, ios::out | ios::binary);
    if (!out)
    {
        cerr << "Cannot open file for saving!\n";
        return false;
    }

    try
    {
        writeArray2Binary(wallets, out);
        writeArray2Binary(expenseCategories, out);
        writeArray2Binary(incomeSources, out);
        writeArray2Binary(expenses, out);
        writeArray2Binary(incomes, out);
        writeArray2Binary(recurringManager, out);
    }
    catch(const std::exception &e)
    {
        cerr << "Error during binary serialization " << e.what() << '\n';
        out.close();
        return false;
    }
    out.close();
    cout << "Finish storing data to " << m_dataFilePath << "!\n";
    return true;
}

bool FileHandler::loadData(
    DynamicArray<Wallet> &wallets,
    DynamicArray<ExpenseCategory> &expenseCategories,
    DynamicArray<IncomeSource> &incomeSources,
    DynamicArray<Expense> &expenses,
    DynamicArray<Income> &incomes,
    DynamicArray<RecurringManager> &recurringManager)
{
    ifstream inp(m_dataFilePath, ios::in | ios::binary);
    if (!inp)
    {
        cerr << "Cannot open data file for uploading!\n";
        return true;
    }

    try
    {
        readArrayFromBinary(wallets, inp);
        readArrayFromBinary(expenseCategories, inp);
        readArrayFromBinary(incomeSources, inp);
        readArrayFromBinary(expenses, inp);
        readArrayFromBinary(incomes, inp);
        readArrayFromBinary(recurringManager, inp);
    }
    catch(const std::exception &e)
    {
        cerr << "Error during binary serialization " << e.what() << '\n';
        inp.close();
        return false;
    }

    inp.close();
    cout << "Finish uploading data from " << m_dataFilePath << "!\n";
    return true;
}

#include "../include/FileHandler.h"
#include "../include/ExpenseCategory.h"
#include "../include/IncomeSource.h"


using namespace std;

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

///--------IMPLEMENTATION---------

bool FileHandler::saveData(
    const DynamicArray<Wallet> &wallets,
    const DynamicArray<ExpenseCategory> &expenseCategories,
    const DynamicArray<IncomeSource> &incomeSources,
    const DynamicArray<Expense> &expenses,
    const DynamicArray<Income> &incomes,
    const DynamicArray<RecurringExpense>& recurringList)
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
    DynamicArray<RecurringExpense>& recurringList)
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

#ifndef APPMENU_H
#define APPMENU_H
#include "RecurringManager.h"
#include "Statistics.h"
#include "IncomeSource.h"
#include "FileHandler.h"
#include<cstdlib>
using namespace std;

class AppMenu{
private:
    DynamicArray<Expense> Expenses;
    DynamicArray<ExpenseCategory> ExpenseCategories;
    DynamicArray<Wallet> Wallets;
    DynamicArray<IncomeSource> IncomeSources;
    DynamicArray<Income> Incomes;

    Statistics stats;
    RecurringManager recurring;
    FileHandler fileHandler;

    int nextWalletId;
    int nextCategogyId;
    int nextSourceId;

    Wallet* findWalletById(const int id);
    ExpenseCategory* findCategoryById(const int id);
    void displayMainMenu();
    void handleTransactionMenu();
    void handleReportMenu();
    void handleSetupMenu();
    void handleNetBalanceReport();
    void handleAnnualReport();

    void inputNewExpense();
    void inputNewCategory();
    void inputNewIncome();
    void inputNewSource();
    void inputNewWallet();
    void listAllWallets();
    void listAllCategories();
    void listAllIncomeSources();
    void editCategory();
    void editSource();
    void editWallet();

public:
    AppMenu();
    void run();
    void loadData();
    void saveData();
};

#endif
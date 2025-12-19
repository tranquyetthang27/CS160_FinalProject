#include "..\include\Statistics.h"
#include <iomanip>
#include <algorithm>

using namespace std;

long long Statistics::calcNetBalance(const Date& start, const Date& end, const DynamicArray<Income>& in, const DynamicArray<Expense>& ex){
    int Total = 0;
    for(int i = 0; i < ex.getSize(); i++){
        if(ex[i].getDate().isBetween(start, end)){
            Total -= ex[i].getAmount();
        }
    }
    for(int i = 0; i < in.getSize(); i++){
        if(in[i].getDate().isBetween(start, end)){
            Total += in[i].getAmount();
        }
    }
    return Total;
}

void Statistics::reportByWallet(const DynamicArray<Wallet>& wallets, const DynamicArray<Expense>& Expenses){
    if(Expenses.isEmpty()){
        cout << "No expense transactions found for wallet statistics.\n";
        return;
    }
    struct ReportItem{
        int walletId;
        long long totalExpense;
    };
    DynamicArray<ReportItem> reportData;
    for(int i = 0; i < Expenses.getSize(); i++){
        int targetID = Expenses[i].getWalletId();
        bool found = false;
        for(int j = 0; j < reportData.getSize(); j ++){
            if(reportData[j].walletId == targetID){
                reportData[j].totalExpense += Expenses[i].getAmount();
                found = true;
                break;
            }
        }
        if(!found){
            ReportItem newItem = {targetID, Expenses[i].getAmount()};
            reportData.push_back(newItem);
        }
    }
    for(int i = 0; i < reportData.getSize(); i ++){
        for(int j = i + 1; j < reportData.getSize(); i ++){
            if(reportData[i].totalExpense < reportData[j].totalExpense)swap(reportData[i], reportData[j]);
        }
    }
    cout << "\n=======================================================\n";
    cout << "                EXPENSE REPORT BY WALLET \n";
    cout << "=======================================================\n";
    cout << "| " << setw(25) << left << "WALLET NAME" 
              << " | " << setw(18) << right << "TOTAL EXPENSE (VND)" << " |\n";
    cout << "-------------------------------------------------------\n" ;

    for(int i = 0; i < reportData.getSize(); i++){
        string walletName = "";
        for(int j = 0; j < wallets.getSize(); j++){
            if(wallets[j].getID() == reportData[i].walletId){
                walletName = wallets[j].getName();
                break;
            }
        }
        cout << "| " << setw(25) << left << walletName
                  << " | " << setw(15) << right << reportData[i].totalExpense << " |\n" ;
    }
    cout << "=======================================================\n";
}

void Statistics::reportAnnualOverview(const int& year, const DynamicArray<Income>& in, const DynamicArray<Expense>& ex){
    long long monthlyIncome[13] = {0};
    long long monthlyExpense[13] = {0};
    long long totalIncome = 0;
    long long totalExpense = 0;
    for(int i = 0; i < ex.getSize(); i++){
        if(ex[i].getDate().get_year() == year){
            totalExpense += ex[i].getAmount();
            monthlyExpense[ex[i].getDate().get_month()] += ex[i].getAmount();
        }
    }
    for(int i = 0; i < in.getSize(); i++){
        if(in[i].getDate().get_year() == year){
            totalIncome += in[i].getAmount();
            monthlyIncome[in[i].getDate().get_month()] += in[i].getAmount();
        }
    }
    cout << "\n==================================================================================" << "\n";
    cout << "                            ANNUAL OVERVIEW REPORT: " << year << "\n";
    cout << "==================================================================================" << "\n";
    cout << "| " << setw(8) << "MONTH" 
              << " | " << setw(18) << right << "INCOME (VND)" 
              << " | " << setw(18) << right << "EXPENSE (VND)" 
              << " | " << setw(18) << right << "NET BALANCE (VND)" << " |" << "\n";
    cout << "----------------------------------------------------------------------------------" << "\n";

    for (int m = 1; m <= 12; ++m) {
        long long netBalance = monthlyIncome[m] - monthlyExpense[m];
        cout << "| " << setw(8) << m 
                  << " | " << setw(18) << right << monthlyIncome[m]
                  << " | " << setw(18) << right << monthlyExpense[m]
                  << " | " << setw(18) << right << netBalance << " |" << "\n";
    }
    
    cout << "----------------------------------------------------------------------------------" << "\n";
    cout << "| " << setw(8) << "TOTAL" 
              << " | " << setw(18) << right << totalIncome
              << " | " << setw(18) << right << totalExpense
              << " | " << setw(18) << right << (totalIncome - totalExpense) << " |" << "\n";
    cout << "==================================================================================" << "\n";
}

void Statistics::groupDataByCategory(const DynamicArray<ExpenseCategory>& Categories, const DynamicArray<Expense>& Expenses){
    if(Expenses.isEmpty()){
        cout << "No expense transactions found for category statistics.\n";
        return;
    }
    struct ReportItem{
        int catogoryId;
        long long totalExpense;
    };
    DynamicArray<ReportItem> reportData;
    for(int i = 0; i < Expenses.getSize(); i++){
        int targetID = Expenses[i].getCategoryId();
        bool found = false;
        for(int j = 0; j < reportData.getSize(); j ++){
            if(reportData[j].catogoryId == targetID){
                reportData[j].totalExpense += Expenses[i].getAmount();
                found = true;
                break;
            }
        }
        if(!found){
            ReportItem newItem = {targetID, Expenses[i].getAmount()};
            reportData.push_back(newItem);
        }
    }
    for(int i = 0; i < reportData.getSize(); i ++){
        for(int j = i + 1; j < reportData.getSize(); i ++){
            if(reportData[i].totalExpense < reportData[j].totalExpense)swap(reportData[i], reportData[j]);
        }
    }
    cout << "\n=======================================================\n";
    cout << "               EXPENSE REPORT BY CATEGORY \n";
    cout << "=======================================================\n";
    cout << "| " << setw(25) << left << "CATEGORY" 
              << " | " << setw(18) << right << "TOTAL EXPENSE (VND)" << " |\n";
    cout << "-------------------------------------------------------\n" ;

    for(int i = 0; i < reportData.getSize(); i++){
        string categoryName = "";
        for(int j = 0; j < Categories.getSize(); j++){
            if(Categories[j].getId() == reportData[i].catogoryId){
                categoryName = Categories[j].getName();
                break;
            }
        }
        cout << "| " << setw(25) << left << categoryName
                  << " | " << setw(15) << right << reportData[i].totalExpense << " |\n" ;
    }
    cout << "=======================================================\n";
}
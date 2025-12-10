#include "..\include\Statistics.h"
#include "..\include\DynamicArray.h"
#include "..\include\Expense.h"
#include "..\include\ExpenseCategory.h"
// #include "..\include\Income.h"
// #include "..\include\Wallet.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

long long Statistics::calcNetBalance(const Date& start, const Date& end, /*const DynamicArray<Income>& in,*/ const DynamicArray<Expense>& ex){
    int Total = 0;
    for(int i = 0; i < ex.getSize(); i++){
        if(ex[i].getDate().isBetween(start, end)){
            Total -= ex[i].getAmount();
        }
    }
    // for(int i = 0; i < in.getSize(); i++){
    //     if(in[i].getDate().isBetween(start, end)){
    //         Total += in[i].getAmount();
    //     }
    // }
    return Total;
}

void Statistics::reportByWallet(/*const DynamicArray<Wallet>& wallets,*/ const DynamicArray<Expense>& Expenses){
    if(Expenses.isEmpty()){
        cout << "Khong co giao dich Chi tieu nao de thong ke theo Vi.\n";
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
    cout << "\n=======================================================\n";
    cout << "          BAO CAO CHI TIEU THEO VI TIEN \n";
    cout << "=======================================================\n";
    cout << "| " << setw(25) << left << "TEN VI" 
              << " | " << setw(15) << right << "TONG CHI (VND)" << " |\n";
    cout << "-------------------------------------------------------\n" ;

    for(int i = 0; i < reportData.getSize(); i++){
        string walletName = "";
        // for(int j = 0; j < wallets.getSize(); j++){
        //     if(wallets[j].getId() == reportData[i].walletId){
        //         walletname = wallets[j].getName();
        //         break;
        //     }
        // }
        cout << "| " << setw(25) << left << walletName
                  << " | " << setw(15) << right << reportData[i].totalExpense << " |\n" ;
    }
    cout << "=======================================================\n";
}

void Statistics::reportAnnualOverview(const int& year, /*const DynamicArray<Income>& in,*/ const DynamicArray<Expense>& ex){
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
    // for(int i = 0; i < in.getSize(); i++){
    //     if(in[i].getDate().get_year() == year){
    //         totalIncome += in[i].getAmount();
    //         monthlyIncome[in[i].getDate().get_month()] += in[i].getAmount();
    //     }
    // }
    cout << "\n==================================================================================" << "\n";
    cout << "                          BAO CAO TONG QUAN NAM " << year << "\n";
    cout << "==================================================================================" << "\n";
    cout << "| " << setw(8) << "THANG" 
              << " | " << setw(15) << right << "THU NHAP (VND)" 
              << " | " << setw(15) << right << "CHI TIEU (VND)" 
              << " | " << setw(15) << right << "SO DU RONG (VND)" << " |" << "\n";
    cout << "----------------------------------------------------------------------------------" << "\n";

    for (int m = 1; m <= 12; ++m) {
        long long netBalance = monthlyIncome[m] - monthlyExpense[m];
        cout << "| " << setw(8) << m 
                  << " | " << setw(15) << right << monthlyIncome[m]
                  << " | " << setw(15) << right << monthlyExpense[m]
                  << " | " << setw(15) << right << netBalance << " |" << "\n";
    }
    
    cout << "----------------------------------------------------------------------------------" << "\n";
    cout << "| " << setw(8) << "TONG" 
              << " | " << setw(15) << right << totalIncome
              << " | " << setw(15) << right << totalExpense
              << " | " << setw(15) << right << (totalIncome - totalExpense) << " |" << "\n";
    cout << "==================================================================================" << "\n";
}

void groupDataByCategory(const DynamicArray<ExpenseCategory>& ExCate, const DynamicArray<Expense>& ex);
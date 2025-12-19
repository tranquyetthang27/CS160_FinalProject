#include "../include/RecurringManager.h"
#include <iomanip>
#include <algorithm>
using namespace std; 

Date RecurringManager::calculateNextDueDate(const Date& lastDate, RecurrencePeriod period) const {
    Date nextDate = lastDate; 

    switch (period) {
        case Daily:
            nextDate.addDays(1); 
            break;
        case Weekly:
            nextDate.addDays(7);
            break;
        case Monthly:
            nextDate.addMonths(1); 
            break;
        case Annually:
            nextDate.addYears(1); 
            break;
        default:
            nextDate.addDays(1);
            break;
    }
    return nextDate;
}

void RecurringManager::addRecurringExpense(
    RecurrencePeriod period,
    const Date& startDate,
    long long amount,
    int walletId,
    int categoryId,
    const string& description
){
    RecurringExpense newRule(
        nextRecurringId, 
        startDate,
        period,
        amount,
        walletId,
        categoryId,
        description
    );
    recurringList.push_back(newRule);
    nextRecurringId++;
}

void RecurringManager::processDueExpenses(const Date& currentDate, DynamicArray<Expense>& expenses, DynamicArray<Wallet>& wallets) {
    if (recurringList.isEmpty()) {
        return;
    }

    int transactionsCreated = 0;
    for (int i = 0; i < recurringList.getSize(); i++) {
        Date nextDueDate = calculateNextDueDate(recurringList[i].getStartDate(), recurringList[i].getPeriod());
        while (nextDueDate <= currentDate) {
            Expense newExpense = recurringList[i].createExpense(nextDueDate);
            Wallet* targetWallet = nullptr;
            for (int j = 0; j < wallets.getSize(); ++j) {
                if (wallets[j].getID() == newExpense.getWalletId()) {
                    targetWallet = &wallets[j];
                    break;
                }
            }
            newExpense.addExpense(*targetWallet, expenses);
            recurringList[i].setStartDay(nextDueDate); 
            transactionsCreated ++;
            nextDueDate = calculateNextDueDate(recurringList[i].getStartDate(), recurringList[i].getPeriod());
        }
    }

    if (transactionsCreated > 0) {
        cout << "=======================================================" << "\n";
        cout << "COMPLETED: Created " << transactionsCreated << " actual recurring transactions." << "\n";
        cout << "=======================================================" << "\n";
    } else {
        cout << "No recurring transactions are due today." << "\n";
    }
}

void RecurringManager::displayRecurringList() const {
    if (recurringList.isEmpty()) {
        cout << "No recurring expense rules have been created." << "\n";
        return;
    }
    
    cout << "\n==================================================================================" << "\n";
    cout << "                         LIST OF RECURRING EXPENSE RULES " << "\n";
    cout << "==================================================================================" << "\n";

    cout << "| " << setw(5) << "ID" 
              << " | " << setw(10) << "PERIOD" 
              << " | " << setw(12) << "START DATE" 
              << " | " << setw(15) << right << "AMOUNT"
              << " | " << setw(30) << left << "DESCRIPTION" << " |" << "\n";
    cout << "----------------------------------------------------------------------------------" << "\n";

    for (int i = 0; i < recurringList.getSize(); ++i) {
        const RecurringExpense& item = recurringList[i];
        
        string periodStr;
        switch (item.getPeriod()) {
            case Daily: periodStr = "Daily"; break;
            case Weekly: periodStr = "Weekly"; break;
            case Monthly: periodStr = "Monthly"; break;
            case Annually: periodStr = "Annualy"; break;
            default: periodStr = "Unknown"; break;
        }

        cout << "| " << setw(5) << item.getId()
                  << " | " << setw(10) << periodStr
                  << " | " << setw(12) << item.getStartDate().toString() 
                  << " | " << setw(15) << right << item.getAmount()
                  << " | " << setw(30) << left << item.getDescription() << " |" << "\n";
    }
    cout << "==================================================================================" << "\n";
}

void RecurringManager::setNextRecurringId(int id){
    nextRecurringId = id;
}

int RecurringManager::getMaxId()const{
    int res = -1;
    for(int i = 0; i < recurringList.getSize(); i ++){
        res = max(res, recurringList[i].getId());
    }
    return res;
}
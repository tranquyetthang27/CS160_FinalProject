#include "../include/RecurringManager.h"
#include <iomanip>
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
        cout << "HOAN THANH: Da tao " << transactionsCreated << " giao dich dinh ky thuc te." << "\n";
        cout << "=======================================================" << "\n";
    } else {
        cout << "Khong co giao dich dinh ky nao den han trong hom nay." << "\n";
    }
}

void RecurringManager::displayRecurringList() const {
    if (recurringList.isEmpty()) {
        cout << "Khong co quy tac chi tieu dinh ky nao duoc tao." << "\n";
        return;
    }
    
    cout << "\n==================================================================================" << "\n";
    cout << "                          DANH SACH QUY TAC CHI TIEU DINH KY " << "\n";
    cout << "==================================================================================" << "\n";

    cout << "| " << setw(5) << "ID" 
              << " | " << setw(10) << "CHU KY" 
              << " | " << setw(12) << "NGAY BAT DAU" 
              << " | " << setw(15) << right << "SO TIEN"
              << " | " << setw(30) << left << "MO TA" << " |" << "\n";
    cout << "----------------------------------------------------------------------------------" << "\n";

    for (int i = 0; i < recurringList.getSize(); ++i) {
        const RecurringExpense& item = recurringList[i];
        
        string periodStr;
        switch (item.getPeriod()) {
            case Daily: periodStr = "Hang ngay"; break;
            case Weekly: periodStr = "Hang tuan"; break;
            case Monthly: periodStr = "Hang thang"; break;
            case Annually: periodStr = "Hang nam"; break;
            default: periodStr = "Khong xac dinh"; break;
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
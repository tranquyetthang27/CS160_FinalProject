#ifndef RECURRINGMANAGER_H
#define RECURRINGMANAGER_H

#include "RecurringExpense.h"
class RecurringManager {
private:
    DynamicArray<RecurringExpense> recurringList;
    int nextRecurringId = 1; 
    Date calculateNextDueDate(const Date& lastDate, RecurrencePeriod period) const;

public:
    RecurringManager() = default;
    void addRecurringExpense(
        RecurrencePeriod period,
        const Date& startDate,
        long long amount,
        int walletId,
        int categoryId,
        const std::string& description
    );

    void processDueExpenses(const Date& currentDate, DynamicArray<Expense>& expenses, DynamicArray<Wallet>& wallets);

    void displayRecurringList() const;
    
    void setNextRecurringId(int id);

    int getMaxId()const;

    DynamicArray<RecurringExpense>& getRecurringList() { return recurringList; }
};

#endif
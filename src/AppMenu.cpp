#include "../include/AppMenu.h"
#include <iomanip>
#include <limits>
using namespace std;

AppMenu::AppMenu(){
    cout << "Initializing Financial Management Application...\n";
}

void AppMenu::run(){
    loadData();
    Date currentDate = Date::get_date();
    cout << "\n==========================================" << "\n";
    cout << "CHECKING DUE RECURRING TRANSACTIONS (" << currentDate.toString() << ")" << "\n";
    recurring.processDueExpenses(currentDate, Expenses, Wallets);
    cout << "==========================================" << "\n";
    int choice;
    do{
        displayMainMenu();
        cout << "Enter choice:";
        if(!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            continue;
        }
        switch (choice){
            case 1:
                handleTransactionMenu();
                break;
            case 2:
                handleReportMenu();
                break;
            case 3:
                handleSetupMenu();
                break;
            case 0:
                saveData();
                cout << "Exiting application. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << "\n";
        }  
    }while(choice);
}


void AppMenu::loadData(){
    if((fileHandler.loadData(Wallets, ExpenseCategories, IncomeSources, Expenses, Incomes, recurring.getRecurringList()))){
        recurring.setNextRecurringId(recurring.getMaxId());
        for(int i = 0; i < ExpenseCategories.getSize(); i++){
            nextCategogyId = max(nextCategogyId, ExpenseCategories[i].getId());
        }
        for(int i = 0; i < Wallets.getSize(); i++){
            nextWalletId = max(nextWalletId, Wallets[i].getID());
        }
        for(int i = 0; i < IncomeSource.getSize(); i++){
            nextSourceId = max(nextSourceId, IncomeSource[i].getID());
        }
        cout << "Data loaded successfully." << "\n";
    }
    else{
        cout << "No existing data found. Initializing empty database..." << "\n";
    }
}

void AppMenu::saveData(){
    cout << "Saving data..." << "\n";
    fileHandler.saveData(Wallets, ExpenseCategories, IncomeSources, Expenses, Incomes, recurring.getRecurringList());
    cout << "Data saved successfully." << "\n";
}

void AppMenu::handleReportMenu(){
    int choice;
    do {
        cout << "\n--- REPORT & STATISTICS MENU ---" << "\n";
        cout << "1. View Recurring Expense Rules" << "\n"; 
        cout << "2. Calculate Net Balance over Period" << "\n"; 
        cout << "3. Report by Wallet" << "\n";                  
        cout << "4. Report Annual Overview" << "\n";         
        cout << "5. Group Expenses by Category" << "\n";      
        cout << "0. Back to Main Menu" << "\n";
        cout << "Enter choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
            case 1:
                recurring.displayRecurringList();
                break;
            case 2:
                handleNetBalanceReport();
                break;
            case 3:
                stats.reportByWallet(Wallets, Expenses); 
                break;
            case 4:
                handleAnnualReport();
                break;
            case 5:
                stats.groupDataByCategory(ExpenseCategories, Expenses);
                break;
            case 0:
                cout << "Returning to Main Menu." << "\n";
                break;
            default:
                cout << "Invalid choice." << "\n";
        }
    } while (choice != 0);
}

void AppMenu::handleNetBalanceReport() {
    int startDay, startMonth, startYear;
    int endDay, endMonth, endYear;
    
    cout << "\n--- CALCULATE NET BALANCE ---" << "\n";
    
    cout << "Enter Start Date (DD MM YYYY): ";
    if (!(cin >> startDay >> startMonth >> startYear)) {
        cout << "Invalid date format." << "\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    Date startDate(startDay, startMonth, startYear);

    cout << "Enter End Date (DD MM YYYY): ";
    if (!(cin >> endDay >> endMonth >> endYear)) {
        cout << "Invalid date format." << "\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    Date endDate(endDay, endMonth, endYear);

    if (startDate >= endDate && !(startDate == endDate) ) {
        cout << "Error: Start date must be before or equal to End date." << "\n";
        return;
    }

    long long balance = stats.calcNetBalance(startDate, endDate, Expenses);
    
    cout << "\n--- REPORT ---" << "\n";
    cout << "Net Balance from " << startDate.toString() << " to " << endDate.toString() << ": " << balance << " VND" << "\n";
}

void AppMenu::handleAnnualReport() {
    int year;
    cout << "\n--- ANNUAL OVERVIEW REPORT ---" << "\n";
    cout << "Enter Year (YYYY): ";
    if (!(cin >> year) || year <= 0) {
        cout << "Invalid year." << "\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    stats.reportAnnualOverview(year, Expenses);
}

void AppMenu::handleTransactionMenu() {
    int choice;
    do {
        cout << "\n--- TRANSACTION MENU ---" << "\n";
        cout << "1. Input New Expense" << "\n";
        cout << "2. Input New Income" << "\n";
        cout << "0. Back to Main Menu" << "\n"; 
        cout << "Enter choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
            case 1:
                inputNewExpense();
                break;
            case 2:
                inputNewIncome();
                break;
            case 0:
                cout << "Returning to Main Menu." << "\n";
                break;
            default:
                cout << "Invalid choice." << "\n";
        }
    } while (choice != 0);
}

void AppMenu::handleSetupMenu() {
    int choice;
    do {
        cout << "\n--- SETUP & CONFIGURATION MENU ---" << "\n";
        cout << "1. Add New Expense Category" << "\n"; 
        cout << "2. Add New Income Source" << "\n";
        cout << "0. Back to Main Menu" << "\n";
        switch (choice) {
            case 1:
                inputNewCategory(); 
                break;
            case 2:
                inputNewSource();
                break;
            case 0:
                cout << "Returning to Main Menu." << "\n";
            default:
                cout << "Invalid choice." << "\n";
        }
    } while (choice != 0);
}

void AppMenu::inputNewExpense() {
    cout << "\n--- INPUT NEW EXPENSE ---" << "\n";
    long long amount;
    int walletId, categoryId, periodChoice;
    string desc;

    cout << "Enter Expense Amount (VND): ";
    if (!(cin >> amount) || amount <= 0) {
        cout << "Error: Invalid or non-positive amount." << "\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    cout << "Enter ID of the Wallet used: ";
    if (!(cin >> walletId)) {
        cout << "Error: Invalid Wallet ID format." << "\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    Wallet* targetWallet = findWalletById(walletId);
    if (!targetWallet) {
        cout << "Error: Wallet with ID " << walletId << " not found." << "\n";
        return;
    }
    
    if (targetWallet->getBalance() < amount) {
        cout << "Error: Insufficient balance in Wallet " << targetWallet->getName() 
             << " (" << targetWallet->getBalance() << " VND)." << "\n";
        return;
    }

    cout << "Enter ID of the Expense Category: ";
    if (!(cin >> categoryId)) {
        cout << "Error: Invalid Category ID format." << "\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (!findCategoryById(categoryId)) {
        cout << "Error: Category with ID " << categoryId << " not found." << "\n";
        return;
    }

    cout << "Enter Transaction Description (e.g., Coffee Purchase): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, desc);

    cout << "Do you want this expense to repeat?" << "\n";
    cout << "  (0: No, 1: Daily, 2: Weekly, 3: Monthly, 4: Annually): ";
    if (!(cin >> periodChoice)) {
        cout << "Error: Invalid recurrence choice." << "\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    if (periodChoice == 0) {
        Expense newExp(Date::get_date(), amount, walletId, categoryId, desc); 
        newExp.addExpense(*targetWallet, Expenses);
        cout << ">> Single Expense transaction recorded successfully." << "\n";
    } else if (periodChoice >= 1 && periodChoice <= 4) {
        RecurrencePeriod period = static_cast<RecurrencePeriod>(periodChoice);
        
        recurring.addRecurringExpense(period, Date::get_date(), amount, walletId, categoryId, desc);
        
        cout << ">> Recurring Expense Rule created successfully. The first transaction will be processed on the next run." << "\n";
    } else {
        cout << "Error: Invalid choice for recurrence type." << "\n";
    }
}

void AppMenu::inputNewCategory() {
    cout << "\n--- ADD NEW EXPENSE CATEGORY ---" << "\n";
    string name;
    
    cout << "Enter Category Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, name);
    
    if (name.empty()) {
        cout << "Error: Category name cannot be empty." << "\n";
        return;
    }

    ExpenseCategory newCat(nextCategogyId, name);
    ExpenseCategories.push_back(newCat);
    nextCategogyId++;
    
    cout << ">> New Expense Category '" << name << "' added successfully (ID: " << newCat.getId() << ")." << "\n";
}


void AppMenu::inputNewIncome() {
    cout << "\n--- INPUT NEW INCOME ---" << "\n";
    long long amount;
    int walletId, sourceId;
    string desc;

    cout << "Enter Income Amount (VND): ";
    if (!(cin >> amount) || amount <= 0) {
        cout << "Error: Invalid or non-positive amount." << "\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    cout << "Enter ID of the Wallet to receive funds: ";
    if (!(cin >> walletId)) {
        cout << "Error: Invalid Wallet ID format." << "\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    Wallet* targetWallet = nullptr;
    for(int i = 0; i < Wallets.getSize(); i++){
        if(Wallets[i].getID() == walletId){
            targetWallet = &Wallets[i];
            break;
        }
    }
    if (!targetWallet) {
        cout << "Error: Wallet with ID " << walletId << " not found." << "\n";
        return;
    }
    
    cout << "Enter ID of the Income Source: ";
    if (!(cin >> sourceId)) {
        cout << "Error: Invalid Income Source ID format." << "\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    IncomeSource* targetSource = nullptr;
    for(int i = 0; i < IncomeSources.getSize(); i++){
        if(IncomeSources[i].getID() == sourceId){
            targetSource = &IncomeSources[i];
            break;
        }
    }
    if (!targetSource) {
        cout << "Error: Income Source with ID " << sourceId << " not found." << "\n";
        return;
    }

    cout << "Enter Transaction Description (e.g., Monthly Salary): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, desc);

    Income newInc(Date::get_date(), amount, walletId, sourceId, desc); 
    
    targetWallet->adjustBalance(amount);
    incomes.push_back(newInc); 
    
    cout << ">> Income transaction recorded successfully." << "\n";
}

void AppMenu::inputNewIncomeSource() {
    cout << "\n--- ADD NEW INCOME SOURCE ---" << "\n";
    string name;
    
    cout << "Enter Income Source Name (e.g., Salary, Gift, Investment): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, name);
    
    if (name.empty()) {
        cout << "Error: Source name cannot be empty." << "\n";
        return;
    }
    
    IncomeSource newSource(nextSourceId, name);
    IncomeSources.push_back(newSource);
    nextSourceID++;
    cout << ">> New Income Source '" << name << "' added successfully (Pending final integration of IncomeSource class)." << "\n";
}

void AppMenu::displayMainMenu() {
    cout << "\n==================================================" << "\n";
    cout << "          FINANCIAL MANAGEMENT APPLICATION" << "\n";
    cout << "==================================================" << "\n";
    cout << "1. Transactions (Income/Expense)" << "\n";
    cout << "2. Reports & Statistics" << "\n";
    cout << "3. Setup & Configuration (Wallets, Categories)" << "\n";
    cout << "0. Exit & Save Data" << "\n";
    cout << "--------------------------------------------------" << "\n";
}
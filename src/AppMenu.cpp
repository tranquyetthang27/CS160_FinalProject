#include "../include/AppMenu.h"
#include <iomanip>
#include <limits>
using namespace std;

AppMenu::AppMenu(){
    system("cls");
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
                system("cls");
                handleTransactionMenu();
                system("cls");
                break;
            case 2:
                system("cls");
                handleReportMenu();
                system("cls");
                break;
            case 3:
                system("cls");
                handleSetupMenu();
                system("cls");
                break;
            case 0:
                system("cls");
                saveData();
                cout << "Exiting application. Goodbye!" << endl;
                system("pause");
                break;
            default:
                system("cls");
                cout << "Invalid choice. Please try again." << "\n";
                system("pause");
                system("cls");
        }  
    }while(choice);
}


void AppMenu::loadData(){
    if((fileHandler.loadData(Wallets, ExpenseCategories, IncomeSources, Expenses, Incomes, recurring.getRecurringList()))){
        recurring.setNextRecurringId(recurring.getMaxId());
        nextCategogyId = 1;
        nextSourceId = 1;
        nextWalletId = 1;
        for(int i = 0; i < ExpenseCategories.getSize(); i++){
            nextCategogyId = max(nextCategogyId, ExpenseCategories[i].getId()+1);
        }
        for(int i = 0; i < Wallets.getSize(); i++){
            nextWalletId = max(nextWalletId, Wallets[i].getID()+1);
        }
        for(int i = 0; i < IncomeSources.getSize(); i++){
            nextSourceId = max(nextSourceId, IncomeSources[i].getID()+1);
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
                system("cls");
                recurring.displayRecurringList();
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                handleNetBalanceReport();
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                stats.reportByWallet(Wallets, Expenses); 
                system("pause");
                system("cls");
                break;
            case 4:
                system("cls");
                handleAnnualReport();
                system("pause");
                system("cls");
                break;
            case 5:
                system("cls");
                stats.groupDataByCategory(ExpenseCategories, Expenses);
                system("pause");
                system("cls");
                break;
            case 0:
                system("cls");
                cout << "Returning to Main Menu." << "\n";
                system("pause");
                system("cls");
                break;
            default:
                system("cls");
                cout << "Invalid choice." << "\n";
                system("pause");
                system("cls");
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

    if(!startDate.isValidDate()){
        cout << "Invalid date format." << "\n";
        return;
    }

    cout << "Enter End Date (DD MM YYYY): ";
    if (!(cin >> endDay >> endMonth >> endYear)) {
        cout << "Invalid date format." << "\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    Date endDate(endDay, endMonth, endYear);
    if(!endDate.isValidDate()){
        cout << "Invalid date format." << "\n";
        return;
    }
    if (startDate >= endDate && !(startDate == endDate) ) {
        cout << "Error: Start date must be before or equal to End date." << "\n";
        return;
    }

    long long balance = stats.calcNetBalance(startDate, endDate, Incomes, Expenses);
    
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
    
    stats.reportAnnualOverview(year, Incomes, Expenses);
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
                system("cls");
                inputNewExpense();
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                inputNewIncome();
                system("pause");
                system("cls");
                break;
            case 0:
                system("cls");
                cout << "Returning to Main Menu." << "\n";
                system("pause");
                system("cls");
                break;
            default:
                system("cls");
                cout << "Invalid choice." << "\n";
                system("pause");
                system("cls");
        }
    } while (choice != 0);
}

void AppMenu::handleSetupMenu() {
    int choice;
    do {
        cout << "\n--- SETUP & CONFIGURATION MENU ---" << "\n";
        cout << "1. Add New Expense Category" << "\n"; 
        cout << "2. Add New Income Source" << "\n";
        cout << "3. Add New Wallet" << "\n";
        cout << "4. List all Expense Caterories" << "\n";
        cout << "5. List all Income Sources" << "\n";
        cout << "6. List all Wallets" << "\n";
        cout << "7. Edit/Delete Expense Category" << "\n";
        cout << "8. Edit/Delete Income Source" << "\n";
        cout << "9. Edit/Delete Wallet" << "\n";
        cout << "0. Back to Main Menu" << "\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }
        switch (choice) {
            case 1:
                system("cls");
                inputNewCategory(); 
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                inputNewSource();
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                inputNewWallet();
                system("pause");
                system("cls");
                break;
            case 4:
                system("cls");
                listAllCategories();
                system("pause");
                system("cls");
                break;
            case 5:
                system("cls");
                listAllIncomeSources();
                system("pause");
                system("cls");
                break;
            case 6:
                system("cls");
                listAllWallets();
                system("pause");
                system("cls");
                break;
            case 7:
                system("cls");
                editCategory();
                system("pause");
                system("cls");
                break;
            case 8:
                system("cls");
                editSource();
                system("pause");
                system("cls");
                break;
            case 9:
                system("cls");
                editWallet();
                system("pause");
                system("cls");
                break;
            case 0:
                system("cls");
                cout << "Returning to Main Menu." << "\n";
                system("pause");
                system("cls");
                break;
            default:
                system("cls");
                cout << "Invalid choice." << "\n";
                system("pause");
                system("cls");
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
    Wallet* targetWallet = AppMenu::findWalletById(walletId);
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
    Wallet* targetWallet = findWalletById(walletId);
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
    Incomes.push_back(newInc); 
    
    cout << ">> Income transaction recorded successfully." << "\n";
}

void AppMenu::inputNewSource() {
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
    nextSourceId++;
    cout << ">> New Income Source '" << name << "' added successfully  (ID: " << newSource.getID() << ")." << "\n";
}

void AppMenu::displayMainMenu() {
    cout << "\n==================================================" << "\n";
    cout << "          FINANCIAL MANAGEMENT APPLICATION" << "\n";
    cout << "==================================================" << "\n";
    cout << "1. Transactions (Income/Expense)" << "\n";
    cout << "2. Reports & Statistics" << "\n";
    cout << "3. Setup & Configuration (Wallets, Categories, IncomeSources)" << "\n";
    cout << "0. Exit & Save Data" << "\n";
    cout << "--------------------------------------------------" << "\n";
}

Wallet* AppMenu::findWalletById(const int id){
    for(int i = 0; i < Wallets.getSize(); i++){
        if(Wallets[i].getID() == id)return &Wallets[i];
    }
    return nullptr;
}

ExpenseCategory* AppMenu::findCategoryById(const int id){
    for(int i = 0; i < ExpenseCategories.getSize(); i++){
        if(ExpenseCategories[i].getId() == id)return &ExpenseCategories[i];
    }
    return nullptr;
}

void AppMenu::inputNewWallet(){
    cout << "--- ADD NEW WALLET ---" << endl;

    string name;
    long long initialBalance;

    cout << "Enter Wallet Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, name); 
    cout << "Enter Initial Balance: ";
    while (!(cin >> initialBalance)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    Wallet newWallet(nextWalletId, name, initialBalance);
    Wallets.push_back(newWallet);
    nextWalletId ++;
    cout << ">> New Wallet '" << name << "' added successfully  (ID: " << newWallet.getID() << ")." << "\n";
}

void AppMenu::listAllWallets() {
    cout << "--- LIST OF ALL WALLETS ---" << endl;
    
    if (Wallets.getSize() == 0) {
        cout << "No wallets found. Please add a wallet first!" << endl;
        return;
    }

    cout << left << setw(5) << "ID" 
         << setw(20) << "Wallet Name" 
         << setw(15) << "Balance" << endl;
    cout << string(40, '-') << endl;

    for (int i = 0; i < Wallets.getSize(); ++i) {
        Wallets[i].display();
    }
    
    cout << "\nTotal wallets: " << Wallets.getSize() << "\n";
}

void AppMenu::listAllCategories() {
    cout << "--- LIST OF EXPENSE CATEGORIES ---" << endl;

    if (ExpenseCategories.getSize() == 0) {
        cout << "No categories found. Please add one in Setup Menu!" << endl;
        return;
    }

    cout << left << setw(10) << "ID" 
         << setw(30) << "Category Name" << endl;
    cout << string(40, '-') << endl;

    for (int i = 0; i < ExpenseCategories.getSize(); ++i) {
        ExpenseCategories[i].display();
    }

    cout << "\nTotal categories: " << ExpenseCategories.getSize() << endl;
}

void AppMenu::listAllIncomeSources() {
    cout << "--- LIST OF INCOME SOURCES ---" << "\n";

    if (IncomeSources.getSize() == 0) {
        cout << "No income sources found. Please add a new one!" << "\n";
        return;
    }

    cout << left << setw(10) << "ID" 
         << setw(30) << "Source Name" << "\n";
    cout << string(40, '-') << "\n";

    for (int i = 0; i < IncomeSources.getSize(); ++i) {
        IncomeSources[i].display();
    }

    cout << "\nTotal income sources: " << IncomeSources.getSize() << "\n";
}
void AppMenu::editCategory() {
    cout << "--- EDIT OR DELETE EXPENSE CATEGORY ---" << "\n";

    if (ExpenseCategories.getSize() == 0) {
        cout << "No categories available to edit!" << "\n";
        return;
    }

    int id;
    cout << "\nEnter Category ID to edit/delete: ";
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid ID format!" << "\n";
        return;
    }
    cin.ignore(1000, '\n');
    int foundIndex = -1;
    for (int i = 0; i < ExpenseCategories.getSize(); ++i) {
        if (ExpenseCategories[i].getId() == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "Category ID " << id << " not found!" << "\n";
        return;
    }

    cout << "\nCategory found: " << ExpenseCategories[foundIndex].getName() << "\n";
    cout << "1. Edit Name" << "\n";
    cout << "2. Delete Category" << "\n";
    cout << "0. Cancel" << "\n";
    cout << "Your choice: ";

    int subChoice;
    cin >> subChoice;
    cin.ignore(1000, '\n');

    if (subChoice == 1) {
        string newName;
        cout << "Enter new name: ";
        getline(cin >> ws, newName);
        ExpenseCategories[foundIndex].setName(newName);
        cout << "Category updated successfully!" << "\n";
    } 
    else if (subChoice == 2) {
        ExpenseCategories.removeAt(foundIndex); 
        cout << "Category deleted successfully!" << "\n";
    }
    else {
        cout << "Operation cancelled." << "\n";
    }
}

void AppMenu::editSource() {
    cout << "--- EDIT OR DELETE INCOME SOURCE ---" << "\n";

    if (IncomeSources.getSize() == 0) {
        cout << "No income sources available to edit!" << "\n";
        return;
    }
    int id;
    cout << "\nEnter Income Source ID to edit/delete: ";
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid ID format!" << "\n";
        return;
    }
    cin.ignore(1000, '\n');
    int foundIndex = -1;
    for (int i = 0; i < IncomeSources.getSize(); ++i) {
        if (IncomeSources[i].getID() == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "Income Source ID " << id << " not found!" << "\n";
        return;
    }

    cout << "\nSource found: " << IncomeSources[foundIndex].getName() << "\n";
    cout << "1. Edit Name" << "\n";
    cout << "2. Delete Source" << "\n";
    cout << "0. Cancel" << "\n";
    cout << "Your choice: ";

    int subChoice;
    if (!(cin >> subChoice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        subChoice = 0;
    }
    cin.ignore(1000, '\n');

    if (subChoice == 1) {
        string newName;
        cout << "Enter new name for this source: ";
        getline(cin >> ws, newName);
        IncomeSources[foundIndex].setName(newName);
        cout << "Income source updated successfully!" << "\n";
    } 
    else if (subChoice == 2) {
        IncomeSources.removeAt(foundIndex); 
        cout << "Income source deleted successfully!" <<"\n";
    }
    else {
        cout << "Operation cancelled." << "\n";
    }
}

void AppMenu::editWallet() {
    cout << "--- EDIT OR DELETE WALLET ---" << "\n";

    if (Wallets.getSize() == 0) {
        cout << "No wallets available to edit!" << "\n";
        return;
    }

    int id;
    cout << "\nEnter Wallet ID to edit/delete: ";
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid ID format!" << "\n";
        return;
    }
    cin.ignore(1000, '\n');

    int foundIndex = -1;
    for (int i = 0; i < Wallets.getSize(); ++i) {
        if (Wallets[i].getID() == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "Wallet ID " << id << " not found!" << "\n";
        return;
    }

    cout << "\nWallet found: " << Wallets[foundIndex].getName() 
         << " (Balance: " << Wallets[foundIndex].getBalance() << ")" << "\n";
    cout << "1. Edit Name" << "\n";
    cout << "2. Delete Wallet" << "\n";
    cout << "0. Cancel" << "\n";
    cout << "Your choice: ";

    int subChoice;
    if (!(cin >> subChoice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        subChoice = 0;
    }
    cin.ignore(1000, '\n');

    if (subChoice == 1) {
        string newName;
        cout << "Enter new name for this wallet: ";
        getline(cin >> ws, newName);
        Wallets[foundIndex].setName(newName);
        cout << "Wallet name updated successfully!" << "\n";
    } 
    else if (subChoice == 2) {
        if (Wallets[foundIndex].getBalance() != 0) {
            cout << "Warning: This wallet still has a balance. Proceed with deletion? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm != 'y' && confirm != 'Y') {
                cout << "Deletion cancelled." << "\n";
                return;
            }
        }
        
        Wallets.removeAt(foundIndex); 
        cout << "Wallet deleted successfully!" << "\n";
    }
    else {
        cout << "Operation cancelled." << "\n";
    }
}
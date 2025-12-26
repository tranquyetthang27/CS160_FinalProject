# Personal Finance Manager

## 1. Project Overview
A C++ application designed to help users manage their personal finances, including wallets, expenses, and income sources.

## 2. Main Features
* **Wallet Management:** Add, edit, delete, and list wallets.
* **Expense & Income Tracking:** Categorize your transactions.
* **Data Persistence:** All data is saved in binary files.

## 3. How to Build and Run
To avoid 'nmake' errors, follow these steps in your terminal:
1. Create a build directory: `mkdir build`
2. Enter the directory: `cd build`
3. Configure with MinGW: `cmake -G "MinGW Makefiles" ..`
4. Build the project: `mingw32-make`
5. Go to Bin: `cd bin`
6. Run the app: `./PersonalFinanceManager.exe`

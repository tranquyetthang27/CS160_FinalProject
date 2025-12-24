#ifndef WALLET_H
#define WALLET_H

#include<string>
#include<iostream>
#include<fstream>
#include<iomanip>
//#pragma once

using namespace std;

class Wallet
{
private:
    int m_id;
    string m_name;
    long long m_balance;

public:
    Wallet(const int &id, const string &name, const long long &init = 0);
    Wallet() = default;
    //Get information
    int getID() const;
    string getName() const;
    long long getBalance() const;

    //Set Name
    void setName(const string &newName);

    //Amount can be + or -
    void adjustBalance(const long long &amount);

    void printDetails() const;

    void write2Binary(ofstream& out)const;
    void readFromBinary(ifstream& in);
    void display() const {
    cout << left << setw(5) << m_id 
         << setw(20) << m_name 
         << setw(15) << m_balance << "\n";
    }
};

#endif // WALLET_H

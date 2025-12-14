#ifndef WALLET_H
#define WALLET_H

#include<string>
#include<iostream>
#include<fstream>

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

    void write2Binary(ofstream &out) const;
    void readFromBinary(ifstream &inp);
};

#endif // WALLET_H

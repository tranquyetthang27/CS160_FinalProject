#include "../include/Wallet.h"
#include<iostream>
#include<iomanip>
#include<stdexcept>

using namespace std;

Wallet::Wallet(const int &id, const string &name, const long long &init = 0) : m_id(id), m_name(name), m_balance(init)
{
    if (init < 0) throw std::invalid_argument("The initial balance must be positive!\n");
}

int Wallet::getID() const
{
    return m_id;
}
string Wallet::getName() const
{
    return m_name;
}
long long Wallet::getBalance() const
{
    return m_balance;
}

Wallet::setName(const string &newName)
{
    m_name = newName;
}

void Wallet::adjustBalance(const long long &amount)
{
    m_balance += amount;
}

void Wallet::printDetails() const
{
    cout << "|" << "ID: " << setw(5) << right << m_id << " | ";
    cout << "Name: " << setw(20) << left << m_name << " | ";
    cout << "Balance: " << setw(15) << right << m_balance << " VND |\n";
}

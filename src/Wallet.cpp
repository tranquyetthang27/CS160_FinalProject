#include "../include/Wallet.h"
#include<iomanip>
#include<stdexcept>

using namespace std;

Wallet::Wallet(const int &id, const string &name, const long long &init) : m_id(id), m_name(name), m_balance(init)
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

void Wallet::setName(const string &newName)
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

void Wallet::write2Binary(ofstream& out)const{
    out.write((char*)&m_id, sizeof(m_id));
    size_t sz = m_name.size();
    out.write((char*)&sz, sizeof(sz));
    out.write(m_name.c_str(), sz);
    out.write((char*)&m_balance, sizeof(m_balance));
}

void Wallet::readFromBinary(ifstream& in){
    in.read((char*)&m_id, sizeof(m_id));
    size_t sz;
    in.read((char*)&sz, sizeof(sz));
    m_name.resize(sz);
    in.read(&m_name[0], sz);
    in.read((char*)&m_balance, sizeof(m_balance));

}

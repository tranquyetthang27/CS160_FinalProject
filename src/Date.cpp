#include "../include/Date.h"
#include "ctime"
#include "iostream"
using namespace std;

int dayinmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void Date::write2Binary(ofstream& out)const{
    out.write((char*)&d, sizeof(int));
    out.write((char*)&m, sizeof(int));
    out.write((char*)&y, sizeof(int));
}

void Date::readFromBinary(ifstream& in){
    in.read((char*)&d, sizeof(int));
    in.read((char*)&m, sizeof(int));
    in.read((char*)&y, sizeof(int));
}

string inttoString(int x){
    string res = "";
    while(x){
        res = char(x%10 + '0') + res;
        x/=10;
    }
    return res;
}

Date::Date(int d, int m, int y): d(d), m(m), y(y){};

bool Date::isValidDate(){
    if( d < 1 || m < 1 || y < 1 || m > 12)return false;
    if(y % 100 != 0 && y % 4 == 0 && m == 2){
        if(d > 29)return false;
    }
    else if(dayinmonth[m] < d)return false;
    return true;
}

void Date::addDays(int target){
    d += target;
    if(y % 100 != 0 && y % 4 == 0 && m == 2){
        if(d > 29){
            m = 3;
            d -= 29;
        }
    }
    else if(d > dayinmonth[m]){
        if(m == 12){
            m = 1;
            d -= 31;
            y ++;
        }
        d -= dayinmonth[m];
        m ++;
    }
}

void Date::addMonths(int target){
    m += target;
    while(m > 12){
        y ++;
        m -= 12;
        d = min(d, dayinmonth[m]);
    }
}

void Date::addYears(int target){
    y++;
    if(m == 2 && d == 29)d = 28;
}

bool Date::operator <= (const Date& other)const{
    if(other.y < y)return false;
    if(other.y == y && other.m < m)return false;
    if(other.y == y && other.m == m && other.d < d)return false;
    return true;
}

bool Date::operator >= (const Date& other)const{
    if(other.y > y)return false;
    if(other.y == y && other.m > m)return false;
    if(other.y == y && other.m == m && other.d > d)return false;
    return true;
}

bool Date::operator == (const Date& other)const{
    return (other.y == y && other.m == m && other.d == d);
}

bool Date::isBetween(const Date&start, const Date& end){
    return( *this >= start && *this <= end);
}

Date Date::get_date(){
    time_t now = time(0);
    tm* t = localtime(&now);
    int d = t->tm_mday; 
    int m = t->tm_mon + 1;
    int y = t->tm_year + 1900;
    return Date(d, m, y);
}

string Date::toString()const{
    string res = "";
    if(d < 10)res = "0";
    res = res + inttoString(d) + '/';
    if(m < 10)res = res + '0';
    res = res + inttoString(m) + '/';
    res = res + inttoString(y);
    return res;
}

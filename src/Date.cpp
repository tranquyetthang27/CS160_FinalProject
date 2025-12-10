#include "../include/Date.h"
#include "ctime"
#include "iostream"
using namespace std;


Date::Date(int d, int m, int y): d(d), m(m), y(y){};

bool Date::isValidDate(){
    if( d < 1 || m < 1 || y < 1 || m > 12)return false;
    if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12 ){
        if(d > 31)return false;
    }
    else{
        if(m == 2){
            if(y % 4 == 0)if(d > 29)return false;
            else if(d > 28)return false;
        }
        else if(d > 30)return false;
    }
    return true;
}

bool Date::operator < (const Date& other)const{
    if(other.y < y)return false;
    if(other.y == y && other.m < m)return false;
    if(other.y == y && other.m == m && other.d < d)return false;
    return true;
}

bool Date::operator > (const Date& other)const{
    if(other.y > y)return false;
    if(other.y == y && other.m > m)return false;
    if(other.y == y && other.m == m && other.d > d)return false;
    return true;
}

bool Date::operator == (const Date& other)const{
    return (other.y == y && other.m == m && other.d == d);
}

Date Date::get_date(){
    time_t now = time(0);
    tm* t = localtime(&now);
    int d = t->tm_mday; 
    int m = t->tm_mon + 1;
    int y = t->tm_year + 1900;
    return Date(d, m, y);
}

void Date::toString()const{
    if(d < 10)cout << 0;
    cout << d <<'/';
    if(m < 10)cout << 0;
    cout << m << '/' << y;
}

# ifndef DATE_H
# define DATE_H

using namespace std;

class Date{
    private:
        int d, m, y;
    public:
        Date(int d, int m, int y);
        Date() = default;
        static Date get_date();
        void changeDate(const Date& other){d = other.d, m = other.m, y = other.y;}
        int get_day(){return d;};
        int get_month(){return m;};
        int get_year(){return y;};
        void addDays(int target);
        void addMonths(int target);
        void addYears(int target);
        bool isValidDate();
        bool operator <= (const Date& other)const;
        bool operator >= (const Date& other)const;
        bool operator == (const Date& other)const;
        bool isBetween(const Date& start, const Date& end);
        string toString()const;
};

#endif
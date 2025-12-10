# ifndef DATE_H
# define DATE_H

using namespace std;

class Date{
    private:
        int d, m, y;
    public:
        Date(int d, int m, int y);
        static Date get_date();
        int get_day(){return d;};
        int get_month(){return m;};
        int get_year(){return y;};
        bool isValidDate();
        bool operator <= (const Date& other)const;
        bool operator >= (const Date& other)const;
        bool operator == (const Date& other)const;
        bool isBetween(const Date& start, const Date& end);
        void toString()const;
};

#endif
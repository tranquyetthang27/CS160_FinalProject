# ifndef DATE_H
# define DATE_H

using namespace std;

class Date{
    private:
        int d, m, y;
    public:
        Date(int d, int m, int y);
        static Date get_date();
        bool isValidDate();
        bool operator < (const Date& other)const;
        bool operator > (const Date& other)const;
        bool operator == (const Date& other)const;
        void toString();
};

#endif
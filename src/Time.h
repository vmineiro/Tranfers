/*
 * Time.h
 */

#ifndef TIME_h
#define TIME_h

#include <iostream>
#include <iomanip>

using namespace std;

class Time
{
private:
    int hour; // 0 - 23 (24-hour clock format)
    int minute; // 0 - 59

public:
    Time();
    Time(int hour, int minute);
    
    void setTime(int hour, int minute);
    void setHour(int hour);
    void setMinute(int minute);
    
    int getHour() const;
    int getMinute() const;
    
    void get();
    void show();
    

    bool operator == (const Time &other) const;
    bool operator < (const Time &other) const;
    bool operator > (const Time &other) const;
    const Time operator + (const Time &other);
    const Time operator - (const Time &other);
    
    friend ostream & operator << (ostream &os, const Time &s);
    
    
    class HourException
    {
        int hour;
        
    public:
        HourException(int h){hour = h;}
        void getMsg()
        {
            cout << "Hora Invalida: " << hour << endl;
        }
        
    };
    
    
    class MinuteException
    {
        int minute;
        
    public:
        MinuteException(int m){minute = m;}
        void getMsg()
        {
            cout << "Minuto Invalido: " << minute << endl;
        }
    };
    
};



#endif

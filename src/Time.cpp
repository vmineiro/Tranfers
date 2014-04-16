/*
 * Time.cpp
 */

#include "Time.h"

// ==========================================================

Time::Time()
{
    setTime(0, 0, 0);
}

// ==========================================================

Time::Time(int hour, int minute, int second)
{
    setTime(hour,minute,second);
}

// ==========================================================

void Time::setTime( int hour, int minute, int second )
{
    try
    {
        setHour(hour);
        setMinute(minute);
        setSecond(second);
    }
    catch(Time::HourException &h)
    {
        h.getMsg();
    }
    catch(Time::MinuteException &m)
    {
        m.getMsg();
    }
    catch(Time::SecondException &s)
    {
        s.getMsg();
    }
    
}

// ==========================================================

void Time::get()
{
    int hour, minute, second;
    cout << "Enter hour : " ;
    cin >> hour;
    cout << endl ;
    cout << "Enter minute : " ;
    cin >> minute;
    cout << endl ;
    cout << "Enter second : " ;
    cin >> second;
    cout << endl ;
    setTime(hour,minute, second);
}

// ==========================================================

void Time::setHour( int h )
{
    if(h < 0 || h > 23)
    {
        throw HourException(h);
    }
    
    hour = h;
}

// ==========================================================

void Time::setMinute( int m )
{
    if(m < 0 || m > 59)
    {
        throw MinuteException(m);
    }
    
    minute = m;
}

// ==========================================================

void Time::setSecond( int s )
{
    if(s < 0 || s > 59)
    {
        throw SecondException(s);
    }
    second = s;
}

// ==========================================================

int Time::getHour ( ) const
{
    return hour;
}

// ==========================================================

int Time::getMinute () const
{
    return minute;
}

// ==========================================================

int Time::getSecond () const
{
    return second;
}

// ==========================================================

void Time::show()
{
    cout << setfill('0') << setw(2) << hour << ":" << setw(2)
    << minute << ":" << setw(2) << second;
}

// ==========================================================

const Time Time::operator+(const Time &other) {
    int hour = (*this).getHour() + other.getHour();
    int min = (*this).getMinute() + other.getMinute();
    int sec = (*this).getSecond() + other.getSecond();
    if ( sec > 60 )
    {
        sec = sec - 60;
        min = min + 1;
    }
    if ( min > 60 )
    {
        min = min - 60;
        hour = hour + 1;
    }
    if ( hour > 24 )
    {
        hour = hour - 24;
    }
 
    return Time(hour,min,sec);
}

// ==========================================================

const Time Time::operator-(const Time &other) {
    int hour = (*this).getHour() - other.getHour();
    int min = (*this).getMinute() - other.getMinute();
    int sec = (*this).getSecond() - other.getSecond();
    if ( sec < 0 )
    {
        sec = sec + 60;
        min = min - 1;
    }
    if ( min < 0 )
    {
        min = min + 60;
        hour = hour - 1;
    }
    if ( hour < 0 )
    {
        hour = hour + 24;
    }

    return Time(hour,min,sec);
}

// ==========================================================

bool Time::operator==(const Time &other) const
{
    return ((hour == other.hour) && (minute == other.minute) && (second == other.second));
}

// ==========================================================

ostream & operator << (ostream &os, const Time &s)
{
    os << setfill('0') << setw(2) << s.getHour() << ":" << setw(2) << s.getMinute() << ":" << setw(2) << s.getSecond();
    return os;
}












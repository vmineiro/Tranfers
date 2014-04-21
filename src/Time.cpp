/*
 * Time.cpp
 */

#include "Time.h"

// ==========================================================

Time::Time()
{
	setTime(0, 0);
}

// ==========================================================

Time::Time(int hour, int minute)
{
	setTime(hour,minute);
}

// ==========================================================

void Time::setTime( int hour, int minute)
{
	try
	{
		setHour(hour);
		setMinute(minute);
	}
	catch(Time::HourException &h)
	{
		h.getMsg();
	}
	catch(Time::MinuteException &m)
	{
		m.getMsg();
	}

}

// ==========================================================

void Time::get()
{
	int hour, minute;
	cout << "Enter hour : " ;
	cin >> hour;
	cout << endl ;
	cout << "Enter minute : " ;
	cin >> minute;
	cout << endl ;
	setTime(hour,minute);
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

void Time::show()
{
	cout << setfill('0') << setw(2) << hour << ":" << setw(2)
    		<< minute;
}

// ==========================================================

const Time Time::operator+(const Time &other) {
	int hour = (*this).getHour() + other.getHour();
	int min = (*this).getMinute() + other.getMinute();

	if ( min > 60 )
	{
		min = min - 60;
		hour = hour + 1;
	}
	if ( hour > 24 )
	{
		hour = hour - 24;
	}

	return Time(hour,min);
}

// ==========================================================

const Time Time::operator-(const Time &other) {
	int hour = (*this).getHour() - other.getHour();
	int min = (*this).getMinute() - other.getMinute();

	if ( min < 0 )
	{
		min = min + 60;
		hour = hour - 1;
	}
	if ( hour < 0 )
	{
		hour = hour + 24;
	}

	return Time(hour,min);
}

// ==========================================================

bool Time::operator==(const Time &other) const
		{
	return ((hour == other.hour) && (minute == other.minute));
		}

// ==========================================================

bool Time::operator<(const Time &other) const
{
	if (hour > other.hour) return false;
	else if (hour < other.hour) return true;
	else {
		if (minute < other.minute) return true;
		else return false;
	}
}

// ==========================================================

bool Time::operator>(const Time &other) const
{
	if (hour < other.hour) return false;
	else if (hour > other.hour) return true;
	else {
		if (minute > other.minute) return true;
		else return false;
	}
}

// ==========================================================

ostream & operator << (ostream &os, const Time &s)
{
	os << setfill('0') << setw(2) << s.getHour() << ":" << setw(2) << s.getMinute();
	return os;
}












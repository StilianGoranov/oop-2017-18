#ifndef TIME_H_
#define TIME_H_

#include <iostream>
#include <iomanip>

class Time {
private:
	int hours;
	int minutes;

public:
	Time(int _hours = 0, int _minutes = 0) {
		setHours(_hours);
		setMinutes(_minutes);
	}

	void setHours(int _hours) {
		while (_hours < 0)
			_hours += 24;
		hours = _hours % 24;
	}

	void setMinutes(int _minutes) {
		while (_minutes < 0)
		{
			_minutes += 60;
			hours -= 1;
		}

		hours += _minutes / 60;
		minutes = _minutes % 60;
		hours %= 24;
	}

	int getHours() const {
		return hours;
	}
	int getMinutes() const {
		return minutes;
	}

	void reset() {
		hours = 0;
		minutes = 0;
	}

	void print(std::ostream& os = std::cout) const {
		os << "<" << std::setw(2) << std::setfill('0') << hours << ":"
			<< std::setw(2) << std::setfill('0') << minutes << ">";
	}

	Time& operator+=(int _minutes) {
		setMinutes(minutes + _minutes);
		return *this;
	}

	Time& operator+=(Time const& _time)
	{
		*this += _time.getMinutes();
		setHours(hours + _time.hours);
		return *this;
	}

	Time& operator++()
	{
		return *this += 1;
	}

	Time operator++(int)
	{
		Time old = *this;
		++*this;
		return old;
	}
};

Time operator+(Time const& t1, Time const& t2)
{
	Time newTime;
	newTime.setHours(t1.getHours() + t2.getHours());
	newTime += t1.getMinutes() + t2.getMinutes();

	return newTime;
}

int operator-(Time const& t1, Time const& t2)
{
	int hoursToMinsDiff = (t1.getHours() - t2.getHours()) * 60;
	int minsDiff = t1.getMinutes() - t2.getMinutes();

	return abs(hoursToMinsDiff + minsDiff);
}

Time operator+(Time const& time, int _minutes)
{
	return Time(time) += _minutes;
}

Time operator+(int _minutes, Time const& time)
{
	return time + _minutes;
}

std::ostream& operator<<(std::ostream& os, Time const& time) {
	time.print(os);
	return os;
}

std::istream& operator>>(std::istream& is, Time& time)
{
	int h;
	std::cout << "Enter hours: ";
	is >> h;
	time.setHours(h);

	int m;
	std::cout << "Enter minutes: ";
	is >> m;
	time.setMinutes(m);

	return is;
}

bool operator==(Time const& t1, Time const& t2) {
	return t1.getHours() == t2.getHours() && t1.getMinutes() == t2.getMinutes();
}

bool operator!=(Time const& t1, Time const& t2)
{
	return !(t1 == t2);
}

bool operator<(Time const& t1, Time const& t2)
{
	if (t1.getHours() < t2.getHours())
		return true;
	if (t1.getHours() == t2.getHours())
		return t1.getMinutes() < t2.getMinutes();

	// t1.hours > t2.hours
	return false;
}

bool operator<=(Time const& t1, Time const& t2)
{
	return t1 < t2 || t1 == t2;
}

bool operator>(Time const& t1, Time const& t2)
{
	return !(t1 <= t2);
}

bool operator>=(Time const& t1, Time const& t2)
{
	return !(t1 < t2);
}

#endif /* TIME_H_ */

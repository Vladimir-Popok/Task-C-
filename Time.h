#pragma once
#include<fstream>
#include <stdexcept>
#include <string>
#include <iostream>

class Time {
	unsigned int m_minutes = 0;
	unsigned int m_hours = 0;

public:
	Time(){}
	Time(int hours, int minutes);
	Time(const Time& other);

	Time& operator=(const Time& other);

	static int Compare(const Time& t1, const Time& t2);

	friend Time operator- (const Time& t1, const Time& t2);

	friend Time operator+ (const Time& t1, const Time& t2);

	friend bool operator< (const Time& t1, const Time& t2);

	friend bool operator> (const Time& t1, const Time& t2);

	friend bool operator== (const Time& t1, const Time& t2);

	friend std::ostream& operator<<(std::ostream& s, const Time& time);

	int static round_up(const Time& t);

	unsigned int getMinutes() {
		return m_minutes;
	}

	unsigned int getHours() {
		return m_hours;
	}
};

Time usage_time(const Time& start, const Time& end);
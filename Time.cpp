#include "Time.h"

Time::Time(int hours, int minutes) {
	if (minutes > 59 || hours > 23) {
		std::invalid_argument("Invalid time format in event");
	}
	m_minutes = minutes;
	m_hours = hours;
}

Time::Time(const Time& other) : m_hours(other.m_hours), m_minutes(other.m_minutes) {
}

Time& Time::operator=(const Time& other) {
	if (this != &other) {
		m_hours = other.m_hours;
		m_minutes = other.m_minutes;
	}
	return *this;
}

int Time::Compare(const Time& t1, const Time& t2) {
	if (t1.m_hours == t2.m_hours) {

		if (t1.m_minutes == t2.m_minutes) {
			return 0;
		}

		return t1.m_minutes < t2.m_minutes ? -1 : 1;
	}
	return t1.m_hours < t2.m_hours ? -1 : 1;
}

Time operator- (const Time& t1, const Time& t2) {
	unsigned int hours, minutes;
	if (t1 < t2) {
		hours = 24 + t1.m_hours - t2.m_hours;
	}
	else {
		hours = t1.m_hours - t2.m_hours;
	}
	
	if (t1.m_minutes < t2.m_minutes) {
		--hours;
		minutes = 60 + t1.m_minutes - t2.m_minutes;
	}
	else {
		minutes = t1.m_minutes - t2.m_minutes;
	}
	return Time(hours, minutes);
}

Time operator+ (const Time& t1, const Time& t2) {
	unsigned int hours, minutes;
	hours = t1.m_hours + t2.m_hours;
	
	if (t1.m_minutes + t2.m_minutes > 60) {
		++hours;
		minutes = t1.m_minutes + t2.m_minutes - 60;
	}
	else {
		minutes = t1.m_minutes + t2.m_minutes - 60;
	}

	return Time(hours, minutes);
}

bool operator< (const Time& t1, const Time& t2) {
	return Time::Compare(t1, t2) == -1;
}

bool operator> (const Time& t1, const Time& t2) {
	return Time::Compare(t1, t2) == 1;
}

bool operator== (const Time& t1, const Time& t2) {
	return Time::Compare(t1, t2) == 0;
}

std::ostream& operator<<(std::ostream& s, const Time& time) {
	time.m_hours < 10 ? s << "0" + std::to_string(time.m_hours) : s << std::to_string(time.m_hours);
	s << ":";
	time.m_minutes < 10 ? s << "0" + std::to_string(time.m_minutes) : s << std::to_string(time.m_minutes);
	return s;
}

int Time::round_up(const Time& t) {
	return t.m_hours == 0 ? t.m_hours : (t.m_hours + 1);
}

Time usage_time(const Time& start, const Time& end) {
	return end - start;
}
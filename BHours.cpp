#include "BHours.h"

BHours::BHours(Time start, Time end) {
	m_start = start;
	m_end = end;
	if (start > end) nt = true;
}

BHours::BHours(const BHours& other) : m_start(other.m_start), m_end(other.m_end), nt(other.nt) {
}

BHours& BHours::operator=(const BHours& other) {
	if (this != &other) {
		m_start = other.m_start;
		m_end = other.m_end;
		nt = other.nt;
	}
	return *this;
}

bool BHours::valid_time(Time time) {
	if (nt) {
		return time < m_end || time > m_start || time == m_start;
	}
	return time < m_end && (time > m_start || time == m_start);
}

Time BHours::usage_time(const Time& start, const Time& end) {
	return end - start;
}
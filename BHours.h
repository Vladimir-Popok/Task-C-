#pragma once
#include "Time.h"

class BHours {
	Time m_start;
	Time m_end;
	bool nt = false;

public:
	BHours(){}

	BHours(Time start, Time end);

	BHours(const BHours& other);

	BHours& operator=(const BHours& other);
	
	bool valid_time(Time time);
	bool is_nt() { return nt; }

	Time usage_time(const Time& start, const Time& end);

	Time getStart() { return m_start; }
	Time getEnd() { return m_end; }
};

#pragma once
#include "BHours.h"
#include "Visitors.h"
#include "Queue.h"
#include "Data.h"
#include <vector>
#include <map>


enum Code {
	CAME = 1,
	SIT = 2,
	WAITING = 3,
	EXIT = 4,
	CLOSED = 11,
	UNDER_FLOW = 12,
	ERROR = 13,
};

class Managment {
	unsigned int m_table_count;
	unsigned int m_hourly_pay;
	BHours m_bh;
	std::vector<bool> m_tables;
	Visitors m_visitors;
	Queue m_queue;
	Data m_data;
	Time* last_event;

public:

	Managment(unsigned int m_table_count, unsigned int m_cost, const Time& start, const Time& end);
	void came(const std::string& name, const Time& now, Code code);
	void sit(const std::string& name, const Time& now, int table_number, Code code);
	void waiting(const std::string& name, const Time& now, Code code);
	void exit(const std::string& name, const Time& now, Code code);
	void get_up(const std::string& name, const Time& now);
	void closed();
	void statistics();
};
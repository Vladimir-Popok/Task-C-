#pragma once

#include "Time.h"
#include <vector>

struct TimeAndProfit {
	Time time;
	int pay_hour;
};

class Data {

	struct DataBlock {
		Time start;
		Time end;

		Time static get_usage_time(DataBlock db) {
			return usage_time(db.start, db.end);
		}

		int static get_round_time(DataBlock db) {
			return Time::round_up(usage_time(db.start, db.end));
		}
	};

	std::vector<std::vector<DataBlock>> data;

public:
	Data(){}
	Data(unsigned int table_count);
	void sit(unsigned int table_number, Time now);
	void get_up(unsigned int table_number, Time now);
	std::vector<TimeAndProfit> info();
};
#include "Data.h"



Data::Data(unsigned int table_count) : data(table_count){
}

void Data::sit(unsigned int table_number, Time now) {
	DataBlock db;
	db.start = now;
	data[table_number].push_back(db);
}


void Data::get_up(unsigned int table_number, Time now) {
	data[table_number].back().end = now;
}

std::vector<TimeAndProfit> Data::info() {
	int count = 0;
	std::vector<TimeAndProfit> out(data.size());
	for (const auto& table : data) {
		int pay_hour = 0;
		Time occupied_time = Time(0, 0);

		for (const auto& db : table) {
			occupied_time = occupied_time + DataBlock::get_usage_time(db);
			pay_hour += DataBlock::get_round_time(db);
		}

		TimeAndProfit tp;
		tp.time = occupied_time;
		tp.pay_hour = pay_hour;

		out[count] = tp;
		++count;
	}
	return out;
}
#include "Managment.h"


Managment::Managment(unsigned int table_count, unsigned int hourly_pay, const Time& start, const Time& end) {
	m_table_count = table_count;
	m_hourly_pay = hourly_pay;
	m_bh = BHours(start, end);
	std::vector<bool>m_tables(m_table_count);
	m_queue = Queue(m_table_count);
	m_visitors = Visitors();
	m_data = Data(m_table_count);
	last_event = nullptr;
}

void Managment::came(const std::string& name, const Time& now, Code code) {
	
	if (last_event != nullptr) {
		if (!(BHours(now, m_bh.getEnd()).valid_time(*last_event))) {
			throw std::invalid_argument("Wrong event time!");
		}
	}
	
	if (now > m_bh.getEnd() || now == m_bh.getStart()) {
		closed();
	}
	std::cout << now << " " << code << " " << name << '\n';
	
	if (!m_bh.valid_time(now)) {
		std::cout << now << " " << ERROR << " " << "NotOpenYet\n";
		return;
	}
	
	m_visitors.insert(name, S_CAME);
	std::cout << m_visitors.get(name) << "\n";
	*last_event = now;
}

void Managment::sit(const std::string& name, const Time& now, int table_number, Code code) {

	if (last_event != nullptr) {
		if (!(BHours(now, m_bh.getEnd()).valid_time(*last_event))) {
			throw std::invalid_argument("Wrong event time!");
		}
	}

	if (now > m_bh.getEnd() || now == m_bh.getStart()) {
		closed();
	}
	std::cout << now << " " << code << " " << name << '\n';
	int status = m_visitors.get(name);
	if (status == NOT_FOUND) {
		std::cout << now << " " << ERROR << " " << "ClientUnknown\n";
		return;
	}
	
	if (m_tables[table_number - 1] == true) {
		std::cout << now << " " << ERROR << " " << "PlaceIsBusy\n";
		return;
	}

	if (status > 0) {
		get_up(name, now);
	}
	m_data.sit(table_number, now);
	m_visitors.insert(name, table_number);
	*last_event = now;
}

void Managment::waiting(const std::string& name, const Time& now, Code code) {
	if (last_event != nullptr) {
		if (!(BHours(now, m_bh.getEnd()).valid_time(*last_event))) {
			throw std::invalid_argument("Wrong event time!");
		}
	}
	if (now > m_bh.getEnd() || now == m_bh.getStart()) {
		closed();
	}
	std::cout << now << " " << code << " " << name << '\n';
	int status = m_visitors.get(name);
	if (status == NOT_FOUND) {
		std::cout << now << " " << ERROR << " " << "ClientUnknown\n";
		return;
	}
	
	if (!m_queue.insert(name)) {
		exit(name, now, CLOSED);
	}

	for (bool flag : m_tables) {
		if (flag == false) {
			std::cout << now << " " << ERROR << " " << "ICanWaitNoLonger!\n";
			return;
		}
	}

	if (status > 0) {
		get_up(name, now);
	}
	m_visitors.insert(name, S_QUEUE);
	*last_event = now;
}

void Managment::exit(const std::string& name, const Time& now, Code code) {
	if (last_event != nullptr) {
		if (!(BHours(now, m_bh.getEnd()).valid_time(*last_event))) {
			throw std::invalid_argument("Wrong event time!");
		}
	}
	if (now > m_bh.getEnd() || now == m_bh.getStart()) {
		closed();
	}
	std::cout << now << " " << code << " " << name << '\n';
	int status = m_visitors.get(name);
	if (status == NOT_FOUND) {
		std::cout << now << " " << ERROR << " " << "ClientUnknown\n";
		return;
	}
	if (status > 0) {
		get_up(name, now);
	}
	m_visitors.remove(name);
	*last_event = now;
}

void Managment::get_up(const std::string& name, const Time& now) {
	int free_table = m_visitors.get(name);
	m_tables[free_table - 1] = false;
	if (!m_queue.is_empty()) {
		sit(name, now, free_table, UNDER_FLOW);
	}
	m_data.get_up(free_table, now);
	m_visitors.insert(name, S_CAME);
}

void Managment::closed() {
	std::unordered_map<std::string, int>& uns_map = m_visitors.getVisitors();
	std::map<std::string, int> sortedMap(uns_map.begin(), uns_map.end());

	Time closed_time = m_bh.getEnd();
	for (const auto& pair : sortedMap) {
		std::cout << closed_time << " " << CLOSED << " " << pair.first << '\n';
	}
	uns_map.clear();
}

void Managment::statistics() {
	std::vector<TimeAndProfit> statistics = m_data.info();
	int count = 1;
	for (auto& stat : statistics) {
		std::cout << count << " " << stat.pay_hour * m_hourly_pay << " " << stat.time << '\n';
	}
}
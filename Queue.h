#pragma once
#include <queue>
#include <string>

class Queue {
	unsigned int max_visitors = 0;
	std::queue<std::string> q;

public:
	Queue(){}
	Queue(unsigned int table_count);

	bool insert(const std::string& visitor);

	bool is_empty();

	std::string get();
};

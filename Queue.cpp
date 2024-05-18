#include "Queue.h"

Queue::Queue(unsigned int table_count) : max_visitors(table_count) {
}

bool Queue::insert(const std::string& visitor) {
    if (q.size() >= max_visitors) {
        return false;
    }
	q.push(visitor);
    return true;
}

bool Queue::is_empty() {
    return q.empty();
}

std::string Queue::get() {
    std::string front = q.front();
    q.pop();
    return front;
}

#include "Visitors.h"

void Visitors::insert(const std::string& key, int value) {
    visitors[key] = value;
}

int Visitors::get(const std::string& key) {
    if (visitors.find(key) != visitors.end()) {
        return visitors[key];
    }
    return NOT_FOUND;
}


void Visitors::remove(const std::string& key) {
    visitors.erase(key);
}

std::unordered_map<std::string, int>& Visitors::getVisitors() {
    return visitors;
}
#pragma once
#include <unordered_map>
#include <string>

enum Status {
    S_EXIT = -1,
    S_QUEUE = -2,
    S_CAME = -3,
    NOT_FOUND = -4,
};

class Visitors {
    std::unordered_map<std::string, int> visitors;
    
public:
    
    void insert(const std::string& key, int value);

    int get(const std::string& key);

    void remove(const std::string& key);

    std::unordered_map<std::string, int>& getVisitors();
};
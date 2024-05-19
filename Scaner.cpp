#include "Managment.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

bool is_valid_client_name(const std::string& name) {
    for (char c : name) {
        if (!isalnum(c) && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

Time parse_time(const std::string& time_str) {
    int hours, minutes;
    char colon;
    std::istringstream time_iss(time_str);
    if (!(time_iss >> hours >> colon >> minutes) || colon != ':' || hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        throw std::invalid_argument("Invalid time format in event");
    }
    return Time(hours, minutes);
}

void check_event_line(const std::string& line, int line_number, Managment& managment) {
    std::istringstream iss(line);
    std::string time_str, client_name;
    int id, table_number;
    if (!(iss >> time_str >> id >> client_name)) {
        throw std::invalid_argument("Invalid event format");
    }

    if (id == SIT) {
        if (!(iss >> table_number)) {
            throw std::invalid_argument("Invalid event format");
        }
    } 

    Time event_time = parse_time(time_str);

    if (id < 1 || id > 4) {
        throw std::invalid_argument("Wrong event ID");
    }

    if (!is_valid_client_name(client_name)) {
        throw std::invalid_argument("Invalid client name");
    }
    switch (id)
    {
    case 1:
        managment.came(client_name, event_time, CAME);
        break;
    case 2:
        managment.sit(client_name, event_time, table_number, SIT);
        break;
    case 3:
        managment.waiting(client_name, event_time, WAITING);
        break;
    case 4:
        managment.exit(client_name, event_time, EXIT);
        break;
    }
}


void check_input_file(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        std::abort();
    }

    std::string line;
    int line_number = 0;

    if (!std::getline(infile, line)) {
        std::cerr << "Missing number of tables" << std::endl;
        return;
    }
    line_number++;
    int table_count;
    try {
        table_count = std::stoi(line);
        if (table_count <= 0) {
            throw std::invalid_argument("Number of tables must be positive");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error in line " << line_number << ": " << e.what() << std::endl;
        return;
    }

    if (!std::getline(infile, line)) {
        std::cerr << "Missing opening and closing times" << std::endl;
        return;
    }
    line_number++;
    std::istringstream iss(line);
    std::string open_time_str, close_time_str;
    if (!(iss >> open_time_str >> close_time_str)) {
        std::cerr << "Error in line " << line_number << ": invalid time format" << std::endl;
        std::abort();
    }

    Time start, end;
    try {
        start = parse_time(open_time_str);
        end = parse_time(close_time_str);
    }
    catch (const std::exception& e) {
        std::cerr << "Error in line " << line_number << ": " << e.what() << std::endl;
        std::abort();
    }

    if (!std::getline(infile, line)) {
        std::cerr << "Missing hourly rate" << std::endl;
        std::abort();
    }
    line_number++;
    int hourly_pay;
    try {
        hourly_pay = std::stod(line);
        if (hourly_pay <= 0) {
            throw std::invalid_argument("Hourly rate must be positive");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error in line " << line_number << ": " << e.what() << std::endl;
        std::abort();
    }
    Managment managment = Managment(table_count, hourly_pay, start, end);
    std::cout << start << '\n';
    while (std::getline(infile, line)) {
        line_number++;
        try {
            check_event_line(line, line_number, managment);
        }
        catch (const std::exception& e) {
            std::cerr << "Error in line " << line_number << ": " << e.what() << std::endl;
            std::abort();
        }
    }
    managment.closed();
    std::cout << end << '\n';
    managment.statistics();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    } 
    std::string filename = argv[1];
    check_input_file(filename);

    return 0;
}

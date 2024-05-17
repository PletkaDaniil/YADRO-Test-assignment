#include "helper_functions.h"

void check_args(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Use " << argv[0] << " source destination" << "\n";
        exit(1);
    }
}

void open_input_file(std::ifstream& input_file, char* argv[]) {
    input_file.open(argv[1]);
    if (!input_file.is_open()) {
        std::cerr << "Can not open file " << argv[1] << "\n";
        exit(1);
    }
}

void ending(std::ifstream& input_file){
    input_file.close();
    exit(0);
}


// Converts a given time in the format “HH:MM” into minutes
int time_to_minutes(const std::string& time){
    int hours = std::stoi(time.substr(0, 2));
    int minutes = std::stoi(time.substr(3, 2));
    return hours * 60 + minutes;
}

// Calculates the earnings for a table
int earnings_per_table(const int& minutes, const int& price){
    // Rounds up the minutes to the nearest hour before multiplying by the price
    return ((minutes + 59) / 60) * price;
}

// Check - if the given string contains only with digits and returns true or false
bool only_digits_check(const std::string& line){
    return line.find_first_not_of("0123456789") == std::string::npos;
}

// Check - if command(event) сontains only with digits and if the value is between 1 and 4 (inclusive)
bool command_check(const std::string& line){
    if (!only_digits_check(line)){
        return false;
    }
    int number_of_command = std::stoi(line);
    return number_of_command >= 1 && number_of_command <= 4;
}

// Check - if the given time is in the format of HH:MM (24-hour format)
bool time_valid_check(const std::string& time){
    if (time.size() != 5 || time[2] != ':') {
        return false;
    }
    int length = time.size();
    for (int index = 0; index < length; ++index) {
        if (index == 2){ continue;}
        if (time[index] < '0' || time[index] > '9') {
            return false;
        }
    }
    int hours = std::stoi(time.substr(0, 2));
    int minutes = std::stoi(time.substr(3, 2));
    return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60;
}

// Check - if the given client name contains only with lowercase letters, digits, underscores or hyphens
bool client_name_valid_check(const std::string& client_name) {
    int length = client_name.size();
    for (int index = 0; index < length; ++index) {
        if (!((client_name[index] >= 'a' && client_name[index] <= 'z') ||
            (client_name[index] >= '0' && client_name[index] <= '9') ||
            client_name[index] == '_' || client_name[index] == '-')) {
            return false;
        }
    }
    return true;
}

// Check - if the given number of the table contains only with digits and if its value is between 1 and "total_number_of_tables" (or N)
bool table_number_range_check(const std::string& table_number, const double& total_number_of_tables) {
    if (!only_digits_check(table_number)) {
        return false;
    }
    int table_number_value = std::stoi(table_number);
    return table_number_value >= 1 && table_number_value <= total_number_of_tables;
}

// Сheck - if the given time (converted to minutes) is within the working hours defined by "start_of_work" and "end_of_work"
bool client_entry_valid_check(const std::string& time, const int& start_of_work, const int& end_of_work){
    int minutes = time_to_minutes(time);
    return minutes >= start_of_work && minutes <= end_of_work;
}

// Each string in data is a substring of "line" separated by spaces 
std::vector<std::string> split_line_by_spaces(const std::string& line){
    std::istringstream stream_line(line);
    std::vector<std::string> data;
    std::string current_part_of_line;

    while (stream_line >> current_part_of_line) {
        data.push_back(current_part_of_line);
    }
    return data;
}

// Сonverts a given total time in minutes into a string format “HH:MM”
std::string convert_minutes_to_hours_minutes(const int& all_minutes) {
    int hours = all_minutes / 60;
    int minutes = all_minutes % 60;

    std::string hours_string = (hours < 10) ? "0" + std::to_string(hours) : std::to_string(hours);
    std::string minutes_string = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);

    std::string timeString = hours_string + ":" + minutes_string;

    return timeString;
}
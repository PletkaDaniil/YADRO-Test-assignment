#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include <sstream>

int time_to_minutes(const std::string& time);
int earnings_per_table(const int& minutes, const int& price);

bool only_digits_check(const std::string& line);
bool command_check(const std::string& line);
bool time_valid_check(const std::string& time);
bool client_name_valid_check(const std::string& client_name);
bool table_number_range_check(const std::string& table_number, const double& total_number_of_tables);
bool client_entry_valid_check(const std::string& time, const int& start_of_work, const int& end_of_work);

std::vector<std::string> split_line_by_spaces(const std::string& line);
std::string convert_minutes_to_hours_minutes(const int& all_minutes);

#endif
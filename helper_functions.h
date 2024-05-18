#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>

void check_args(int argc, char* argv[]);
void open_input_file(std::ifstream &input_file, char *argv[]);
void ending(std::ifstream &input_file);
void remove_client_from_queue(std::queue<std::string>& clients_waiting_for_tables, const std::string& client_left_the_club);

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
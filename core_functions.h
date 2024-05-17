#ifndef CORE_FUNCTIONS_H
#define CORE_FUNCTIONS_H

#include <map>
#include "helper_functions.h"

struct client_info{
    int table_num;
    int command;
    std::string time;
    std::string client_name;
    client_info(int new_table_num = -1, int new_command = -1, const std::string& new_time = "HH:MM", const std::string& new_client_name = "None")
        : table_num(new_table_num), command(new_command), time(new_time), client_name(new_client_name) {}
};

client_info create_client_information(int number_of_command, const std::vector<std::string>& data, const std::string& current_file_line, int total_number_of_tables, std::map<int, bool>& table_availability);
void ensure_data_correctness(const std::string& current_file_line, int& check_stage, int& total_number_of_tables, int& start_of_work, int& end_of_work, int& table_price, int& previous_time, std::map<int, bool>& table_availability, std::vector<client_info>& active_clients_data);

#endif
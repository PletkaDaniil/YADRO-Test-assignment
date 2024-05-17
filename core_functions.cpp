#include "core_functions.h"

client_info create_client_information(int number_of_command, const std::vector<std::string>& data, const std::string& current_file_line, int total_number_of_tables, std::map<int, bool>& table_availability) {
    client_info new_client_information;
    switch (number_of_command){
        case 1: new_client_information = {-1, number_of_command, data[0], data[2]}; break;
        case 2:
            if (data.size() == 4 && table_number_range_check(data[3], total_number_of_tables)){
                new_client_information = {std::stoi(data[3]), number_of_command,data[0], data[2]};
                table_availability[std::stoi(data[3])] = true;
                break;
            }else{throw std::string{"Format error in line: "}.append(current_file_line);}
        case 3: new_client_information = {-1, number_of_command, data[0], data[2]}; break;
        case 4: new_client_information = {-1, number_of_command, data[0], data[2]}; break;
    }
    return new_client_information;
}

void ensure_data_correctness(const std::string& current_file_line, int& check_stage, int& total_number_of_tables, int& start_of_work, int& end_of_work, int& table_price, int& previous_time, std::map<int, bool>& table_availability, std::vector<client_info>& active_clients_data) {
    std::vector<std::string> data = split_line_by_spaces(current_file_line);
    switch (check_stage){
        case 1:
            if (data.size() == 1 && only_digits_check(data[0])){
                total_number_of_tables = std::stoi(data[0]);
                ++check_stage;
                break;
            }else{ throw std::string{"Format error in line: "}.append(current_file_line); }
        case 2:
            if (data.size() == 2 && time_valid_check(data[0]) && time_valid_check(data[1])){
                start_of_work = time_to_minutes(data[0]);
                end_of_work = time_to_minutes(data[1]);
                ++check_stage;
                break;
            }else{ throw std::string{"Format error in line: "}.append(current_file_line); }
        case 3:
            if (data.size() == 1 && only_digits_check(data[0]) ){
                table_price = std::stoi(data[0]);
                ++check_stage;
                break;
            }else{ throw std::string{"Format error in line: "}.append(current_file_line); }
        case 4:
            if (data.size() > 2 && data.size() < 5 && time_valid_check(data[0]) && command_check(data[1]) && client_name_valid_check(data[2])){
                int current_time = time_to_minutes(data[0]);
                if (current_time < previous_time){
                    throw std::string{"Format error in line: "}.append(current_file_line);
                }
                previous_time = current_time;
                active_clients_data.push_back(create_client_information(std::stoi(data[1]), data, current_file_line, total_number_of_tables, table_availability));
                break;
            }else{ throw std::string{"Format error in line: "}.append(current_file_line); }   
    }
}
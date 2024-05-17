#include "core_functions.h"

// Checking the input file data
void ensure_data_correctness(const std::string& current_file_line, int& check_stage, int& total_number_of_tables, int& start_of_work, int& end_of_work, int& table_price, int& previous_time, std::map<int, bool>& table_availability, std::vector<client_info>& active_clients_data) {
    std::vector<std::string> data = split_line_by_spaces(current_file_line);
    switch (check_stage){
        case 1: // Stage of checking the correctness for:  "number of tables in the computer club"
            if (data.size() == 1 && only_digits_check(data[0])){
                total_number_of_tables = std::stoi(data[0]);
                ++check_stage;
                break;
            }else{ throw std::string{"Format error in line: "}.append(current_file_line); }
        case 2: // Stage of checking the correctness for:  "start time" --> "end time"
            if (data.size() == 2 && time_valid_check(data[0]) && time_valid_check(data[1])){
                start_of_work = time_to_minutes(data[0]);
                end_of_work = time_to_minutes(data[1]);
                ++check_stage;
                break;
            }else{ throw std::string{"Format error in line: "}.append(current_file_line); }
        case 3: // Stage of checking the correctness for:  "hourly cost in the computer club"
            if (data.size() == 1 && only_digits_check(data[0]) ){
                table_price = std::stoi(data[0]);
                ++check_stage;
                break;
            }else{ throw std::string{"Format error in line: "}.append(current_file_line); }
        case 4: // Stage of checking the correctness for:  "event time" --> "event id" --> "event body"
            if (data.size() > 2 && data.size() < 5 && time_valid_check(data[0]) && command_check(data[1]) && client_name_valid_check(data[2])){
                int current_time = time_to_minutes(data[0]);
                if (current_time < previous_time){  // Also check that events are sequential in time
                    throw std::string{"Format error in line: "}.append(current_file_line);
                }
                previous_time = current_time;
                active_clients_data.push_back(create_client_information(std::stoi(data[1]), data, current_file_line, total_number_of_tables, table_availability));
                break;
            }else{ throw std::string{"Format error in line: "}.append(current_file_line); }   
    }
}

// Adding information about all clients to the "database"
client_info create_client_information(int number_of_command, const std::vector<std::string>& data, const std::string& current_file_line, int total_number_of_tables, std::map<int, bool>& table_availability) {
    client_info new_client_information;
    switch (number_of_command){
        case 1: new_client_information = {-1, number_of_command, data[0], data[2]}; break;
        case 2:
            // Check for the correctness of the table number
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


//--------------------------------------------------------------------------------------------------------------------------


void process_club_work_and_handle_clients(const std::vector<client_info>& active_clients_data, std::map<int, bool>& table_availability, int start_of_work, int end_of_work, int table_price, int total_number_of_tables) {
    std::cout << convert_minutes_to_hours_minutes(start_of_work) << "\n";
    std::queue<std::string> clients_waiting_for_tables;
    std::set<std::string> clients_in_club;
    std::map<std::string, table_info> client_to_table;
    std::map<int, result_after_work> time_spent_at_each_table;
    int queue_size = 0;
    for (const auto& client: active_clients_data){
        switch (client.command){
            case 1:
                handle_client_event_1(client, clients_waiting_for_tables, clients_in_club, start_of_work, end_of_work, queue_size);
                break;
            case 2:
                handle_client_event_2(client, table_availability, client_to_table, time_spent_at_each_table, table_price,
                                        start_of_work, end_of_work, clients_waiting_for_tables, clients_in_club, queue_size);
                break;
            case 3:
                handle_client_event_3(client, table_availability, clients_waiting_for_tables, clients_in_club, total_number_of_tables, queue_size);
                break;
            case 4:
                handle_client_event_4(client, table_availability, client_to_table, time_spent_at_each_table, table_price, end_of_work, clients_waiting_for_tables, clients_in_club, queue_size);
                break;
        }
    }
    display_latest_club_clients_info(clients_in_club, client_to_table, time_spent_at_each_table, end_of_work, table_price);
    display_revenue_for_each_table(time_spent_at_each_table);
}


void display_latest_club_clients_info(const std::set<std::string>& clients_in_club, std::map<std::string, table_info>& client_to_table, 
                                    std::map<int, result_after_work>& time_spent_at_each_table, int end_of_work, int table_price) {

    std::string ending_of_day_work = convert_minutes_to_hours_minutes(end_of_work);
    for(const auto& client: clients_in_club) {
        std::cout << ending_of_day_work << " 11 " << client << "\n";
        int tmp_timer = end_of_work - client_to_table[client].timer;
                    
        time_spent_at_each_table[client_to_table[client].table].money += earnings_per_table(tmp_timer, table_price);
        time_spent_at_each_table[client_to_table[client].table].all_time_for_table += tmp_timer;
    }
    std::cout << ending_of_day_work << "\n";
}


void display_revenue_for_each_table(const std::map<int, result_after_work>& time_spent_at_each_table) {
    for (const auto& result : time_spent_at_each_table) {
        std::cout  << result.first  << " "  << result.second.money
                   << " "  << convert_minutes_to_hours_minutes(result.second.all_time_for_table)  << "\n";
    }
}


void handle_client_event_1 (const client_info& client, std::queue<std::string>& clients_waiting_for_tables, std::set<std::string>& clients_in_club, int start_of_work, int end_of_work, int& queue_size) {
    std::cout << client.time << " " << client.command << " " << client.client_name << "\n";
    if (!client_entry_valid_check(client.time, start_of_work, end_of_work)) {
        std::cout << client.time << " 13 NotOpenYet" << "\n";
        return;
    }
    if (clients_in_club.count(client.client_name)) {
        std::cout << client.time << " 13 YouShallNotPass" << "\n";
        return;
    }
    clients_in_club.insert(client.client_name);
    clients_waiting_for_tables.push(client.client_name);
    ++queue_size;
}


void handle_client_event_2 (const client_info& client, std::map<int, bool>& table_availability, std::map<std::string, table_info>& client_to_table, std::map<int, result_after_work>& time_spent_at_each_table,
                            int table_price, int start_of_work, int end_of_work, std::queue<std::string>& clients_waiting_for_tables, std::set<std::string>& clients_in_club, int& queue_size) {
    std::cout << client.time << " " << client.command << " " << client.client_name << " " << client.table_num << "\n";
    if (!clients_in_club.count(client.client_name)) {
        std::cout << client.time << " 13 ClientUnknown" << "\n";
        return;
    }
    if (table_availability[client.table_num]) {
        table_availability[client.table_num] = false;
        if (client_to_table.find(client.client_name) != client_to_table.end()) {
            table_availability[client_to_table[client.client_name].table] = true;
            int tmp_timer = time_to_minutes(client.time) - client_to_table[client.client_name].timer;
            time_spent_at_each_table[client.table_num].money += earnings_per_table(tmp_timer, table_price);
            time_spent_at_each_table[client.table_num].all_time_for_table += tmp_timer;
        }
        client_to_table[client.client_name] = {client.table_num, time_to_minutes(client.time)};
        if (clients_waiting_for_tables.front() == client.client_name) {
            clients_waiting_for_tables.pop();
            --queue_size;
        } //else{...} <-- you can add some special error here, if necessary
    } else {
        std::cout << client.time << " 13 PlaceIsBusy" << "\n";
    }
}


void handle_client_event_3 (const client_info& client, std::map<int, bool>& table_availability, std::queue<std::string>& clients_waiting_for_tables,
                            std::set<std::string>& clients_in_club, int total_number_of_tables, int& queue_size) {
    std::cout << client.time << " " << client.command << " " << client.client_name << "\n";
    if (clients_in_club.count(client.client_name)) {
        bool empty_table = false;
        for (const auto& table: table_availability) {
            if (table.second == true) {
                empty_table = true;
                std::cout << client.time << " 13 ICanWaitNoLonger!" << "\n";
                break;
            }
        }
        if (empty_table) {
            return;
        }
    }
    if (queue_size >= total_number_of_tables) {
        std::cout << client.time << " 11 " << client.client_name << "\n";
        --queue_size;
        clients_in_club.erase(client.client_name);
    }
}


void handle_client_event_4(const client_info& client, std::map<int, bool>& table_availability, std::map<std::string, table_info>& client_to_table, std::map<int, result_after_work>& time_spent_at_each_table, int table_price, int end_of_work, std::queue<std::string>& clients_waiting_for_tables, std::set<std::string>& clients_in_club, int& queue_size) {
    std::cout << client.time << " " << client.command << " " << client.client_name << "\n";
    if (!clients_in_club.count(client.client_name)) {
        std::cout << client.time << " 13 ClientUnknown" << "\n";
        return;
    }
    if (client_to_table.find(client.client_name) != client_to_table.end()) {
        table_availability[client_to_table[client.client_name].table] = true;
        int tmp_timer = time_to_minutes(client.time) - client_to_table[client.client_name].timer;
        time_spent_at_each_table[client_to_table[client.client_name].table].money += earnings_per_table(tmp_timer, table_price);
        time_spent_at_each_table[client_to_table[client.client_name].table].all_time_for_table += tmp_timer;

        while (!clients_waiting_for_tables.empty()) {
            std::string first_client_in_queue = clients_waiting_for_tables.front();
            if (clients_in_club.count(first_client_in_queue)) {
                client_to_table[first_client_in_queue] = client_to_table[client.client_name];
                table_availability[client_to_table[client.client_name].table] = false;
                std::cout << client.time << " 12 " << first_client_in_queue << " " << client_to_table[client.client_name].table << "\n";
                client_to_table[first_client_in_queue].timer = time_to_minutes(client.time);
                clients_waiting_for_tables.pop();
                --queue_size;
                break;
            }
            clients_waiting_for_tables.pop();
        }
    } else {
        --queue_size;
    }
    clients_in_club.erase(client.client_name);
}
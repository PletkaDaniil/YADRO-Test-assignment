#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

struct client{
    int table_num = -1;
    int command = -1;
    std::string time;
    std::string client_name;
};

struct table_info{
    int table;
    int timer;
};

struct result_after_work{
    int all_time_for_table = 0;
    int money = 0;
};

bool only_digits_check(const std::string& line){
    return line.find_first_not_of("0123456789") == std::string::npos;
}

bool command_check(const std::string& line){
    if (!only_digits_check(line)){
        return false;
    }
    int number_of_command = std::stoi(line);
    return number_of_command >= 1 && number_of_command <= 4;
}

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

bool table_number_range_check(const std::string& table_number, const double& total_number_of_tables) {
    if (!only_digits_check(table_number)) {
        return false;
    }
    int table_number_value = std::stoi(table_number);
    return table_number_value >= 1 && table_number_value <= total_number_of_tables;
}

int time_to_minutes(const std::string& time){
    int hours = std::stoi(time.substr(0, 2));
    int minutes = std::stoi(time.substr(3, 2));
    return hours * 60 + minutes;
}

std::vector<std::string> split_line_by_spaces(const std::string& line){
    std::istringstream stream_line(line);
    std::vector<std::string> data;
    std::string current_part_of_line;
    while (stream_line >> current_part_of_line) {
        data.push_back(current_part_of_line);
    }
    return data;
}


bool client_entry_valid_check(const std::string& time, const int& start_of_work, const int& end_of_work){
    int minutes = time_to_minutes(time);
    return minutes >= start_of_work && minutes <= end_of_work;
}

std::string convert_minutes_to_hours_minutes(const int& all_minutes) {
    int hours = all_minutes / 60;
    int minutes = all_minutes % 60;

    std::string hours_string = (hours < 10) ? "0" + std::to_string(hours) : std::to_string(hours);
    std::string minutes_string = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);

    std::string timeString = hours_string + ":" + minutes_string;

    return timeString;
}

int earnings_per_table(const int& minutes, const int& price){
    return ((minutes + 59) / 60) * price;
}


int main(int argc, char* argv[]){
    if (argc != 2){
        std::cerr << "Use " << argv[0] << " source destination" << "\n";
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()){
        std::cerr << "Can not open file " << argv[1] << "\n";
        return 1;
    }
    
    try{
        std::string str;
        int start_of_work = -1;
        int end_of_work = -1;
        int count = 1;
        int total_number_of_tables = 0;
        int previous_time = -1;
        int table_price = 0;

        std::map <int, bool> table_availability;
        std::vector<client> active_clients_data;
        while (getline(input_file, str)){
            std::vector<std::string> data = split_line_by_spaces(str);
            switch (count){
                case 1:
                    if (data.size() == 1 && only_digits_check(data[0])){
                        total_number_of_tables = std::stoi(data[0]);
                        ++count;
                        break;
                    }else{ throw std::string{"Format error in line: "}.append(str); }
                case 2:
                    if (data.size() == 2 && time_valid_check(data[0]) && time_valid_check(data[1])){
                        start_of_work = time_to_minutes(data[0]);
                        end_of_work = time_to_minutes(data[1]);
                        ++count;
                        break;
                    }else{ throw std::string{"Format error in line: "}.append(str); }
                case 3:
                    if (data.size() == 1 && only_digits_check(data[0]) ){
                        table_price = std::stoi(data[0]);
                        ++count;
                        break;
                    }else{ throw std::string{"Format error in line: "}.append(str); }
                case 4:
                    if (data.size() > 2 && data.size() < 5 && time_valid_check(data[0]) && command_check(data[1]) && client_name_valid_check(data[2])){
                        int current_time = time_to_minutes(data[0]);
                        if (current_time < previous_time){
                            throw std::string{"Format error in line: "}.append(str);
                        }
                        previous_time = current_time;
                        client new_client;
                        int number_of_command = std::stoi(data[1]);
                        switch (number_of_command){
                            case 1: new_client = {-1, number_of_command, data[0], data[2]}; break;
                            case 2:
                                if (data.size() == 4 && table_number_range_check(data[3], total_number_of_tables)){
                                    new_client = {std::stoi(data[3]), number_of_command,data[0], data[2]};
                                    table_availability[std::stoi(data[3])] = true;
                                    break;
                                }else{throw std::string{"Format error in line: "}.append(str);}
                            case 3: new_client = {-1, number_of_command, data[0], data[2]}; break;
                            case 4: new_client = {-1, number_of_command, data[0], data[2]}; break;
                        }
                        active_clients_data.push_back(new_client);
                        break;
                    }else{ throw std::string{"Format error in line: "}.append(str); }   
            }
        }
        // for(const auto pair: table_availability) {
        //     std::cout << "Table " << pair.first << ": " 
        //             << (pair.second.table_status ? "Available" : "Not Available") 
        //             << " " <<  pair.second.table_taken_by_client <<std::endl;
        // }
        std::cout << convert_minutes_to_hours_minutes(start_of_work) << "\n";
        std::queue<std::string> clients_waiting_for_tables;
        std::map<std::string, table_info> client_to_table;
        std::set<std::string> clients_in_club;
        std::map<int, result_after_work> time_spent_at_each_table;
        int queue_size = 0;
        for (const auto& client: active_clients_data) {
            switch (client.command){
                case 1:
                    std::cout << client.time << " " << client.command << " " << client.client_name << "\n";
                    if(!client_entry_valid_check(client.time, start_of_work, end_of_work)){
                        std::cout << client.time << " 13 NotOpenYet" << "\n";
                        break;
                    }
                    if (clients_in_club.count(client.client_name)){
                        std::cout << client.time << " 13 YouShallNotPass" << "\n";
                        break;  
                    }
                    clients_in_club.insert(client.client_name);
                    clients_waiting_for_tables.push(client.client_name);
                    ++queue_size;
                    break;
                case 2:
                    std::cout << client.time << " " << client.command << " " << client.client_name << " " << client.table_num << "\n";
                    if (!clients_in_club.count(client.client_name)){
                        std::cout << client.time << " 13 ClientUnknown" << "\n";
                        break;
                    }
                    if (table_availability[client.table_num]){
                        table_availability[client.table_num] = false;
                        if (client_to_table.find(client.client_name) != client_to_table.end()){
                            table_availability[client_to_table[client.client_name].table] = true;
                            int tmp_timer = time_to_minutes(client.time) - client_to_table[client.client_name].timer;
                            time_spent_at_each_table[client.table_num].money += earnings_per_table(tmp_timer, table_price);
                            time_spent_at_each_table[client.table_num].all_time_for_table += tmp_timer;
                            std::cout << client.table_num << " " << time_to_minutes(client.time) - client_to_table[client.client_name].timer << "!!!!!!!!!!!!!!!!" <<std::endl;
                        }
                        client_to_table[client.client_name].table = client.table_num;
                        client_to_table[client.client_name].timer = time_to_minutes(client.time);
                        if (clients_waiting_for_tables.front() == client.client_name){
                            clients_waiting_for_tables.pop();
                            --queue_size;
                        } //else{...} <-- you can add some special error here, if necessary
                    }else{
                        std::cout << client.time << " 13 PlaceIsBusy" << "\n";
                        break;
                    }
                    break;
                case 3:
                    std::cout << client.time << " " << client.command << " " << client.client_name << "\n";
                    if (clients_in_club.count(client.client_name)){
                        bool empty_table = false;
                        for (const auto& table: table_availability) {
                            if (table.second == true) {
                                empty_table = true;
                                std::cout << client.time << " 13 ICanWaitNoLonger!" << "\n";
                                break;
                            }
                        }
                        if (empty_table){break;}
                    }
                    if (queue_size >= total_number_of_tables){
                        std::cout << client.time << " 11 " << client.client_name << "\n";
                        --queue_size;
                        clients_in_club.erase(client.client_name);
                    }
                    break;
                case 4:
                    std::cout << client.time << " " << client.command << " " << client.client_name << "\n";
                    if (!clients_in_club.count(client.client_name)){
                        std::cout << client.time << " 13 ClientUnknown" << "\n";
                        break;  
                    }

                    if (client_to_table.find(client.client_name) != client_to_table.end()){

                        table_availability[client_to_table[client.client_name].table] = true;

                        int tmp_timer = time_to_minutes(client.time) - client_to_table[client.client_name].timer;

                        time_spent_at_each_table[client_to_table[client.client_name].table].money += earnings_per_table(tmp_timer, table_price);
                        time_spent_at_each_table[client_to_table[client.client_name].table].all_time_for_table += tmp_timer;
                        // std::cout << client_to_table[client.client_name].table << " " << time_to_minutes(client.time) - client_to_table[client.client_name].timer << "!!!!!!!!!!!!!!!!" <<std::endl;
                        
                        
                        while (!clients_waiting_for_tables.empty()){
                            std::string first_client_in_queue = clients_waiting_for_tables.front();
                            if (clients_in_club.count(first_client_in_queue)){
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
                    }else{
                        --queue_size;
                    }
                    clients_in_club.erase(client.client_name);
                    break;
            }
        }
        std::string ending_of_day_work = convert_minutes_to_hours_minutes(end_of_work);
        for(const auto& client: clients_in_club) {
            std::cout << ending_of_day_work << " 11 " << client << "\n";
            int tmp_timer = end_of_work - client_to_table[client].timer;
                        
            time_spent_at_each_table[client_to_table[client].table].money += earnings_per_table(tmp_timer, table_price);
            time_spent_at_each_table[client_to_table[client].table].all_time_for_table += tmp_timer;
        }
        std::cout << ending_of_day_work << "\n";


        for (const auto& elem : time_spent_at_each_table) {
            std::cout << elem.first << " " << elem.second.money
                    << " " << convert_minutes_to_hours_minutes(elem.second.all_time_for_table) << std::endl;
        }
    }catch (const std::string& error_message){
        std::cerr << error_message << "\n";
    }

    input_file.close();
    return 0;
}
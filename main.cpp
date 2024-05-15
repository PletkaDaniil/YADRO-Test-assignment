#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

bool only_digits_check(const std::string& line){
    return line.find_first_not_of("0123456789") == std::string::npos;
}

bool commands_check(const std::string& line){
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

std::vector<std::string> split_line_by_spaces(const std::string& line){
    std::istringstream stream_line(line);
    std::vector<std::string> data;
    std::string current_part_of_line;
    while (stream_line >> current_part_of_line) {
        data.push_back(current_part_of_line);
    }
    return data;
}

int main(int argc, char* argv[]){
    if (argc != 2){
        std::cerr << "Use " << argv[0] << " source destination" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()){
        std::cerr << "Can not open file " << argv[1] << std::endl;
        return 1;
    }
    
    try{
        std::string str;
        int count = 1;
        int total_number_of_tables = 0;
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
                        ++count;
                        break;
                    }else{ throw std::string{"Format error in line: "}.append(str); }
                case 3:
                    if (data.size() == 1 && only_digits_check(data[0]) ){
                        ++count;
                        break;
                    }else{ throw std::string{"Format error in line: "}.append(str); }
                case 4:
                    if (data.size() > 2 && data.size() < 5 && time_valid_check(data[0]) && commands_check(data[1]) && client_name_valid_check(data[2])){
                        int number_of_command = std::stoi(data[1]);
                        switch (number_of_command){
                            case 1: break;
                            case 2:
                                if (data.size() == 4 && table_number_range_check(data[3], total_number_of_tables)){
                                    break;
                                }else{throw std::string{"Format error in line: "}.append(str);}
                            case 3: break;
                            case 4: break;
                        }
                        break;
                    }else{ throw std::string{"Format error in line: "}.append(str); }   
                // default:
                //     break;
            }
        }
    }catch (const std::string& error_message){
        std::cout << error_message << std::endl;
    }

    input_file.close();
    return 0;
}
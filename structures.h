#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

struct client_info{
    int table_num;
    int command;
    std::string time;
    std::string client_name;
    client_info(int new_table_num = -1, int new_command = -1, const std::string& new_time = "HH:MM", const std::string& new_client_name = "None")
        : table_num(new_table_num), command(new_command), time(new_time), client_name(new_client_name) {}
};

struct table_info{
    int table;
    int timer;
};

struct result_after_work{
    int all_time_for_table = 0;
    int money = 0;
};

#endif
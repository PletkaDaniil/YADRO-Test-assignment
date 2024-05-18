#ifndef CLUB_H
#define CLUB_H

#include "core_functions.h"

class Club{
private:
    int start_of_work = -1;
    int end_of_work = -1;
    int check_stage = 1;
    int total_number_of_tables = 0;
    int previous_time = -1;
    int table_price = 0;

    std::map <int, bool> table_availability;
    std::vector<client_info> active_clients_data;

public:
    void file_correctness(const std::string& current_file_line){
        ensure_data_correctness(current_file_line, check_stage, total_number_of_tables, start_of_work, end_of_work, table_price, previous_time, table_availability, active_clients_data);
    }

    void club_working(){
        process_club_work_and_handle_clients(active_clients_data, table_availability, start_of_work, end_of_work, table_price, total_number_of_tables); 
    }
};

#endif
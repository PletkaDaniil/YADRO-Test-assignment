#include <fstream>
#include "core_functions.h"

int main(int argc, char* argv[]){
    check_args(argc, argv);

    std::ifstream input_file;
    open_input_file(input_file, argv);
    try{
        std::string current_file_line;
        int start_of_work = -1;
        int end_of_work = -1;
        int check_stage = 1;
        int total_number_of_tables = 0;
        int previous_time = -1;
        int table_price = 0;

        std::map <int, bool> table_availability;
        std::vector<client_info> active_clients_data;

        // Reading the input file information (and checking it)
        while (getline(input_file, current_file_line)){
            ensure_data_correctness(current_file_line, check_stage, total_number_of_tables, start_of_work, end_of_work, table_price, previous_time, table_availability, active_clients_data);
        }
        process_club_work_and_handle_clients(active_clients_data, table_availability, start_of_work, end_of_work, table_price, total_number_of_tables);   
    }catch (const std::string& error_message){
        std::cerr << error_message << "\n";
    }
    ending(input_file);
}
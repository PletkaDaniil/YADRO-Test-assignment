#ifndef CORE_FUNCTIONS_H
#define CORE_FUNCTIONS_H

#include <map>
#include <set>
#include <queue>

#include "helper_functions.h"
#include "structures.h"

void ensure_data_correctness(const std::string& current_file_line, int& check_stage, int& total_number_of_tables, int& start_of_work, int& end_of_work, int& table_price, int& previous_time, std::map<int, bool>& table_availability, std::vector<client_info>& active_clients_data);
client_info create_client_information(int number_of_command, const std::vector<std::string>& data, const std::string& current_file_line, int total_number_of_tables, std::map<int, bool>& table_availability);

void process_club_work_and_handle_clients(const std::vector<client_info>& active_clients_data, std::map<int, bool>& table_availability, int start_of_work, int end_of_work, int table_price, int total_number_of_tables);
void handle_client_event_1 (const client_info& client, std::queue<std::string>& clients_waiting_for_tables, std::set<std::string>& clients_in_club, int start_of_work, int end_of_work, int& queue_size);
void handle_client_event_2 (const client_info& client, std::map<int, bool>& table_availability, std::map<std::string, table_info>& client_to_table, std::map<int, result_after_work>& time_spent_at_each_table,
                            int table_price, int start_of_work, int end_of_work, std::queue<std::string>& clients_waiting_for_tables, std::set<std::string>& clients_in_club, int& queue_size);
void handle_client_event_3 (const client_info& client, std::map<int, bool>& table_availability, std::queue<std::string>& clients_waiting_for_tables,
                            std::set<std::string>& clients_in_club, int total_number_of_tables, int& queue_size);
void handle_client_event_4(const client_info& client, std::map<int, bool>& table_availability, std::map<std::string, table_info>& client_to_table, std::map<int, result_after_work>& time_spent_at_each_table, int table_price, int end_of_work, std::queue<std::string>& clients_waiting_for_tables, std::set<std::string>& clients_in_club, int& queue_size);
void display_latest_club_clients_info(const std::set<std::string>& clients_in_club, std::map<std::string, table_info>& client_to_table, 
                                    std::map<int, result_after_work>& time_spent_at_each_table, int end_of_work, int table_price);
void display_revenue_for_each_table(const std::map<int, result_after_work>& time_spent_at_each_table);

#endif
#include <fstream>
#include "Club.h"

int main(int argc, char* argv[]){
    check_args(argc, argv);
    std::ifstream input_file;
    open_input_file(input_file, argv);
    Club computer_club;
    try{
        // Reading the input file information (and checking it)
        std::string current_file_line;
        while (getline(input_file, current_file_line)){
            computer_club.file_correctness(current_file_line);
        }
        computer_club.club_working(); 

    }catch (const std::string& error_message){
        std::cerr << error_message << "\n";
    }
    ending(input_file);
}
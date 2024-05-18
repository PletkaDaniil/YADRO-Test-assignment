#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <streambuf>
#include "Club.h"

// #ifdef _WIN32
//     #include <direct.h>
//     #define GETCWD _getcwd
// #else
//     #include <unistd.h>
//     #define GETCWD getcwd
// #endif

void run_test_for_file_check(const std::string& input_file_name, const std::string& expected_output) {
    std::ifstream input_file(input_file_name);
    ASSERT_TRUE(input_file.is_open());
    std::streambuf* old_cout_stream_buf = std::cout.rdbuf();
    std::ostringstream str_cout;
    std::cout.rdbuf(str_cout.rdbuf());

    Club computer_club;
    try{
        std::string current_file_line;
        while (getline(input_file, current_file_line)){
            computer_club.file_correctness(current_file_line);
        }
        computer_club.club_working();
    }catch (const std::string& error_message){
        std::cout.rdbuf(old_cout_stream_buf);
        // std::cout << error_message << std::endl;
        EXPECT_EQ(error_message, expected_output);
    }
}

void run_test_for_club_working_check(const std::string& input_file_path, const std::string& expected_output) {
    std::ifstream input_file(input_file_path);
    ASSERT_TRUE(input_file.is_open());
    std::streambuf* old_cout_stream_buf = std::cout.rdbuf();
    std::ostringstream str_cout;
    std::cout.rdbuf(str_cout.rdbuf());

    Club computer_club;
    try{
        std::string current_file_line;
        while (getline(input_file, current_file_line)){
            computer_club.file_correctness(current_file_line);
        }
        computer_club.club_working(); 
    }catch (const std::string& error_message){
        std::cout << error_message << std::endl;
        FAIL();
    }
    std::cout.rdbuf(old_cout_stream_buf);
    // std::cout << str_cout.str() << std::endl;
    // std::cout << expected_output << std::endl;
    EXPECT_EQ(str_cout.str(), expected_output);
}


TEST(ClubTest1, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input1.txt", "Format error in line: 90:00 19:00");
}

TEST(ClubTest2, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input2.txt", "Format error in line: s");
}

TEST(ClubTest3, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input3.txt", "Format error in line: 1 0");
}

TEST(ClubTest4, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input4.txt", "Format error in line: 09:52 3 client1");
}

TEST(ClubTest5, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input5.txt", "Format error in line: 19:00 09:00");
}

TEST(ClubTest6, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input6.txt", "Format error in line: 08:48 1 cLient1");
}

TEST(ClubTest7, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input7.txt", "Format error in line: 09:448 1 client2");
}

TEST(ClubTest8, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input8.txt", "Format error in line: 8:48 1 client1");
}

TEST(ClubTest9, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input9.txt", "Format error in line: 09:54 2 client1 7");
}

TEST(ClubTest10, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input10.txt", "Format error in line: 09:54 2 client1 third");
}

TEST(ClubTest11, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input11.txt", "Format error in line: 09:52 5 client1");
}

TEST(ClubTest12, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input12.txt", "Format error in line: 09:52 second client1");
}

TEST(ClubTest13, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input13.txt", "Format error in line: 08-48 1 client1");
}

TEST(ClubTest14, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input14.txt", "Format error in line: 10");
}

TEST(ClubTest15, CheckOutput) {
    run_test_for_file_check("all_tests/input_tests/input15.txt", "Format error in line: 11:3 1 client4");
}

TEST(ClubTest16, CheckOutput) {
    std::string expected_output = 
    "09:00\n"
    "08:48 1 client1\n"
    "08:48 13 NotOpenYet\n"
    "09:41 1 client1\n"
    "09:48 1 client2\n"
    "09:52 3 client1\n"
    "09:52 13 ICanWaitNoLonger!\n"
    "09:54 2 client1 1\n"
    "10:25 2 client2 2\n"
    "10:58 1 client3\n"
    "10:59 2 client3 3\n"
    "11:30 1 client4\n"
    "11:35 2 client4 2\n"
    "11:35 13 PlaceIsBusy\n"
    "11:45 3 client4\n"
    "12:33 4 client1\n"
    "12:33 12 client4 1\n"
    "12:43 4 client2\n"
    "15:52 4 client4\n"
    "19:00 11 client3\n"
    "19:00\n"
    "1 70 05:58\n"
    "2 30 02:18\n"
    "3 90 08:01\n";
    run_test_for_club_working_check("all_tests/input_tests/input16.txt", expected_output);
}

TEST(ClubTest17, CheckOutput) {
    std::string expected_output = 
    "09:00\n"
    "09:48 1 client1\n"
    "18:30 4 client1\n"
    "19:00\n";
    run_test_for_club_working_check("all_tests/input_tests/input17.txt", expected_output);
}

TEST(ClubTest18, CheckOutput) {
    std::string expected_output = 
    "08:10\n"
    "07:48 1 client1\n"
    "07:48 13 NotOpenYet\n"
    "08:41 1 client1\n"
    "09:47 4 client1\n"
    "09:48 1 client1\n"
    "09:52 3 client1\n"
    "09:52 13 ICanWaitNoLonger!\n"
    "09:54 2 client1 1\n"
    "09:55 2 client1 2\n"
    "12:33 4 client1\n"
    "12:43 4 client2\n"
    "12:43 13 ClientUnknown\n"
    "20:01\n"
    "1 10 00:01\n"
    "2 30 02:38\n";
    run_test_for_club_working_check("all_tests/input_tests/input18.txt", expected_output);
}

TEST(ClubTest19, CheckOutput) {
    std::string expected_output = 
    "08:10\n"
    "07:48 1 client1\n"
    "07:48 13 NotOpenYet\n"
    "08:41 1 client1\n"
    "09:47 4 client1\n"
    "09:48 1 client1\n"
    "09:52 3 client1\n"
    "09:52 13 ICanWaitNoLonger!\n"
    "09:54 2 client1 1\n"
    "09:55 2 client1 5\n"
    "10:11 1 client3\n"
    "10:13 1 client4\n"
    "12:33 4 client1\n"
    "12:33 12 client3 5\n"
    "12:43 4 client2\n"
    "12:43 13 ClientUnknown\n"
    "20:01 11 client3\n"
    "20:01 11 client4\n"
    "20:01\n"
    "1 10 00:01\n"
    "5 110 10:06\n";
    run_test_for_club_working_check("all_tests/input_tests/input19.txt", expected_output);
}

TEST(ClubTest20, CheckOutput) {
    std::string expected_output = 
    "07:13\n"
    "06:48 1 client1\n"
    "06:48 13 NotOpenYet\n"
    "08:41 1 client1\n"
    "09:47 4 client1\n"
    "09:48 1 client1\n"
    "09:52 3 client1\n"
    "09:52 13 ICanWaitNoLonger!\n"
    "09:54 2 client1 1\n"
    "09:55 2 client1 2\n"
    "10:11 1 client3\n"
    "10:12 2 client3 1\n"
    "10:13 1 client4\n"
    "10:14 1 client5\n"
    "10:15 3 client5\n"
    "10:15 11 client5\n"
    "10:16 1 client6\n"
    "10:17 3 client6\n"
    "10:17 11 client6\n"
    "10:18 1 client7\n"
    "10:19 3 client7\n"
    "10:19 11 client7\n"
    "12:33 4 client1\n"
    "12:33 12 client4 2\n"
    "12:43 4 client2\n"
    "12:43 13 ClientUnknown\n"
    "16:08 11 client3\n"
    "16:08 11 client4\n"
    "16:08\n"
    "1 77 05:57\n"
    "2 77 06:13\n";
    run_test_for_club_working_check("all_tests/input_tests/input20.txt", expected_output);
}

TEST(ClubTest21, CheckOutput) {
    std::string expected_output = 
    "06:51\n"
    "06:48 1 client1\n"
    "06:48 13 NotOpenYet\n"
    "08:41 1 client1\n"
    "09:47 1 client1\n"
    "09:47 13 YouShallNotPass\n"
    "12:33 4 client1\n"
    "18:37\n";
    run_test_for_club_working_check("all_tests/input_tests/input21.txt", expected_output);
}

TEST(ClubTest22, CheckOutput) {
    std::string expected_output = 
    "07:30\n"
    "08:45 1 client1\n"
    "09:45 3 client1\n"
    "09:45 13 ICanWaitNoLonger!\n"
    "09:54 2 client1 3\n"
    "10:25 1 client2\n"
    "10:58 1 client3\n"
    "10:59 4 client1\n"
    "10:59 12 client2 3\n"
    "11:30 1 client4\n"
    "11:35 2 client3 1\n"
    "11:45 4 client3\n"
    "11:45 12 client4 1\n"
    "20:07 11 client2\n"
    "20:07 11 client4\n"
    "20:07\n"
    "1 110 08:32\n"
    "3 132 10:13\n";
    run_test_for_club_working_check("all_tests/input_tests/input22.txt", expected_output);
}

TEST(ClubTest23, CheckOutput) {
    std::string expected_output = 
    "06:31\n"
    "08:45 1 client1\n"
    "09:45 3 client1\n"
    "09:45 13 ICanWaitNoLonger!\n"
    "09:54 2 client1 9\n"
    "10:25 1 client2\n"
    "10:58 1 client3\n"
    "11:30 1 client4\n"
    "11:35 1 client5\n"
    "13:41 1 client6\n"
    "14:02 4 client5\n"
    "15:00 4 client2\n"
    "20:06 4 client1\n"
    "20:06 12 client3 9\n"
    "21:41 2 client2 8\n"
    "21:41 13 ClientUnknown\n"
    "21:42 2 client3 8\n"
    "21:50 4 client6\n"
    "23:01 11 client3\n"
    "23:01 11 client4\n"
    "23:01\n"
    "8 230 01:19\n"
    "9 1495 11:48\n";
    run_test_for_club_working_check("all_tests/input_tests/input23.txt", expected_output);
}

TEST(ClubTest24, CheckOutput) {
    std::string expected_output = 
    "06:00\n"
    "08:00 1 client1\n"
    "09:00 1 client2\n"
    "09:25 2 client1 1\n"
    "09:35 2 client2 2\n"
    "10:00 1 client3\n"
    "11:00 1 client4\n"
    "12:00 1 client5\n"
    "13:00 1 client6\n"
    "14:00 1 client7\n"
    "15:00 3 client7\n"
    "15:00 11 client7\n"
    "16:00 3 client1\n"
    "16:00 11 client1\n"
    "17:00 2 client9 2\n"
    "17:00 13 ClientUnknown\n"
    "17:00 2 client2 1\n"
    "17:00 13 PlaceIsBusy\n"
    "19:01 4 client1\n"
    "19:01 13 ClientUnknown\n"
    "18:00 11 client2\n"
    "18:00 11 client3\n"
    "18:00 11 client4\n"
    "18:00 11 client5\n"
    "18:00 11 client6\n"
    "18:00\n"
    "2 9 08:25\n";
    run_test_for_club_working_check("all_tests/input_tests/input24.txt", expected_output);
}

TEST(ClubTest25, CheckOutput) {
    std::string expected_output = 
    "19:30\n"
    "08:45 1 client1\n"
    "08:45 13 NotOpenYet\n"
    "19:45 4 client1\n"
    "19:45 13 ClientUnknown\n"
    "21:00 1 client1\n"
    "21:14 2 client1 9\n"
    "21:15 11 client1\n"
    "21:15\n"
    "9 1000 00:01\n";
    run_test_for_club_working_check("all_tests/input_tests/input25.txt", expected_output);
}
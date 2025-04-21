#include "csv_utils.hpp"
#include "run_data.hpp"
#include <iostream>
#include <fstream>

bool wants_to_save_to_csv(){
    std::cout << "Save data? (Y/N)";
    std::string input;
    std::getline(std::cin, input);
    return input == "Y";
}

bool file_exists(const std::string& file_name){
    struct stat buffer;
    return stat(file_name.c_str(), &buffer) == 0 && buffer.st_size > 0;
}

void create_run_data_csv_with_header(const std::string& file_name){
    std::ofstream file("output.csv");
    if (!file.is_open()){
        throw std::runtime_error("Failed to open file");
    }
    file << "date,run duration,km,minute km,mile,minute mile\n";
    file.close();
    return;
}

void save_to_csv(const RunData& data){
    if (!file_exists("output.csv")){
        create_run_data_csv_with_header("output.csv");
    }
    std::ofstream file("output.csv", std::ios::app);
    if (!file.is_open()){
        throw std::runtime_error("Failed to open file");
    }
    file << data.to_csv_row() << "\n";
    file.close();
    std::cout << "Successfully saved run data to CSV!" << std::endl;
}
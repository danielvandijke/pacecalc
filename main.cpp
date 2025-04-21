//Daniel van Dijke
//Program to calculate pace of a run

#include "time.hpp"
#include "date.hpp"
#include "run_data.hpp"
#include "csv_utils.hpp"
#include <iostream>

char get_distance_unit(){
    while (true){
        std::cout << "To select unit of distance type either 'm' or 'k':" << std::endl;
        std::string input;
        std::getline(std::cin, input);
        if (input == "m" || input == "k") {
            return input[0];
        }
        std::cout << "Invalid input" << std::endl;
    }
}

float get_distance_run(){
    std::string input;
    float distance = 0.0f;
    std::cout << "Please enter distance run: " << std::endl;
    std::getline(std::cin, input);
    try {
        distance = stof(input);
    } catch (...) {
        std::cout << "Invalid input. Defaulting to 0." << std::endl;
    }
    return distance;
}

std::string get_run_time_input(){
    std::string run_time;
    std::cout << "Enter time ran in form 'xx:xx'" << std::endl;
    std::cin >> run_time;
    std::cin.ignore();
    return run_time;
}

Time parse_run_time_input(const std::string& run_time){
    Time t{0, 0};
    size_t pos = run_time.find(":");
    if (pos != std::string::npos){
        t.minutes = stoi(run_time.substr(0, pos));
        t.seconds = stoi(run_time.substr(pos + 1));
    }
    return t;
}

int main() {
    Date date = get_date();
    char distance_unit = get_distance_unit();
    float distance = get_distance_run();
    std::string run_time_input = get_run_time_input();
    Time run_duration = parse_run_time_input(run_time_input);
    RunData run_data = RunData(date, distance, distance_unit, run_duration);
    std::cout << run_data.to_string() << std::endl;
    bool save_to_csv_selected = wants_to_save_to_csv();
    if (save_to_csv_selected){
        save_to_csv(run_data);
    }

    std::cout << "Program successfully ended";
    return 0;
}

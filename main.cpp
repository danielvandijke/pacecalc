//Daniel van Dijke
//Program to calculate pace of a run

#include "time.hpp"
#include "date.hpp"
#include "run_data.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <string>
#include <sstream>
#include <format>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

char get_distance_unit(){
    while (true){
        cout << "To select unit of distance type either 'm' or 'k':" << endl;
        string input;
        getline(cin, input);
        if (input == "m" || input == "k") {
            return input[0];
        }
        cout << "Invalid input" << endl;
    }
}

float get_distance_run(){
    string input;
    float distance = 0.0f;
    cout << "Please enter distance run: " << endl;
    getline(cin, input);
    try {
        distance = stof(input);
    } catch (...) {
        cout << "Invalid input. Defaulting to 0." << endl;
    }
    return distance;
}

string get_run_time_input(){
    string run_time;
    cout << "Enter time ran in form 'xx:xx'" << endl;
    cin >> run_time;
    cin.ignore();
    return run_time;
}

Time parse_run_time_input(const string& run_time){
    Time t{0, 0};
    size_t pos = run_time.find(":");
    if (pos != string::npos){
        t.minutes = stoi(run_time.substr(0, pos));
        t.seconds = stoi(run_time.substr(pos + 1));
    }
    return t;
}

bool wants_to_save_to_csv(){
    cout << "Save data? (Y/N)";
    string input;
    getline(cin, input);
    return input == "Y";
}

bool file_exists(const string& file_name){
    struct stat buffer;
    return stat(file_name.c_str(), &buffer) == 0 && buffer.st_size > 0;
}

void create_run_data_csv_with_header(const string& file_name){
    std::ofstream file("output.csv");
    if (!file.is_open()){
        throw runtime_error("Failed to open file");
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
        throw runtime_error("Failed to open file");
    }
    file << data.to_csv_row() << "\n";
    file.close();
    cout << "Successfully saved run data to CSV!" << endl;
}

int main() {
    Date date = get_date();
    char distance_unit = get_distance_unit();
    float distance = get_distance_run();
    string run_time_input = get_run_time_input();
    Time run_duration = parse_run_time_input(run_time_input);
    RunData run_data = RunData(date, distance, distance_unit, run_duration);
    cout << run_data.to_string() << endl;
    bool save_to_csv_selected = wants_to_save_to_csv();
    if (save_to_csv_selected){
        save_to_csv(run_data);
    }

    cout << "Program successfully ended";
    return 0;
}

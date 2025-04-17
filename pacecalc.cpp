//Daniel van Dijke
//Program to calculate pace of a run
// NEEDS FIXING! DEBUG THE ADDITION OF THE DATE STRUCT AND HOW THE INPUT IS PARSED FOR THIS


#include <iostream>
#include <string>
#include <iomanip>
#include <string>
#include <sstream>
#include <format>
#include <fstream>
#include <vector>
#include <chrono>

constexpr float MILES_TO_KM = 1.60934f;
constexpr float KM_TO_MILES = 0.621371f;

using namespace std;

struct Time {
    int minutes;
    int seconds;

    string to_verbose_string() const {
        return std::to_string(minutes) + " minutes and " + std::to_string(seconds) + " seconds";
    }
    string to_compact_string() const {
        return std::format("{}:{:02}", minutes, seconds);
    }
};

struct DistanceAndPace {
    float distance;
    Time pace;
};

struct Date {
    int year;
    int month;
    int day;

    string to_string() const {
        return std::format("{:02}/{:02}/{:02}", day, month, year % 100);
    }
};

Date parse_date(string input){
    Date date;
    date.day = stoi(input.substr(0, 2));
    date.month = stoi(input.substr(3,2));
    date.year = stoi(input.substr(6,2)) + 2000;
    return date;
}

Date get_date(){
    string input;
    while(true) {
        cout << "Enter date you ran in format 00/00/00" << endl;
        getline(cin, input);
        if (input.length() != 8 || input[2] != '/' || input[5] != '/') {
            cout << "Invalid date format" << endl;
        }
        else {
            return parse_date(input);
        }
    }
}

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

float time_in_decimal(int mins, int secs){
    return (float)mins + ((float)secs / 60);
}

float calculate_speed(Time time, float dist){
    return time_in_decimal(time.minutes, time.seconds) / dist;
}

Time speed_to_pace(const float& speed){
    Time pace = {};
    pace.minutes = static_cast<int>(speed);
    float remainder = (speed - static_cast<float>(pace.minutes)) * 60;
    pace.seconds = static_cast<int>(remainder);
    return pace;
}

Time calculate_pace(Time run_time, float dist){
    float speed = calculate_speed(run_time, dist);
    Time pace = speed_to_pace(speed);
    return pace;
}

class RunData {
    private: 
        Date date;
        Time run_duration;
        DistanceAndPace km_data;
        DistanceAndPace mile_data;

    public:
        RunData(Date date, float distance, const char distance_unit, Time run_duration)
        : date(date), run_duration(run_duration) {
            if (distance_unit == 'm'){
               distance *= MILES_TO_KM;
            }
            km_data.distance = distance;
            km_data.pace = calculate_pace(run_duration, km_data.distance);
            mile_data.distance = distance * KM_TO_MILES;
            mile_data.pace = calculate_pace(run_duration, mile_data.distance);
        }
        const DistanceAndPace& getKmData() const{ return km_data; }
        const DistanceAndPace& getMileData() const{ return mile_data; }

        string to_string() const {
            return std::format("On {}, you ran {:.2f} kilometers or {:.2f} miles in a time of {} at a pace of {} per kilometer or {} per mile.",
                date.to_string(), km_data.distance, mile_data.distance, run_duration.to_verbose_string(), km_data.pace.to_verbose_string(), mile_data.pace.to_verbose_string());
        }
        string to_csv_row() const {
            return std::format("{},{},{:.2f},{},{:.2f},{}", date.to_string(), run_duration.to_compact_string(), km_data.distance, km_data.pace.to_compact_string(), mile_data.distance, mile_data.pace.to_compact_string());
        }
};

bool wants_to_save_to_csv(){
    cout << "Save data? (Y/N)";
    string input;
    getline(cin, input);
    return input == "Y";
}

void save_to_csv(const RunData& data){
    std::ofstream file("output.csv");
    if (!file.is_open()){
        throw runtime_error("Failed to open file");
    }

    file << "date,run duration,km,minute km,mile,minute mile\n";
    file << data.to_csv_row();
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

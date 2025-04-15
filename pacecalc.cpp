//Daniel van Dijke
//Program to calculate pace of a run

#include <iostream>
#include <string>
#include <iomanip>
#include <string>
#include <sstream>
#include <format>
#include <fstream>
#include <vector>

constexpr float MILES_TO_KM = 1.60934f;
constexpr float KM_TO_MILES = 0.621371f;

using namespace std;

struct Time {
    int minutes;
    int seconds;

    string to_string() const {
        return std::to_string(minutes) + " minutes and " + std::to_string(seconds) + " seconds";
    }
};

struct DistanceAndPace {
    float distance;
    Time pace;
};

string get_date(){
    string date;
    while(true) {
        cout << "Enter date you ran in format 00/00/00" << endl;
        getline(cin, date);
        if (date.length() != 8 || date[2] != '/' || date[5] != '/') {
            cout << "Invalid date format" << endl;
        }
        else {
            return date;
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
        Time run_duration;
        DistanceAndPace km_data;
        DistanceAndPace mile_data;

    public:
        RunData(float distance, const char distance_unit, Time run_duration)
        : run_duration(run_duration) {
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
            return std::format("you ran {:.2f} kilometers or {:.2f} miles in a time of {} at a pace of {} per kilometer or {} per mile.",
                km_data.distance, mile_data.distance, run_duration.to_string(), km_data.pace.to_string(), mile_data.pace.to_string());
        }
};

void print_results(const string& date, const RunData& run_data){
    cout << "\nOn " << date << ", " << run_data.to_string();
}

int main()
{
    string date = get_date();
    char distance_unit = get_distance_unit();
    float distance = get_distance_run();
    string run_time_input = get_run_time_input();
    Time run_duration = parse_run_time_input(run_time_input);
    RunData run_data = RunData(distance, distance_unit, run_duration);
    print_results(date, run_data);

    std::vector<std::vector<std::string>> data = {
        {"Name", "Age", "City"},
        {"Alice", "30", "New York"},
        {"Bob", "25", "Los Angeles"},
        {"Charlie", "35", "Chicago"}
    };

    // Open a file to write to
    std::ofstream file("output.csv");

    if (file.is_open()) {
        // Loop through the data and write it to the file
        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i != row.size() - 1) {
                    file << ","; // Add a comma between elements
                }
            }
            file << "\n"; // Newline after each row
        }
        file.close(); // Close the file
        std::cout << "Data written to output.csv successfully!" << std::endl;
    } else {
        std::cout << "Error opening the file!" << std::endl;
    }
}

//Daniel van Dijke
//Program to calculate pace of a run

#include <iostream>
#include <string>
#include <iomanip>
#include <string>
#include <sstream>

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
    Time run_duration;
    DistanceAndPace km_data;
    DistanceAndPace mile_data;

    public:
        RunData(float distance, char distance_unit, Time run_duration)
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
            stringstream result;
            result << "you ran " << fixed << setprecision(2) << km_data.distance << " kilometers or " 
            << fixed << setprecision(2) << mile_data.distance << " miles " 
            << "in a time of " << run_duration.to_string() 
            << " at a pace of " << km_data.pace.to_string() << " per kilometer or " 
            << mile_data.pace.to_string() << " per mile.";
            return result.str();
        }
};

void print_results(string date, RunData& run_data){
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
}

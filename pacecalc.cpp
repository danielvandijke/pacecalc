//Daniel van Dijke
//Program to calculate pace of a run

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <format>
#include <iomanip>
#include <string>

constexpr float MILES_TO_KM = 1.60934f;
constexpr float KM_TO_MILES = 0.621371f;

using namespace std;

struct Time {
    int minutes;
    int seconds;
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
    return "";
}

char get_distance_unit(){
    while (true){
        cout << "To select unit of distance type either 'm' or 'k':" << endl;
        char input = getchar();
        if (input == 'm'){
            return 'm';
        }
        if (input == 'k'){
            return 'k';
        }
        cout << "Invalid input" << endl;
    }
}

float get_distance_run(){
    float distance;
    cout << "Please enter distance run: " << endl;
    cin >> distance;
    return distance;
}

string get_run_time_input(){
    string run_time;
    cout << "Enter time ran in form 'xx:xx'" << endl;
    cin >> run_time;
    return run_time;
}

void string_to_minutes_and_seconds(const string& run_time, int& mins, int& secs){
    size_t pos = run_time.find(":");
    if (pos != string::npos){
        mins = stoi(run_time.substr(0, pos));
        secs = stoi(run_time.substr(pos + 1));
    }
}

float calculate_time_run(int mins, int secs){
    return (float)mins + ((float)secs / 60);
}

float calculate_pace(Time time_run, float dist){
    return calculate_time_run(time_run.minutes, time_run.seconds) / dist;
}

void float_to_minutes_and_seconds(const float& pace, int& pace_mins, int& pace_secs){
    pace_mins = (int)pace;
    float remainder = (pace - pace_mins) * 60;
    pace_secs = (int)remainder;
}

void convert_distance_and_pace(char distance_unit, float input_distance, float pace, Time input_pace, DistanceAndPace& km_result, DistanceAndPace& mile_result){
    if (distance_unit == 'k'){
        km_result.distance = input_distance;
        km_result.pace.minutes = input_pace.minutes;
        km_result.pace.seconds = input_pace.seconds;
        mile_result.distance = KM_TO_MILES * input_distance;
        float mile_pace = MILES_TO_KM * pace;
        float_to_minutes_and_seconds(mile_pace, mile_result.pace.minutes, mile_result.pace.seconds);
    }
    else {
        mile_result.distance = input_distance;
        mile_result.pace.minutes = input_pace.minutes;
        mile_result.pace.seconds = input_pace.seconds;
        km_result.distance = MILES_TO_KM * input_distance;
        float km_pace = KM_TO_MILES * pace;
        float_to_minutes_and_seconds(km_pace, km_result.pace.minutes, km_result.pace.seconds);
    }
}

void print_results(string date, Time time_run, DistanceAndPace& km_data, DistanceAndPace& mile_data){
    cout << "\nOn " << date << ",\nyou ran " << fixed << setprecision(2) << km_data.distance << " kilometers or " << fixed << setprecision(2) << mile_data.distance << " miles in a time of " << time_run.minutes << " minutes and " << time_run.seconds << " seconds at a pace of " 
    << km_data.pace.minutes << " minutes and " << km_data.pace.seconds << " seconds per kilometer or " << mile_data.pace.minutes << " minutes and " << mile_data.pace.seconds << " seconds per mile." << endl;
}

int main(int argc, char **argv)
{
    string date = get_date();
    char distance_unit = get_distance_unit();
    float dist = get_distance_run();
    string run_time_input = get_run_time_input();
    Time time_run{0, 0};
    string_to_minutes_and_seconds(run_time_input, time_run.minutes, time_run.seconds);
    float pace = calculate_pace(time_run, dist);
    int pace_mins = 0, pace_secs = 0;
    float_to_minutes_and_seconds(pace, pace_mins, pace_secs);

    DistanceAndPace km_data, mile_data;
    Time input_pace = {pace_mins, pace_secs};
    convert_distance_and_pace(distance_unit, dist, pace, input_pace, km_data, mile_data);

    print_results(date, time_run, km_data, mile_data);
}
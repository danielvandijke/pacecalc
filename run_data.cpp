#include "run_data.hpp"
#include "time.hpp"
#include "date.hpp"
#include <format>

constexpr float MILES_TO_KM = 1.60934f;
constexpr float KM_TO_MILES = 0.621371f;

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

RunData::RunData(Date date, float distance, const char distance_unit, Time run_duration)
: date(date), run_duration(run_duration) {
    if (distance_unit == 'm'){
        distance *= MILES_TO_KM;
    }
    km_data.distance = distance;
    km_data.pace = calculate_pace(run_duration, km_data.distance);
    mile_data.distance = distance * KM_TO_MILES;
    mile_data.pace = calculate_pace(run_duration, mile_data.distance);
}

const DistanceAndPace& RunData::getKmData() const{ return km_data; }
const DistanceAndPace& RunData::getMileData() const{ return mile_data; }

std::string RunData::to_string() const {
    return std::format("On {}, you ran {:.2f} kilometers or {:.2f} miles in a time of {} at a pace of {} per kilometer or {} per mile.",
        date.to_string(), km_data.distance, mile_data.distance, run_duration.to_verbose_string(), km_data.pace.to_verbose_string(), mile_data.pace.to_verbose_string());
}
std::string RunData::to_csv_row() const {
    return std::format("{},{},{:.2f},{},{:.2f},{}", date.to_string(), run_duration.to_compact_string(), km_data.distance, km_data.pace.to_compact_string(), mile_data.distance, mile_data.pace.to_compact_string());
}
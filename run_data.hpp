#pragma once
#include "time.hpp"
#include "date.hpp"
#include <string>


struct DistanceAndPace {
    float distance;
    Time pace;
};

class RunData {
    private: 
        Date date;
        Time run_duration;
        DistanceAndPace km_data;
        DistanceAndPace mile_data;

    public:
        RunData(Date date, float distance, const char distance_unit, Time run_duration);
        const DistanceAndPace& getKmData() const;
        const DistanceAndPace& getMileData() const;

        std::string to_string() const;
        std::string to_csv_row() const;
};


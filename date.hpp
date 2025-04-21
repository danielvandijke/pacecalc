#pragma once
#include <string>

struct Date {
    int year;
    int month;
    int day;

    std::string to_string() const;
};

Date parse_date(std::string input);
Date get_date();

#pragma once
#include <string>

struct Time {
    int minutes;
    int seconds;

    std::string to_verbose_string() const;
    std::string to_compact_string() const;
};
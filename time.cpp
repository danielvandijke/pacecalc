#include "time.hpp"
#include <format>

std::string Time::to_verbose_string() const {
    return std::to_string(minutes) + " minutes and " + std::to_string(seconds) + " seconds";
}

std::string Time::to_compact_string() const {
    return std::format("{}:{:02}", minutes, seconds);
}
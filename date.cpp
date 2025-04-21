#include "date.hpp"
#include <iostream>
#include <format>

std::string Date::to_string() const {
    return std::format("{:02}/{:02}/{:02}", day, month, year % 100);
}

Date parse_date(std::string input){
    Date date;
    date.day = std::stoi(input.substr(0, 2));
    date.month = std::stoi(input.substr(3,2));
    date.year = std::stoi(input.substr(6,2)) + 2000;
    return date;
}

Date get_date(){
    std::string input;
    while(true) {
        std::cout << "Enter date you ran in format 00/00/00" << std::endl;
        std::getline(std::cin, input);
        if (input.length() != 8 || input[2] != '/' || input[5] != '/') {
            std::cout << "Invalid date format" << std::endl;
        }
        else {
            return parse_date(input);
        }
    }
}
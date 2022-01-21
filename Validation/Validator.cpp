//
// Created by HarcioGG on 4/6/2021.
//

#include <iostream>
#include "Validator.h"

bool Validator::performAddValidation(const std::string &title, const std::string &description, const std::string &dateAndTime, const std::string &link) {
    std::string errorString;
    if(title.empty() || description.empty() || dateAndTime.empty() || link.empty())
        errorString += "Invalid input data! Don't input empty strings!\n";
    if(link.substr(0, 3) != "www")
        errorString += "Invalid input data! A link should start with 'www.'\n";
///============================================ Validate date and time ================================================
    std::string dateAndTimeFake = dateAndTime;
    int day, month, year,hour, minute;
    std::string dayString, monthString, yearString, hourString, minuteString;
    std::string date;
    std::string time;
    std::string::iterator it;
    ///create the date and time
    for(it = dateAndTimeFake.begin(); it != dateAndTimeFake.end(); it++)
        if(*it != ' ')
            date.push_back(*it);
        else{ it++; break; }
    while(it != dateAndTimeFake.end())
    {
        time.push_back(*it);
        it++;
    }

    ///create the day
    for(it = date.begin(); it != date.end(); it++)
        if(*it != '.')
            dayString.push_back(*it);
        else{ it++; break; }
    try {
        day = std::stoi(dayString);
        if(day<0 || day>30)
            errorString += "Validation error! Invalid day input!\n";
    } catch (...) {
        errorString += "Validation error! Invalid day input!\n";
    }

    ///create the month
    for(it = it; it != date.end(); it++)
        if(*it != '.')
            monthString.push_back(*it);
        else{ it++; break; }
    try {
        month = std::stoi(monthString);
        if(month<0 || month>12)
            errorString += "Invalid month input!\n";
    } catch (...) {
        errorString += "Validation error! Invalid month input!\n";
    }

    ///create year
    for(it = it; it != date.end(); it++)
        if(*it != '.')
            yearString.push_back(*it);
        else{ it++; break; }
    try {
        year = std::stoi(yearString);
        if(year<=0)
            errorString += "Invalid year input!\n";
    } catch (...) {
        errorString += "Validation error! Invalid year input!\n";
    }

    ///create hour
    for(it = time.begin(); it != time.end(); it++)
        if(*it != ':')
            hourString.push_back(*it);
        else{ it++; break; }
    try {
        hour = std::stoi(hourString);
        if(hour<0 || hour>24)
            errorString += "Invalid hour input!\n";
    } catch (...) {
        errorString += "Validation error! Invalid hour input!\n";
    }

    ///create minute
    for(it = it; it != time.end(); it++)
        if(*it != ' ')
            minuteString.push_back(*it);
    try {
        minute = std::stoi(minuteString);
        if(minute<0 || minute>60)
            errorString += "Invalid minute input!\n";
    } catch (...) {
        errorString += "Validation error! Invalid minute input!\n";
    }
    if(errorString.length())
        throw ValidationException(errorString);
    return true;
}

bool Validator::performUpdateValidation(const std::string &title, const std::string &description,
                                        const std::string &dateAndTime, const std::string &link) {
    std::string errorString;
    if(!link.empty())
        if(link.substr(0, 3) != "www")
            errorString += "Invalid input data! A link should start with 'www.'\n";
///============================================ Validate date and time ================================================
    if(!dateAndTime.empty()) {
        std::string dateAndTimeFake = dateAndTime;
        int day, month, year,hour, minute;
        std::string dayString, monthString, yearString, hourString, minuteString;
        std::string date;
        std::string time;
        std::string::iterator it;
        ///create the date and time
        for(it = dateAndTimeFake.begin(); it != dateAndTimeFake.end(); it++)
            if(*it != ' ')
                date.push_back(*it);
            else{ it++; break; }
        while(it != dateAndTimeFake.end())
        {
            time.push_back(*it);
            it++;
        }

        ///create the day
        for(it = date.begin(); it != date.end(); it++)
            if(*it != '.')
                dayString.push_back(*it);
            else{ it++; break; }
        try {
            day = std::stoi(dayString);
            if(day<0 || day>30)
                errorString += "Validation error! Invalid day input!\n";
        } catch (...) {
            errorString += "Validation error! Invalid day input!\n";
        }

        ///create the month
        for(it = it; it != date.end(); it++)
            if(*it != '.')
                monthString.push_back(*it);
            else{ it++; break; }
        try {
            month = std::stoi(monthString);
            if(month<0 || month>12)
                errorString += "Invalid month input!\n";
        } catch (...) {
            errorString += "Validation error! Invalid month input!\n";
        }

        ///create year
        for(it = it; it != date.end(); it++)
            if(*it != '.')
                yearString.push_back(*it);
            else{ it++; break; }
        try {
            year = std::stoi(yearString);
            if(year<=0)
                errorString += "Invalid year input!\n";
        } catch (...) {
            errorString += "Validation error! Invalid year input!\n";
        }

        ///create hour
        for(it = time.begin(); it != time.end(); it++)
            if(*it != ':')
                hourString.push_back(*it);
            else{ it++; break; }
        try {
            hour = std::stoi(hourString);
            if(hour<0 || hour>24)
                errorString += "Invalid hour input!\n";
        } catch (...) {
            errorString += "Validation error! Invalid hour input!\n";
        }

        ///create minute
        for(it = it; it != time.end(); it++)
            if(*it != ' ')
                minuteString.push_back(*it);
        try {
            minute = std::stoi(minuteString);
            if(minute<0 || minute>60)
                errorString += "Invalid minute input!\n";
        } catch (...) {
            errorString += "Validation error! Invalid minute input!\n";
        }
        if(errorString.length())
            throw ValidationException(errorString);
    }
    return true;
}


std::ostream &operator<<(std::ostream &out, const ValidationException &ex) {
    out<<ex.msg;
    return out;
}

#pragma once

#include <iomanip>
#include <ostream>
#include <istream>

class Date {
private:
    unsigned year;
    unsigned month;
    unsigned day;
public:
    Date() : year(0), month(0), day(0) {}

    Date(unsigned int year, unsigned int month, unsigned int day) : year(year), month(month), day(day) {}

    unsigned int getYear() const {
        return year;
    }

    void setYear(unsigned int year) {
        this->year = year;
    }

    unsigned int getMonth() const {
        return month;
    }

    void setMonth(unsigned int month) {
        if (month && (month <= 12)) this->month = month;
    }

    unsigned int getDay() const {
        return day;
    }

    void setDay(unsigned int day) {
        if (day && (day <= 31)) this->day = day;
    }

    bool operator==(const Date &rhs) const {
        return year == rhs.year &&
               month == rhs.month &&
               day == rhs.day;
    }

    bool operator!=(const Date &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Date &rhs) const {
        if (year < rhs.year)
            return true;
        if (rhs.year < year)
            return false;
        if (month < rhs.month)
            return true;
        if (rhs.month < month)
            return false;
        return day < rhs.day;
    }

    bool operator>(const Date &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Date &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Date &rhs) const {
        return !(*this < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Date &date) {
        os << date.year << " "
           << date.month << " "
           << date.day << std::endl;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Date &date) {
        is >> date.year
           >> date.month
           >> date.day;
        return is;
    }

    std::string getStringRep() const {
        std::string s = std::to_string(year) + "/";
        if (month < 10) s += "0";
        s += std::to_string(month) + "/";
        if (day < 10) s += "0";
        return s + std::to_string(day);
    }

};

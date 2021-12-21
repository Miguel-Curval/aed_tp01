#pragma once

#include "Date.h"
#include "Time.h"

class DateTime {
private:
    Date date;
    Time time;
public:
    DateTime() : date(), time() {}

    DateTime(const Date &date, const Time &time) : date(date), time(time) {}

    DateTime(const unsigned year, const unsigned month, const unsigned day,
             const Time &time) : date(Date(year, month, day)), time(time) {}

    DateTime(const Date &date,
             const unsigned hour, const unsigned minute) : date(date), time(Time(hour, minute)) {}

    DateTime(const unsigned year, const unsigned month, const unsigned day,
             const unsigned hour, const unsigned minute) : date(Date(year, month, day)), time(Time(hour, minute)) {}

    const Date &getDate() const {
        return date;
    }

    void setDate(const Date &date) {
        this->date = date;
    }

    const Time &getTime() const {
        return time;
    }

    void setTime(const Time &time) {
        this->time = time;
    }

    bool operator==(const DateTime &rhs) const {
        return date == rhs.date &&
               time == rhs.time;
    }

    bool operator!=(const DateTime &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const DateTime &rhs) const {
        if (date < rhs.date)
            return true;
        if (rhs.date < date)
            return false;
        return time < rhs.time;
    }

    bool operator>(const DateTime &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const DateTime &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const DateTime &rhs) const {
        return !(*this < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const DateTime &dateTime) {
        os << dateTime.date << dateTime.time;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, DateTime &dateTime) {
        is >> dateTime.date >> dateTime.time;
        return is;
    }

    bool matches(const Date &rhs) const {
        return date == rhs;
    }

    bool matches(const Time &rhs) const {
        return time == rhs;
    }

    std::string getStringRep() const {
        return date.getStringRep() + "-" + time.getStringRep();
    }

};

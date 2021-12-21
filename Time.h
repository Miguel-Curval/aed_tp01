#pragma once

#include <iomanip>
#include <ostream>
#include <istream>

class Time {
private:
    unsigned hour;
    unsigned minute;
public:
    Time() : hour(0), minute(0) {}

    Time(unsigned int hour, unsigned int minute) : hour(hour), minute(minute) {}

    unsigned int getHour() const {
        return hour;
    }

    void setHour(unsigned int hour) {
        if (hour < 24) this->hour = hour;
    }

    unsigned int getMinute() const {
        return minute;
    }

    void setMinute(unsigned int minute) {
        if (minute < 60) this->minute = minute;
    }

    bool operator==(const Time &rhs) const {
        return hour == rhs.hour &&
               minute == rhs.minute;
    }

    bool operator!=(const Time &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Time &rhs) const {
        if (hour < rhs.hour)
            return true;
        if (rhs.hour < hour)
            return false;
        return minute < rhs.minute;
    }

    bool operator>(const Time &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Time &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Time &rhs) const {
        return !(*this < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Time &time) {
        os << time.hour << " "
           << time.minute << std::endl;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Time &time) {
        is >> time.hour
           >> time.minute;
        return is;
    }

    std::string getStringRep() const {
        std::string s;
        if (hour < 10) s += "0";
        s += std::to_string(hour) + "-";
        if (minute < 10) s += "0";
        return s + std::to_string(minute);
    }

};

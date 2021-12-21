#pragma once

#include <string>
#include <ostream>
#include <utility>
#include <vector>

#include "Time.h"

class Transportation {
private:
    std::string type;
    unsigned distance;
    Time schedule;
public:
    Transportation() : type(), distance(0), schedule() {}

    Transportation(std::string type, unsigned distance, const Time &schedule) : type(std::move(type)),
                                                                                       distance(distance),
                                                                                       schedule(schedule) {}

    bool operator<(const Transportation &rhs) const {
        if (schedule < rhs.schedule)
            return true;
        if (rhs.schedule < schedule)
            return false;
        if (distance < rhs.distance)
            return true;
        if (rhs.distance < distance)
            return false;
        return type < rhs.type;
    }

    bool operator==(const Transportation &rhs) const {
        return type == rhs.type &&
               distance == rhs.distance &&
               schedule == rhs.schedule;
    }

    const std::string & getType() const {
        return type;
    }

    unsigned int getDistance() const {
        return distance;
    }

    const Time & getSchedule() const {
        return schedule;
    }

    friend std::ostream &operator<<(std::ostream &os, const Transportation &transportation) {
        os << transportation.type << "\n"
           << transportation.distance << "\n"
           << transportation.schedule;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Transportation &transportation) {
        is >> transportation.type
           >> transportation.distance
           >> transportation.schedule;
        return is;
    }

    std::string getStringRep() const {
        return type + ", " + std::to_string(distance) + "m, " + schedule.getStringRep();
    }

    static std::vector<std::string> getHeaderElements() {
        return {"Type", "Distance", "Time"};
    }

};

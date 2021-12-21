#pragma once

#include <deque>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <ostream>

#include "Flight.h"

class Service;
class DateTime;

class Aircraft {
private:
    std::string registration;
    std::string type;
    unsigned capacity;
    std::string location;
    std::deque<Flight> flightPlan;
    std::queue<Service> services;
    std::vector<Service> cleaningDone;
    std::vector<Service> maintenanceDone;

public:
    Aircraft() : registration(), type(), capacity(0), location(),
                 flightPlan(), services(), cleaningDone(), maintenanceDone() {}

    Aircraft(std::string registration, std::string type, unsigned int capacity,
             std::string location) : registration(std::move(registration)),
                                            type(std::move(type)),
                                            capacity(capacity),
                                            location(std::move(location)) {}

    std::deque<Flight> &getFlightPlan() {
        return flightPlan;
    }

    DateTime getWhenLastCleaning() const;

    DateTime getWhenLastMaintenance() const;

    const std::string &getRegistration() const {
        return registration;
    }

    const std::string &getType() const {
        return type;
    }

    unsigned int getCapacity() const {
        return capacity;
    }

    const std::string &getLocation() const {
        return location;
    }

    friend std::ostream &operator<<(std::ostream &os, const Aircraft &aircraft);

    friend std::istream &operator>>(std::istream &is, Aircraft &aircraft);

    DateTime getDeparture() const;

    void addFlight(const Flight &flight);

    void clearFlightPlan();

    void fly();

    void cancelLastFlight();

    void scheduleService(const Service & service);

    void dispatchService();

    bool hasFlights() const;

    std::string getStringRep() const {
        return registration + ", " + type + ", " + std::to_string(capacity) + ", " + location + ", "
        + getDeparture().getStringRep() + ", "
        + getWhenLastCleaning().getStringRep() + ", " + getWhenLastMaintenance().getStringRep();
    }

    static std::vector<std::string> getHeaderElements() {
        return {"Registration", "Type", "Capacity", "Location",
                "Departure", "Last cleaned", "Last maintained"};
    }

};

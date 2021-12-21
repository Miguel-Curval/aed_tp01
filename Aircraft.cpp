#include "Aircraft.h"
#include "Service.h"

DateTime Aircraft::getWhenLastCleaning() const {
    if (cleaningDone.empty()) return DateTime();
    return cleaningDone.back().getDatetime();
}

DateTime Aircraft::getWhenLastMaintenance() const {
    if (maintenanceDone.empty()) return DateTime();
    return maintenanceDone.back().getDatetime();
}

std::ostream &operator<<(std::ostream &os, const Aircraft &aircraft) {
    os << aircraft.registration << "\n" << aircraft.type << "\n" << aircraft.capacity << "\n"
       << aircraft.location << "\n";
    os << aircraft.flightPlan.size() << "\n";
    for (const auto & f : aircraft.flightPlan) {
        os << f;
    }
    os << aircraft.services.size() << "\n";
    std::queue<Service> tmp_q = aircraft.services;
    while (!tmp_q.empty()) {
        const auto &s = tmp_q.front();
        os << s <<"\n";
        tmp_q.pop();
    }
    os << aircraft.cleaningDone.size() << "\n";
    for (const auto & s : aircraft.cleaningDone) {
        os << s << "\n";
    }
    os << aircraft.maintenanceDone.size() << "\n";
    for (const auto & s : aircraft.maintenanceDone) {
        os << s << "\n";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Aircraft &aircraft) {
    is >> aircraft.registration >> aircraft.type >> aircraft.capacity;
    std::getline(is >> std::ws, aircraft.location);
    int n;
    is >> n;
    for (int i = 0; i < n; ++i) {
        Flight f;
        is >> f;
        aircraft.flightPlan.push_back(f);
    }
    is >> n;
    for (int i = 0; i < n; ++i) {
        Service s;
        is >> s;
        aircraft.services.push(s);
    }
    is >> n;
    for (int i = 0; i < n; ++i) {
        Service s;
        is >> s;
        aircraft.cleaningDone.push_back(s);
    }
    is >> n;
    for (int i = 0; i < n; ++i) {
        Service s;
        is >> s;
        aircraft.maintenanceDone.push_back(s);
    }
    return is;
}

DateTime Aircraft::getDeparture() const {
    if (flightPlan.empty()) return DateTime();
    return flightPlan.front().getDeparture();
}

void Aircraft::addFlight(const Flight &flight) {
    if (flight.getOrigin().getName() == getLocation()) flightPlan.push_back(flight);
}

void Aircraft::cancelLastFlight() {
    if (!flightPlan.empty()) flightPlan.pop_back();
}

void Aircraft::fly() {
    if (!flightPlan.empty()) {
        location = flightPlan.front().getDestination().getName();
        flightPlan.pop_front();
    }
}

void Aircraft::clearFlightPlan() {
    flightPlan.clear();
}

void Aircraft::dispatchService() {
    if (!services.empty()) services.pop();
}

void Aircraft::scheduleService(const Service & service) {
    if (services.empty() || service.getDatetime() > services.back().getDatetime()) services.push(service);
}

bool Aircraft::hasFlights() const {
    return !flightPlan.empty();
}


#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "Aircraft.h"
#include "Passenger.h"
#include "Service.h"
#include "Transportation.h"

constexpr char GO_BACK[] = "0";

template <typename Iter>
void printListing(Iter it, Iter end) {
    std::cout << "\n@@@ ";
    auto header_elements = it->getHeaderElements();
    for (const auto & e : header_elements) {
        std::cout << e << " ";
    }
    std::cout << ":\n";
    for (; it!=end; ++it) {
        std::cout << it->getStringRep() << "\n";
    }
    std::cout << std::endl;
}

std::string prompt(const std::string &prompt) {
    std::cout << "\n" << prompt;
    std::string line;
    std::getline(std::cin >> std::ws, line);
    return line;
}

Passenger promptPassenger() {
    return {prompt("Full Name: "), prompt("Baggage (Y for yes)? ") == "Y"};
}

Date promptDate() {
    return {(unsigned) stoul(prompt("Year: ")),
            (unsigned) stoul(prompt("Month: ")),
            (unsigned) stoul(prompt("Day: "))};
}

Time promptTime() {
    return {(unsigned) stoul(prompt("Hour: ")),
            (unsigned) stoul(prompt("Minute: "))};
}

DateTime promptDateTime() {
    return {promptDate(), promptTime()};
}

Airport promptAirport() {
    return {prompt("Name: ")};
}

Flight promptFlight(unsigned capacity) {
    return {promptAirport(), promptAirport(), promptDateTime(), promptDateTime(), capacity};
}

Transportation promptTransportation() {
    return {prompt("Type (Metro, Train, Bus): "),
            (unsigned) stoul(prompt("Distance in meters:")),
            promptTime()};
}

std::map<unsigned, std::set<Passenger>> initializePassengers() {
    std::map<unsigned, std::set<Passenger>> flight_to_passengers;
    std::ifstream infile("passengers.txt");
    unsigned num_flights, num_passengers;
    infile >> num_flights;
    for (int i = 0; i < num_flights; ++i) {
        unsigned flight_num;
        infile >> flight_num;
        infile >> num_passengers;
        flight_to_passengers[flight_num] = std::set<Passenger>();
        for (int j = 0; j < num_passengers; ++j) {
            Passenger passenger;
            infile >> passenger;
            flight_to_passengers[flight_num].insert(passenger);

        }
    };
    return flight_to_passengers;
}

std::vector<Aircraft> initializeAircraft() {
    std::vector<Aircraft> aircraft;
    std::ifstream infile("aircraft.txt");
    infile >> Flight::count;
    unsigned num_aircraft;
    infile >> num_aircraft;
    for (int i = 0; i < num_aircraft; ++i) {
        Aircraft ac;
        aircraft.push_back(ac);
        infile >> aircraft.back();
    }
    return aircraft;
}

std::map<Airport, std::vector<Transportation>> initializeAirports() {
    std::map<Airport, std::vector<Transportation>> airports;
    std::ifstream infile("airports.txt");
    unsigned num_airports, num_transport;
    infile >> num_airports;
    for (int i = 0; i < num_airports; ++i) {
        Airport airport;
        infile >> airport >> num_transport;
        std::vector<Transportation> v;
        for (int j = 0; j < num_transport; ++j) {
            Transportation t;
            infile >> t;
            v.push_back(t);
        }
        airports.insert({airport, v});
    }
    return airports;
}

void listAirports(std::map<Airport, std::vector<Transportation>> & airports) {
    std::cout << "\n@@@ Name:\n";
    for (const auto & a : airports) {
        std::cout << a.first << "\n";
    }
    std::cout << "\n";
}

void sortAircraftDeparture(std::vector<Aircraft> & aircraft) {
    std::sort(aircraft.begin(), aircraft.end(), [](const Aircraft & a1, const Aircraft & a2) {
        if (!a2.hasFlights()) return true;
        if (!a1.hasFlights()) return false;
        return a1.getDeparture() < a2.getDeparture();
    });
}

void sortAircraft(std::vector<Aircraft> & aircraft) {
    auto byReg = [](const Aircraft & a1, const Aircraft & a2) { return a1.getRegistration() < a2.getRegistration(); };
    auto byType = [](const Aircraft & a1, const Aircraft & a2) { return a1.getType() < a2.getType(); };
    auto byCap = [](const Aircraft & a1, const Aircraft & a2) { return a1.getCapacity() < a2.getCapacity(); };
    auto byLoc = [](const Aircraft & a1, const Aircraft & a2) { return a1.getLocation() < a2.getLocation(); };
    auto byDep = [](const Aircraft & a1, const Aircraft & a2) {
        if (!a2.hasFlights()) return true;
        if (!a1.hasFlights()) return false;
        return a1.getDeparture() < a2.getDeparture();
    };
    auto byClean = [](const Aircraft & a1, const Aircraft & a2) {
        if (!a2.hasFlights()) return true;
        if (!a1.hasFlights()) return false;
        return a1.getWhenLastCleaning() < a2.getWhenLastCleaning();
    };
    auto byMaint = [](const Aircraft & a1, const Aircraft & a2) {
        if (!a2.hasFlights()) return true;
        if (!a1.hasFlights()) return false;
        return a1.getWhenLastMaintenance() < a2.getWhenLastMaintenance();
    };
    std::vector<std::function<bool(Aircraft&, Aircraft&)>> cmps{byReg, byType, byCap, byLoc, byDep, byClean, byMaint};
    std::string reply = prompt("1: Registration number.\n"
                               "2: Type of aircraft.\n"
                               "3: Maximum capacity.\n"
                               "4: Current Location.\n"
                               "5: Date of departure.\n"
                               "6: Last cleaned.\n"
                               "7: Last maintained.\n"
                               "0: This airline sucks!\n");
    if (reply == GO_BACK) return;
    if (reply.length() == 1) {
        unsigned idx = reply[0] - '1';
        if (idx >=0 && idx < 7) std::sort(aircraft.begin(), aircraft.end(), cmps[idx]);
    }
}

void manageTransportation(std::vector<Transportation> &tv) {
    auto byDist = [](const Transportation & t1, const Transportation & t2) { return t1.getDistance() < t2.getDistance(); };
    auto byTime = [](const Transportation & t1, const Transportation & t2) { return t1.getSchedule() < t2.getSchedule(); };
    auto byType = [](const Transportation & t1, const Transportation & t2) { return t1.getType() < t2.getType(); };
    std::vector<std::function<bool(Transportation&, Transportation&)>> cmps{byDist, byTime, byType};
    while (true) {
        printListing(tv.begin(), tv.end());
        std::string reply = prompt("1: Add new transportation.\n"
                                          "2: Remove transportation.\n"
                                          "3: Clear all."
                                          "4: Sort by distance.\n"
                                          "5: Sort by time schedule.\n"
                                          "6: Sort by transportation type.\n"
                                          "0: This airline sucks!\n");
        if (reply == GO_BACK) return;
        if (reply == "1" || reply == "2") {
            Transportation t = promptTransportation();
            if (reply == "1") tv.push_back(t);
            else if (reply == "2") tv.erase(std::find(tv.begin(), tv.end(), t));
        }
        else if (reply == "3") tv.clear();
        else if (reply == "4" || reply == "5" || reply == "6") std::sort(tv.begin(), tv.end(), cmps[reply[0] - '4']);
    }
}

void manageFlights(Aircraft & aircraft) {
    while (true) {
        printListing(aircraft.getFlightPlan().begin(), aircraft.getFlightPlan().end());
        std::string reply = prompt("1: Schedule flight.\n"
                                   "2: Cancel last flight.\n"
                                   "3: Clear flight plan.\n"
                                   "0: This airline sucks!\n");
        if (reply == GO_BACK) return;
        if (reply == "1") aircraft.addFlight(promptFlight(aircraft.getCapacity()));
        else if (reply == "2") aircraft.cancelLastFlight();
        else if (reply == "3") aircraft.clearFlightPlan();
    }
}

void manageServices(Aircraft & aircraft) {
    // TODO
}

void manageAircraft(std::vector<Aircraft> & aircraft) {
    while (true) {
        printListing(aircraft.begin(), aircraft.end());
        std::string reply = prompt("1: Add new aircraft.\n"
                                   "2: Manage flights.\n"
                                   "3: Manage flights.\n"
                                   "4: Remove aircraft.\n"
                                   "5: Sort.\n"
                                   "0: This airline sucks!\n");
        if (reply == GO_BACK) return;
        if (reply == "1" || reply == "2" || reply == "3" || reply == "4") {
            std::string registration = prompt("Registration number: ");
            auto it = std::find_if(aircraft.begin(), aircraft.end(), [&registration](const Aircraft & a) {
                return a.getRegistration() == registration;
            });
            if (reply == "1") {
                if (it == aircraft.end())
                    aircraft.emplace_back(registration,
                                          prompt("Type of aircraft: "),
                                          (unsigned) stoul(prompt("Maximum capacity: ")),
                                          prompt("Current location: "));
                else std::cout << "We already have that one registered.\n";
            } else if (it == aircraft.end()) std::cout << "We don't have that one registered.\n";
            else if (reply == "2") manageFlights(*it);
            else if (reply == "3") manageServices(*it);
            else aircraft.erase(it);
        } else if (reply == "4") sortAircraft(aircraft);
    }
}

void manageAirports(std::map<Airport, std::vector<Transportation>> & airports) {
    std::cout << "Here they are boss.\n";
    while (true) {
        listAirports(airports);
        std::string reply = prompt("1: Add new airport.\n"
                                          "2: Manage transportation.\n"
                                          "3: Remove airport.\n"
                                          "0: This airline sucks!\n");
        if (reply == GO_BACK) return;
        if (reply == "1" || reply == "2" || reply == "3") {
            Airport airport = promptAirport();
            const std::string & name = airport.getName();
            if (reply == "1") airports[name] = std::vector<Transportation>();
            else if (reply == "2") manageTransportation(airports[name]);
            else if (reply == "3") airports.erase(name);
        }
    }
}

void storeAircraft(std::vector<Aircraft> & aircraft) {
    std::ofstream outfile("aircraft.txt");
    outfile << Flight::count << "\n" << aircraft.size() << "\n";
    for (const auto & a : aircraft) {
        outfile << a;
    }
}

void storeAirports(std::map<Airport, std::vector<Transportation>> & airports) {
    std::ofstream outfile("airports.txt");
    outfile << airports.size() << "\n";
    for (const auto & p : airports) {
        outfile << p.first << p.second.size() << "\n";
        for (const auto & t : p.second) {
            outfile << t;
        }
    }
}

void storePassengers(std::map<unsigned, std::set<Passenger>> & flight_to_passengers) {
    std::ofstream outfile("passengers.txt");
    outfile << flight_to_passengers.size() << "\n";
    for (const auto & fp : flight_to_passengers) {
        outfile << fp.first << "\n" << fp.second.size() << "\n";
        for (const auto & p : fp.second) {
            outfile << p;
        }
    }
}

std::set<Passenger> flyNext(std::vector<Aircraft> & aircraft,
                            std::map<unsigned, std::set<Passenger>> & flight_to_passengers) {
    sortAircraftDeparture(aircraft);

    if (!aircraft.empty() && aircraft.front().hasFlights()) {
        unsigned num = aircraft.front().getFlightPlan().front().getNumber();
        aircraft.front().fly();
        return flight_to_passengers[num];
    }
    return {};
}

void terrorist() {
    // TODO
}

void management(std::vector<Aircraft> & aircraft, std::map<Airport, std::vector<Transportation>> & airports) {
    std::cout << "I am terribly sorry, I'm still new here.\n";
    while (true) {
        std::string reply = prompt("Can I help you with something boss?\n"
                                   "1: About our aircraft and flights...\n"
                                   "2: Remember that transportation map we had for each airport?\n"
                                   "0: This airline sucks!\n");
        if (reply == GO_BACK) {
            std::cout << "(Sigh... Should've studied computer science...)\n";
            return;
        }
        if (reply == "1") manageAircraft(aircraft);
        else if (reply == "2") manageAirports(airports);
    }
}

void embark(std::set<Passenger> passengers) {
    std::cout << "CCTV is right this way, we'll peep together.\n";
    // TODO

}

void bookFlight(std::vector<Aircraft> & aircraft,
                std::map<unsigned, std::set<Passenger>> & flight_to_passengers) {
    std::vector<Flight> flights;
    for (auto & ac : aircraft) {
        for (auto & f : ac.getFlightPlan()) {
            flights.push_back(f);
            if (flight_to_passengers.find(f.getNumber()) == flight_to_passengers.end())
                flight_to_passengers[f.getNumber()] = std::set<Passenger>();
        }
    }
    auto byNum = [](const Flight & f1, const Flight & f2) { return f1.getNumber() < f2.getNumber(); };
    auto byTime = [](const Flight & f1, const Flight & f2) { return f1.getDeparture() < f2.getDeparture(); };
    auto byOrig = [](const Flight & f1, const Flight & f2) { return f1.getOrigin() < f2.getOrigin(); };
    auto byDest = [](const Flight & f1, const Flight & f2) { return f1.getDestination() < f2.getDestination(); };
    std::vector<std::function<bool(Flight&, Flight&)>> cmps {byNum, byTime, byOrig, byDest};
    std::sort(flights.begin(), flights.end(), byTime);
    while (true) {
        printListing(flights.begin(), flights.end());
        std::string reply = prompt("1: Pick a flight.\n"
                                   "2: Sort by flight number.\n"
                                   "3: Sort by date of departure.\n"
                                   "4: Sort by origin.\n"
                                   "5: Sort by destination.\n"
                                   "0: This airline sucks!\n");
        if (reply == GO_BACK) {
            return;
        }
        if (reply == "1") {
            unsigned num = (unsigned) std::stoul(prompt("Flight Number: "));
            auto it = std::find_if(flights.begin(), flights.end(), [num](const Flight & f) {
                return f.getNumber() == num;
            });
            if (it == flights.end()) {
                std::cout << "Flight doesn't exist. Can't you read?\n";
                continue;
            }
            const auto & passengers = flight_to_passengers[num];
            printListing(passengers.begin(), passengers.end());
            if (it->hasSeats()) {
                unsigned tickets = (unsigned) std::stoul(prompt("How many tickets? "));
                for (auto & ac : aircraft) {
                    bool breaker = false;
                    for (auto & f : ac.getFlightPlan()) {
                        if (num == f.getNumber()) {
                            if (f.takeSeats(tickets)) {
                                it->takeSeats(tickets);
                                for (int i = 0; i < tickets; ++i) {
                                    flight_to_passengers[num].insert(promptPassenger());
                                }
                            }
                            breaker = true;
                            break;
                        }
                    }
                    if (breaker) break;
                }
            }
        }
        else if (reply == "2" || reply == "3" || reply == "4" || reply == "5") {
            std::sort(flights.begin(), flights.end(), cmps[reply[0] - '2']);
        }

    }
}

int main() {
    std::vector<Aircraft> aircraft = initializeAircraft();
    std::map<Airport, std::vector<Transportation>> airports = initializeAirports();
    std::map<unsigned, std::set<Passenger>> flight_to_passengers = initializePassengers();
    while (true) {
        std::string reply = prompt("Welcome to Vailonge Valongo Airlines. What can I help you with?\n"
                                   "1: I'd like to book a flight.\n"
                                   "2: Good day. I have taken a moderate to high dose of both LSD and psilocybin at the same time. As of now, I derive immense spiritual value from the idea of watching the embarking process of individuals unknown to me. Therefore, I would be immensely grateful if you could let me watch how it all unfolds through remote video footage.\n"
                                   "3: I happen to be your supervisor.\n"
                                   "0: This airline sucks!\n");
        if (reply == GO_BACK) {
            storeAircraft(aircraft);
            storeAirports(airports);
            storePassengers(flight_to_passengers);
            return 0;
        }
        if (reply == "1") bookFlight(aircraft, flight_to_passengers);
        else if (reply == "2") embark(flyNext(aircraft, flight_to_passengers));
        else if (reply == "3") management(aircraft, airports);
        else if (reply == "Cyka.") terrorist();
    }
}

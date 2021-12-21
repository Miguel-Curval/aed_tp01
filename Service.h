#pragma once

#include <string>
#include <ostream>
#include <utility>

#include "DateTime.h"

class Service {
private:
    std::string type;
    std::string responsible;
    DateTime datetime;
public:
    Service() : type(), responsible(), datetime() {}

    Service(std::string type, std::string responsible, const DateTime &datetime) : type(std::move(type)),
                                                                                   responsible(std::move(responsible)),
                                                                                   datetime(datetime) {}

    const std::string &getType() const {
        return type;
    }

    const DateTime &getDatetime() const {
        return datetime;
    }

    const std::string &getResponsible() const {
        return responsible;
    }

    friend std::ostream &operator<<(std::ostream &os, const Service &service) {
        os << service.type << "\n" << service.responsible << "\n" << service.datetime;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Service &service) {
        is >> service.type;
        std::getline(is >> std::ws, service.responsible);
        is >> service.datetime;
        return is;
    }

    std::string getStringRep() const {
        return type + ", " + responsible + ", " + datetime.getStringRep();
    }

};

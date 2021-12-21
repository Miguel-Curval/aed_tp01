#pragma once

#include <string>
#include <utility>

class Luggage {
private:
    std::string ownerName;
public:
    Luggage(std::string ownerName) : ownerName(std::move(ownerName)) {}

    const std::string &getOwnerName() const {
        return ownerName;
    }
};

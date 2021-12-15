#pragma once

class Date;
class Staff;

enum class Type {
    cleaning,
    maintenance
};

class Service {
    Type type;
    Date date;
    Staff responsible;

};

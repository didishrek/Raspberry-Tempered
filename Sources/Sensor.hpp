//
// Created by adrien on 24/01/17.
//

#ifndef RASPTEMP_SENSOR_HPP
#define RASPTEMP_SENSOR_HPP

#include <ostream>

class Sensor {
private:
    int number;
    float value;
    int type; // TEMPERED_SENSOR_TYPE_NONE or TEMPERED_SENSOR_TYPE_TEMPERATURE or TEMPERED_SENSOR_TYPE_HUMIDITY
    std::string type_string;

public:
    Sensor(int number, float value, int type) : number(number), value(value), type(type) {
        if (type == TEMPERED_SENSOR_TYPE_NONE)
            type_string = "TYPE_NONE";
        else if (type == TEMPERED_SENSOR_TYPE_TEMPERATURE)
            type_string = "TYPE_TEMPERATURE";
        else if (type == TEMPERED_SENSOR_TYPE_HUMIDITY)
            type_string = "TYPE_HUMIDITY";
    }

    int getNumber() const {
        return number;
    }

    float getValue() const {
        return value;
    }

    int getType() const {
        return type;
    }

    friend ostream &operator<<(ostream &os, const Sensor &sensor) {

        os << "number: " << sensor.number << " value: " << sensor.value << " type: " << sensor.type_string;
        return os;
    }

};

#endif //RASPTEMP_SENSOR_HPP

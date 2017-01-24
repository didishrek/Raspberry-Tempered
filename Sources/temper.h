//
// Created by adrien on 19/12/16.
//

#ifndef RASPTEMP_TEMPER_H
#define RASPTEMP_TEMPER_H

#include <cstdlib>
#include <tempered.h>
#include <vector>
#include "TemperDevice.hpp"
#include "Sensor.hpp"

class Temper {
private:
    std::vector<TemperDevice*> all_devices;
    char *error;
    struct tempered_device_list *list_devices_enumerated;



    void initialization();
    void finalization();

    void update_devices_list();

    Sensor read_device_sensor(tempered_device *, int);
public:
    Temper();
    virtual ~Temper();;

    void enumerate_devices();

    std::vector<Sensor> get_sensors_values(TemperDevice &);

    const vector<TemperDevice *> &getAll_devices() const;
};


#endif //RASPTEMP_TEMPER_H

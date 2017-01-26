//
// Created by adrien on 19/12/16.
//


#include <iostream>
#include "temper.h"


//privates
void Temper::initialization() {
    if (!tempered_init(&this->error))
        throw TemperException("Initialization failed", this->error);
}

void Temper::finalization(){
    if (!tempered_exit(&this->error))
        throw TemperException("Finalization failed", this->error);
}

void Temper::update_devices_list() {
    try {
        if (this->list_devices_enumerated != NULL){
            //tempered_free_device_list(this->list_devices_enumerated);
            this->list_devices_enumerated = NULL;
        }
        this->list_devices_enumerated = tempered_enumerate( &this->error );
        if ( list_devices_enumerated == NULL )
            std::cerr << this->error << std::endl;
        else
        {
            struct tempered_device_list *dev;
            if (!all_devices.empty())
                all_devices.clear();
            for ( dev = list_devices_enumerated ; dev != NULL ; dev = dev->next )
            {
                all_devices.push_back(new TemperDevice(dev->path, dev->type_name, dev->vendor_id, dev->product_id,
                                                       dev->interface_number, dev));
            }
        }
    } catch (TemperException e){
        std::cerr << e.what() << std::endl;
    }
}


Sensor Temper::read_device_sensor(tempered_device * device, int sensor) {
    int type = tempered_get_sensor_type( device, sensor );
    if ( type == TEMPERED_SENSOR_TYPE_NONE )
    {
        return Sensor(sensor, 0.0, TEMPERED_SENSOR_TYPE_NONE);
    }
    if ( type & TEMPERED_SENSOR_TYPE_TEMPERATURE )
    {
        float tempC;
        if ( tempered_get_temperature( device, sensor, &tempC ) )
        {
            return Sensor(sensor, tempC, TEMPERED_SENSOR_TYPE_TEMPERATURE);
        }
        else
        {
            error = tempered_error( device );
            throw TemperException("read temperature failed :", error);
        }
    }
    if ( type & TEMPERED_SENSOR_TYPE_HUMIDITY )
    {
        float rel_hum;
        if ( tempered_get_humidity( device, sensor, &rel_hum ) )
        {
            return Sensor(sensor, rel_hum, TEMPERED_SENSOR_TYPE_HUMIDITY);
        }
        else
        {
            error = tempered_error( device );
            throw TemperException("read humidity failed :", error);
        }
    }
    return Sensor(sensor, 0.0, TEMPERED_SENSOR_TYPE_NONE);
}

//public
Temper::Temper() {
    this->error = NULL;
    try {
        initialization();
    } catch (TemperException e){
        std::cerr << e.what() << std::endl;
    }
}

Temper::~Temper() {
    free(this->error);
    try {
        tempered_free_device_list(this->list_devices_enumerated);
        finalization();
    } catch (TemperException e){
        std::cerr << e.what() << std::endl;
    }
}

void Temper::enumerate_devices() {
    update_devices_list();

    for (std::vector<TemperDevice*>::iterator it = all_devices.begin() ; it != all_devices.end(); ++it)
        std::cout << **it << std::endl;

}

std::vector<Sensor> Temper::get_sensors_values(TemperDevice & temperDevice) {
    std::vector<Sensor> sensors_vector;

    try {
        temperDevice.open_device();

        if (!tempered_read_sensors(temperDevice.getDev())) {
            error = tempered_error(temperDevice.getDev());
            throw TemperException("Failed to read the sensors:", error);
        } else {
            int sensor, sensors = tempered_get_sensor_count(temperDevice.getDev());
            for (sensor = 0; sensor < sensors; sensor++) {
                sensors_vector.push_back(read_device_sensor(temperDevice.getDev(), sensor));
            }
        }
        temperDevice.close_device();
    } catch (TemperException e){
        std::cerr << e.what() << std::endl;
    }

    return sensors_vector;
}

const vector<TemperDevice *> &Temper::getAll_devices() const {
    return all_devices;
}














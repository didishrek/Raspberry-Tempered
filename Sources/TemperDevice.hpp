//
// Created by adrien on 19/12/16.
//

#ifndef RASPTEMP_TEMPERDEVICE_HPP
#define RASPTEMP_TEMPERDEVICE_HPP

#include <iostream>
#include "TemperException.hpp"

using namespace std;

class TemperDevice {
private:
    string path;
    string type_name;
    unsigned short vendor_idl;
    unsigned short product_id;
    int interface_number;
    tempered_device_list *device;
    bool open;
    tempered_device *dev;
    char *error;

public:
    TemperDevice(const char *path, const char *type_name, unsigned short vendor_idl, unsigned short product_id,
                 int interface_number, tempered_device_list *device)
            : path(path), type_name(type_name), vendor_idl(vendor_idl), product_id(product_id), interface_number(interface_number),
              device(device) {
        open = false;
        dev = NULL;
        error = NULL;
    }

    virtual ~TemperDevice() {
        free(error);
    }

    const string &getPath() const {
        return path;
    }

    const string &getType_name() const {
        return type_name;
    }

    unsigned short getVendor_idl() const {
        return vendor_idl;
    }

    unsigned short getProduct_id() const {
        return product_id;
    }

    int getInterface_number() const {
        return interface_number;
    }

    tempered_device_list *getDevice() const {
        return device;
    }

    bool isOpen() const {
        return open;
    }

    tempered_device *getDev() const {
        return dev;
    }

    void open_device(){
        if (!open){
            dev = tempered_open( device, &error );
            if (dev == NULL){
                throw TemperException("Error when opening device", error);
            }
            open = true;
        }
    }

    void close_device(){
        tempered_close(dev);
        open = false;
    }

    friend ostream &operator<<(ostream &os, const TemperDevice &device) {
        os << "path: " << device.path << " type_name: " << device.type_name << " vendor_idl: " << device.vendor_idl
           << " product_id: " << device.product_id << " interface_number: " << device.interface_number;
        return os;
    }

};


#endif //RASPTEMP_TEMPERDEVICE_HPP

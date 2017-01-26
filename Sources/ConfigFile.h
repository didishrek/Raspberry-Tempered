//
// Created by adrien on 24/01/17.
//

#ifndef RASPTEMP_CONFIGFILE_H
#define RASPTEMP_CONFIGFILE_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>

class ConfigFile {
private:
    std::string path_file;
    libconfig::Config cfg;

    std::string prod_login;
    std::string prod_password;
    std::string prod_address;
    std::string prod_schemas;

    std::string dev_login;
    std::string dev_password;
    std::string dev_address;
    std::string dev_schemas;

    std::string location;
public:

    ConfigFile();

    void open_and_read();

    const std::string &getProd_login() const;

    const std::string &getProd_password() const;

    const std::string &getProd_address() const;

    const std::string &getProd_schemas() const;

    const std::string &getDev_login() const;

    const std::string &getDev_password() const;

    const std::string &getDev_address() const;

    const std::string &getDev_schemas() const;

    const std::string &getLocation() const;

    friend std::ostream &operator<<(std::ostream &os, const ConfigFile &file);

};


#endif //RASPTEMP_CONFIGFILE_H

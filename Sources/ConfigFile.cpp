//
// Created by adrien on 24/01/17.
//

#include "ConfigFile.h"

void ConfigFile::open_and_read() {
    try
    {
        cfg.readFile(path_file.c_str());
        const libconfig::Setting & root = cfg.getRoot();
        const libconfig::Setting & sql = root["sql"];
        const libconfig::Setting & prod = sql["prod"];
        const libconfig::Setting & dev = sql["dev"];

        prod.lookupValue("login", prod_login);
        prod.lookupValue("password", prod_password);
        prod.lookupValue("address", prod_address);
        prod.lookupValue("schemas", prod_schemas);

        dev.lookupValue("login", dev_login);
        dev.lookupValue("password", dev_password);
        dev.lookupValue("address", dev_address);
        dev.lookupValue("schemas", dev_schemas);

        sql.lookupValue("location", location);
    }
    catch(const libconfig::FileIOException &fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
    }
    catch(const libconfig::ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
    }
}

const std::string &ConfigFile::getProd_login() const {
    return prod_login;
}

const std::string &ConfigFile::getProd_password() const {
    return prod_password;
}

const std::string &ConfigFile::getProd_address() const {
    return prod_address;
}

const std::string &ConfigFile::getProd_schemas() const {
    return prod_schemas;
}

const std::string &ConfigFile::getDev_login() const {
    return dev_login;
}

const std::string &ConfigFile::getDev_password() const {
    return dev_password;
}

const std::string &ConfigFile::getDev_address() const {
    return dev_address;
}

const std::string &ConfigFile::getDev_schemas() const {
    return dev_schemas;
}

const std::string &ConfigFile::getLocation() const {
    return location;
}

std::ostream &operator<<(std::ostream &os, const ConfigFile &file) {
    os << "prod_login: " << file.prod_login << " prod_password: " << file.prod_password << " prod_address: "
       << file.prod_address << " prod_schemas: " << file.prod_schemas << " dev_login: " << file.dev_login
       << " dev_password: " << file.dev_password << " dev_address: " << file.dev_address << " dev_schemas: "
       << file.dev_schemas << " location: " << file.location;
    return os;
}

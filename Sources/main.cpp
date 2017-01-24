//
// Created by adrien on 19/12/16.
//

#include <iostream>
#include "temper.h"
#include "ConfigFile.h"
#include "MysqlTemper.h"

int main(void) {
    ConfigFile cfg;
    Temper temper;

    cfg.open_and_read();
    std::cout << cfg << std::endl;

    MysqlTemper mysqlTemper(cfg.getDev_login().c_str(), cfg.getDev_password().c_str(), cfg.getDev_address().c_str(), cfg.getDev_schemas().c_str());

    temper.enumerate_devices();



    for (int i =0; i < temper.getAll_devices().size(); ++i){

        if (temper.getAll_devices()[i]->getProduct_id() == 29697 && temper.getAll_devices()[i]->getVendor_idl() == 3141){
            std::vector<Sensor> sensors = temper.get_sensors_values(* temper.getAll_devices()[i]);
            std::vector<float> temps;

            for (std::vector<Sensor>::iterator it = sensors.begin() ; it != sensors.end(); ++it){
                std::cout << *it << std::endl;
                temps.push_back((it)->getValue());
            }
            mysqlTemper.add_temp(cfg.getLocation().c_str(), temps[0], temps[1]);
        }
    }

    return 0;
}
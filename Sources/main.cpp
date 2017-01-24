//
// Created by adrien on 19/12/16.
//

#include <iostream>
#include "temper.h"

int main(void) {
    Temper temper;
    temper.enumerate_devices();

    for (int i =0; i < temper.getAll_devices().size(); ++i){

        if (temper.getAll_devices()[i]->getProduct_id() == 29697 && temper.getAll_devices()[i]->getVendor_idl() == 3141){
            std::vector<Sensor> sensors = temper.get_sensors_values(* temper.getAll_devices()[i]);

            for (std::vector<Sensor>::iterator it = sensors.begin() ; it != sensors.end(); ++it)
                std::cout << *it << std::endl;
        }
    }

    return 0;
}
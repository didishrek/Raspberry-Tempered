//
// Created by adrien on 24/01/17.
//

#ifndef RASPTEMP_MYSQLTEMPER_H
#define RASPTEMP_MYSQLTEMPER_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;

class MysqlTemper {
private :
    const char * login;
    const char * password;
    const char * address;
    const char * schemas;


public :
    void configure(const char *login, const char *password, const char *address, const char *schemas);

    void add_temp(const char * position, float temp1, float temp2);
};


#endif //RASPTEMP_MYSQLTEMPER_H

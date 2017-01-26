//
// Created by adrien on 24/01/17.
//

#include "MysqlTemper.h"


void MysqlTemper::add_temp(const char *location, float temp1, float temp2) {
    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::PreparedStatement *pstmt;

        driver = get_driver_instance();
        con = driver->connect(address, login, password);
        con->setSchema(schemas);

        std::string stmt_string = "INSERT INTO temperature(Location, Temp1, Temp2) VALUES (?, ?, ?)";
        pstmt = con->prepareStatement(stmt_string);


        pstmt->setString(1, location);
        pstmt->setDouble(2, temp1);
        pstmt->setDouble(3, temp2);
        pstmt->executeUpdate();

        delete pstmt;
        delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void MysqlTemper::configure(const char *login, const char *password, const char *address, const char *schemas) {
    this->login = login;
    this->password = password;
    this->address = address;
    this->schemas = schemas;
}


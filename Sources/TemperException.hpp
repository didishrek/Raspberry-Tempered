//
// Created by adrien on 19/12/16.
//

#ifndef RASPTEMP_TEMPEREXCEPTION_HPP
#define RASPTEMP_TEMPEREXCEPTION_HPP

#include <iostream>
#include <exception>
#include <sstream>

class TemperException : public std::exception {
public:
    TemperException(const char *message, const char *error) {
        std::ostringstream oss;
        oss << message << " : " << error;
        this->msg = oss.str();
    }

    virtual ~TemperException() throw(){

    }

    virtual const char * what() const throw()
    {
        return this->msg.c_str();
    }

private:
    std::string msg;
};


#endif //RASPTEMP_TEMPEREXCEPTION_HPP

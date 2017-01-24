cmake_minimum_required(VERSION 3.5)
project(RaspTemp)

set(CMAKE_CXX_STANDARD 11)

find_library(TEMPERED tempered /usr/local/lib)
find_library(TEMPEREDUTIL tempered-util /usr/local/lib)
find_library(HIDAPI_LIB NAMES hidapi-hidraw hidapi-libusb
        PATHS /usr/local/lib
        )


set(SOURCE_FILES Sources/main.cpp Sources/temper.cpp Sources/temper.h Sources/TemperException.hpp Sources/TemperDevice.hpp Sources/Sensor.hpp)
add_executable(RaspTemp ${SOURCE_FILES})
target_link_libraries(RaspTemp ${TEMPERED} ${TEMPEREDUTIL} ${HIDAPI_LIB})
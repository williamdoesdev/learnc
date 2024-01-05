#include <iostream>
#include "config.h"

void info(const char* message) {
    if (LOG_LEVEL > LOG_LEVEL_INFO) return;

    std::cout << "[INFO]: " << message << std::endl;
}

void warning(const char* message) {
    if (LOG_LEVEL > LOG_LEVEL_WARNING) return;

    std::cout << "[WARNING]: " << message << std::endl;     
}

void error(const char* message) {
    if (LOG_LEVEL > LOG_LEVEL_ERROR) return;

    std::cout << "[ERROR]: " << message << std::endl;      
}
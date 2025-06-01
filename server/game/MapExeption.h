#ifndef MAP_EXCEPTION_H_
#define MAP_EXCEPTION_H_

#include <stdexcept>
#include <string>
class MapException: public std::runtime_error {
public:
    explicit MapException(const std::string& message):
            std::runtime_error("Excepcion del Map: " + message) {}
};
#endif  // MAP_EXCEPTION_H_

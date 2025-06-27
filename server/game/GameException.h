#ifndef GAME_EXCEPTION_H_
#define GAME_EXCEPTION_H_
#include <stdexcept>
#include <string>
class GameException: public std::runtime_error {
public:
    explicit GameException(const std::string& message):
            std::runtime_error("Excepcion del game: " + message) {}
};
#endif  // GAME_EXCEPTION_H_

#ifndef QUIT_GAME_EXCEPTION_H
#define QUIT_GAME_EXCEPTION_H

#pragma once
#include <stdexcept>
#include <string>

class QuitGameException: public std::runtime_error {
public:
    explicit QuitGameException(const std::string& message): std::runtime_error(message) {}
};

class GameFinishExeption: public std::runtime_error {
public:
    explicit GameFinishExeption(const std::string& message): std::runtime_error(message) {}
};

#endif  // !QUIT_GAME_EXCEPTION_H

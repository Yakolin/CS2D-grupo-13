#ifndef CLIENT_CLOSED_EXCEPTION_H
#define CLIENT_CLOSED_EXCEPTION_H

#pragma once
#include <stdexcept>
#include <string>

class ConnectionClosedException: public std::runtime_error {
public:
    explicit ConnectionClosedException(const std::string& message): std::runtime_error(message) {}
};

#endif  // CLIENT_CLOSED_EXCEPTION_H
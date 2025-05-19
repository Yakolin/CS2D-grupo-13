#ifndef WRONG_SENDER_EXCEPTION_H
#define WRONG_SENDER_EXCEPTION_H

#pragma once
#include <stdexcept>
#include <string>

class WrongSenderException: public std::runtime_error {
public:
    explicit WrongSenderException(const std::string& message): std::runtime_error(message) {}
};

#endif
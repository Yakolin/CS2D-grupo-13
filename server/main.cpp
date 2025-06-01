#include <iostream>
#include <sstream>
#include <string>

#include "server.h"


#define PORT_INDEX 1
#define N_ARGS 2
#define ERROR 1
#define SUCCESS 0

int main(int argc, const char** argv) {
    try {
        if (argc != N_ARGS) {
            std::ostringstream oss;
            oss << "Bad program call. Expected " << N_ARGS - 1 << " args, <port> \n";
            throw std::runtime_error(oss.str());
        } else {
            Server server(argv[PORT_INDEX]);
            server.run();
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return ERROR;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        return ERROR;
    }
    return SUCCESS;
}

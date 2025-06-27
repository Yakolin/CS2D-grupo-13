#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::string p = argv[1];
        return 1;
    }
    return 0;
}

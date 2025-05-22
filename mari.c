#include <iostream>
#include <cstdint>
#include <cstring>

int main() {
    uint8_t bytes1[] = {0xC3, 0xF5, 0x48, 0x40};
    float x;
    std::memcpy(&x, bytes1, sizeof(float));
    std::cout << x << std::endl; 
    //-----------------------------------------------
    float y = 3.14f;

    uint8_t bytes[sizeof(float)];

    std::memcpy(bytes, &y, sizeof(float));

    for (size_t i = 0; i < sizeof(float); i++) {
        std::printf("0x%02X ", bytes[i]);
    }
    std::cout << std::endl;
}

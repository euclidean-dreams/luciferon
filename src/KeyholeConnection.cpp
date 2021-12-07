#include "KeyholeConnection.h"

namespace luciferon {

KeyholeConnection::KeyholeConnection()
        : sendBuffer{} {
    sendBuffer.resize(PACKET_SIZE, 0);
    spiHandle = spiOpen(0, BAUDRATE, 0);
    if (spiHandle < 0) {
        spdlog::get(LOGGER_NAME)->info("failed to open spi connection, error code: {}", spiHandle);
    }
}

void KeyholeConnection::send(const unsigned char *data) {
    std::memcpy(sendBuffer.data(), data, PACKET_SIZE);
    auto spiResult = spiWrite(spiHandle, sendBuffer.data(), PACKET_SIZE);
    if (spiResult != PACKET_SIZE) {
        spdlog::get(LOGGER_NAME)->info("spi write failed, error code: {}", spiResult);
    }
}

}

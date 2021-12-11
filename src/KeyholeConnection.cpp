#include "KeyholeConnection.h"

namespace luciferon {

KeyholeConnection::KeyholeConnection(bool useMainSpi)
        : sendBuffer{} {
    sendBuffer.resize(PACKET_SIZE, 0);
    int spiFlags;
    if (useMainSpi) {
        spiFlags = 0;
    } else {
        spiFlags = 256;
    }
    spiHandle = spiOpen(0, BAUDRATE, spiFlags);
    if (spiHandle < 0) {
        LOGGER->error("failed to open spi connection, error code: {}", spiHandle);
    }
}

void KeyholeConnection::send(const unsigned char *data) {
    std::memcpy(sendBuffer.data(), data, PACKET_SIZE);
    auto spiResult = spiWrite(spiHandle, sendBuffer.data(), PACKET_SIZE);
    if (spiResult != PACKET_SIZE) {
        LOGGER->error("spi write failed, error code: {}", spiResult);
    }
}

}

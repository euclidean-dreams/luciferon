#include "Luciferon.h"

namespace luciferon {

Luciferon::Luciferon(std::unique_ptr<impresarioUtils::NetworkSocket> cosmographerSocket)
        : cosmographerSocket{move(cosmographerSocket)},
          keyholeConnection{std::make_unique<KeyholeConnection>()} {

}

void Luciferon::activate() {
    auto parcel = cosmographerSocket->receiveParcel();
    auto glimpse = impresarioUtils::Unwrap::Glimpse(*parcel);
    std::vector<unsigned char> sendBuffer;
    sendBuffer.reserve(PACKET_SIZE);

    // header
    sendBuffer.push_back(glimpse->brightness());
    sendBuffer.push_back(0);
    sendBuffer.push_back(0);
    sendBuffer.push_back(0);

    // led data
    for (int i = 0; i < glimpse->colors()->size(); i++) {
        auto color = glimpse->colors()->Get(i);
        sendBuffer.push_back(color->red());
        sendBuffer.push_back(color->green());
        sendBuffer.push_back(color->blue());
    }
    keyholeConnection->send(sendBuffer.data());
}

uint64_t Luciferon::getTickInterval() {
    return 0;
}

bool Luciferon::finished() {
    return false;
}

}

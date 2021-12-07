#include "Luciferon.h"

namespace luciferon {

Luciferon::Luciferon(std::unique_ptr<impresarioUtils::NetworkSocket> cosmographerSocket)
        : cosmographerSocket{move(cosmographerSocket)},
          keyholeConnection{std::make_unique<KeyholeConnection>()} {

}

void Luciferon::activate() {
    auto serializedData = cosmographerSocket->receiveSerializedData();
    auto luminary = ImpresarioSerialization::GetLuminary(serializedData->getBuffer());
    std::vector<unsigned char> sendBuffer;
    sendBuffer.reserve(luminary->glimpse()->size() * 3);
    for (int i = 0; i < luminary->glimpse()->size(); i++) {
        auto color = luminary->glimpse()->Get(i);
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

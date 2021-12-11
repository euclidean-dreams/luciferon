#include "Luciferon.h"

namespace luciferon {

Luciferon::Luciferon(std::unique_ptr<impresarioUtils::NetworkSocket> cosmographerSocket,
                     std::shared_ptr<impresarioUtils::Arbiter<const SendBuffer>> mainArbiter,
                     std::shared_ptr<impresarioUtils::Arbiter<const SendBuffer>> auxArbiter)
        : cosmographerSocket{move(cosmographerSocket)},
          mainArbiter{move(mainArbiter)},
          auxArbiter{move(auxArbiter)},
          identity{0} {

}

void Luciferon::activate() {
    auto parcel = cosmographerSocket->receiveParcel();
    auto glimpse = impresarioUtils::Unwrap::Glimpse(*parcel);
    auto mainSendBuffer = std::make_unique<SendBuffer>(PACKET_SIZE, glimpse->brightness(), identity);
    auto auxSendBuffer = std::make_unique<SendBuffer>(PACKET_SIZE, glimpse->brightness(), identity);

    // led data
    for (int i = 0; i < glimpse->colors()->size(); i++) {
        auto color = glimpse->colors()->Get(i);
        mainSendBuffer->add(color->red());
        mainSendBuffer->add(color->green());
        mainSendBuffer->add(color->blue());
    }
    mainArbiter->give(move(mainSendBuffer));

    // led data
    for (int i = 0; i < glimpse->colors()->size(); i++) {
        auto color = glimpse->colors()->Get(i);
        auxSendBuffer->add(color->red());
        auxSendBuffer->add(color->green());
        auxSendBuffer->add(color->blue());
    }
    auxArbiter->give(move(auxSendBuffer));

    identity++;
}

uint64_t Luciferon::getTickInterval() {
    return 0;
}

bool Luciferon::finished() {
    return false;
}

}

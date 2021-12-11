#include "KeyholeCommunicator.h"

namespace luciferon {

KeyholeCommunicator::KeyholeCommunicator(bool useMainSpi,
                                         std::shared_ptr<impresarioUtils::Arbiter<const SendBuffer>> arbiter)
        : keyholeConnection{useMainSpi},
          arbiter{move(arbiter)},
          identity{0} {

}

void KeyholeCommunicator::activate() {
    auto sendBuffer = arbiter->take();
    if (sendBuffer != nullptr) {
        auto sendBufferIdentity = sendBuffer->getIdentity();
        if (sendBufferIdentity > identity) {
            identity = sendBufferIdentity;
            keyholeConnection.send(sendBuffer->getData());
        }
    }
}

uint64_t KeyholeCommunicator::getTickInterval() {
    return 500;
}

bool KeyholeCommunicator::finished() {
    return false;
}
}

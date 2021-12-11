#ifndef LUCIFERON_KEYHOLECOMMUNICATOR_H
#define LUCIFERON_KEYHOLECOMMUNICATOR_H

#include <ImpresarioUtils.h>
#include "KeyholeConnection.h"
#include "SendBuffer.h"

namespace luciferon {

class KeyholeCommunicator : public impresarioUtils::Circulable {
private:
    KeyholeConnection keyholeConnection;
    std::shared_ptr<impresarioUtils::Arbiter<const SendBuffer>> arbiter;
    uint64_t identity;

public:
    explicit KeyholeCommunicator(bool useMainSpi, std::shared_ptr<impresarioUtils::Arbiter<const SendBuffer>> arbiter);

    void activate() override;

    uint64_t getTickInterval() override;

    bool finished() override;

};

}

#endif //LUCIFERON_KEYHOLECOMMUNICATOR_H

#ifndef LUCIFERON_LUCIFERON_H
#define LUCIFERON_LUCIFERON_H

#include <spdlog/spdlog.h>
#include <ImpresarioUtils.h>
#include "Constants.h"
#include "SendBuffer.h"

namespace luciferon {

class Luciferon : public impresarioUtils::Circulable {
private:
    std::unique_ptr<impresarioUtils::NetworkSocket> cosmographerSocket;
    std::shared_ptr<impresarioUtils::Arbiter<const SendBuffer>> mainArbiter;
    std::shared_ptr<impresarioUtils::Arbiter<const SendBuffer>> auxArbiter;
    uint64_t identity;

public:
    explicit Luciferon(std::unique_ptr<impresarioUtils::NetworkSocket> cosmographerSocket,
                       std::shared_ptr<impresarioUtils::Arbiter<const SendBuffer>> mainArbiter,
                       std::shared_ptr<impresarioUtils::Arbiter<const SendBuffer>> auxArbiter);

    void activate() override;

    uint64_t getTickInterval() override;

    bool finished() override;
};

}

#endif //LUCIFERON_LUCIFERON_H

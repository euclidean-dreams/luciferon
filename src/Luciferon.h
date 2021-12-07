#ifndef LUCIFERON_LUCIFERON_H
#define LUCIFERON_LUCIFERON_H

#include <spdlog/spdlog.h>
#include <ImpresarioUtils.h>
#include "Constants.h"

#include "KeyholeConnection.h"

namespace luciferon {

class Luciferon : public impresarioUtils::Circulable {
private:
    std::unique_ptr<impresarioUtils::NetworkSocket> cosmographerSocket;
    std::unique_ptr<KeyholeConnection> keyholeConnection;

public:
    explicit Luciferon(std::unique_ptr<impresarioUtils::NetworkSocket> cosmographerSocket);

    void activate() override;

    uint64_t getTickInterval() override;

    bool finished() override;
};

}

#endif //LUCIFERON_LUCIFERON_H

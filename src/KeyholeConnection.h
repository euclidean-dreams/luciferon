#ifndef LUCIFERON_KEYHOLECONNECTION_H
#define LUCIFERON_KEYHOLECONNECTION_H

#include <vector>
#include <pigpio.h>
#include <cstring>
#include <spdlog/spdlog.h>
#include "Constants.h"

namespace luciferon {

class KeyholeConnection {
private:
    std::vector<char> sendBuffer;
    int spiHandle;

public:
    KeyholeConnection();

    void send(const unsigned char *data);
};

}

#endif //LUCIFERON_KEYHOLECONNECTION_H

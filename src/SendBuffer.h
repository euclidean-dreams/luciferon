#ifndef LUCIFERON_SENDBUFFER_H
#define LUCIFERON_SENDBUFFER_H

#include <cstdint>
#include <vector>
#include <cstdlib>

namespace luciferon {

class SendBuffer {
private:
    uint64_t identity;
    std::vector<unsigned char> buffer;

public:
    explicit SendBuffer(uint size, int brightness, uint64_t identity);

    void add(unsigned char point);

    uint64_t getIdentity() const;

    const unsigned char *getData() const;
};

}

#endif //LUCIFERON_SENDBUFFER_H

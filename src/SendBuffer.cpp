#include "SendBuffer.h"

namespace luciferon {

SendBuffer::SendBuffer(uint size, int brightness, uint64_t identity)
        : identity{identity},
          buffer{} {
    buffer.reserve(size);
    buffer.push_back(brightness);
    buffer.push_back(0);
    buffer.push_back(0);
    buffer.push_back(0);
}

void SendBuffer::add(unsigned char point) {
    buffer.push_back(point);
}

uint64_t SendBuffer::getIdentity() const {
    return identity;
}

const unsigned char *SendBuffer::getData() const {
    return buffer.data();
}

}

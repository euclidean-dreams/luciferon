#include <pigpio.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <zmq.hpp>
#include <ImpresarioUtils.h>
#include "Constants.h"
#include "Luciferon.h"
#include "SendBuffer.h"
#include "KeyholeCommunicator.h"

void initializePigpio() {
    auto pigpioInitializationResult = gpioInitialise();
    if (pigpioInitializationResult < 0) {
        LOGGER->error("failed to initialize pigpio - failed with error code: {}", pigpioInitializationResult);
    }
}

int main() {
    std::string configFilePath = "./config.yml";
    impresarioUtils::Bootstrapper bootstrapper(configFilePath, 1);

    initializePigpio();
    auto mainArbiter = std::make_shared<impresarioUtils::Arbiter<const luciferon::SendBuffer>>();
    auto auxArbiter = std::make_shared<impresarioUtils::Arbiter<const luciferon::SendBuffer>>();
    auto cosmographerSocket = std::make_unique<impresarioUtils::NetworkSocket>(
            bootstrapper.getZmqContext(),
            COSMOGRAPHER_ENDPOINT,
            zmq::socket_type::sub,
            false
    );
    cosmographerSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::glimpse);
    auto luciferonInstance = std::make_unique<luciferon::Luciferon>(move(cosmographerSocket), mainArbiter, auxArbiter);
    auto luciferonThread = impresarioUtils::Circlet::begin(move(luciferonInstance));

    auto mainKeyholeCommunicator = std::make_unique<luciferon::KeyholeCommunicator>(0, move(mainArbiter));
    auto mainKeyholeCommunicatorThread = impresarioUtils::Circlet::begin(move(mainKeyholeCommunicator));

    auto auxKeyholeCommunicator = std::make_unique<luciferon::KeyholeCommunicator>(1, move(auxArbiter));
    auto auxKeyholeCommunicatorThread = impresarioUtils::Circlet::begin(move(auxKeyholeCommunicator));

    luciferonThread->join();
    mainKeyholeCommunicatorThread->join();
    auxKeyholeCommunicatorThread->join();
}

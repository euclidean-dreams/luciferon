#include <pigpio.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <zmq.hpp>
#include <ImpresarioUtils.h>
#include "Constants.h"
#include "Luciferon.h"

void initializeLogger() {
    spdlog::stdout_color_mt(LOGGER_NAME);
}

void initializePigpio() {
    auto pigpioInitializationResult = gpioInitialise();
    if (pigpioInitializationResult < 0) {
        spdlog::get(LOGGER_NAME)->info(
                "failed to initialize pigpio - failed with error code: {}", pigpioInitializationResult
        );
    }
}

std::unique_ptr<std::thread> initializeLuciferon(zmq::context_t &context) {
    auto cosmographerSocket = std::make_unique<impresarioUtils::NetworkSocket>(
            context,
            COSMOGRAPHER_ENDPOINT,
            zmq::socket_type::sub,
            false
    );
    cosmographerSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::glimpse);
    auto luciferonInstance = std::make_unique<luciferon::Luciferon>(move(cosmographerSocket));
    auto luciferonThread = impresarioUtils::Circlet::begin(move(luciferonInstance));
    return luciferonThread;
}

int main() {
    zmq::context_t context(1);
    initializeLogger();
    initializePigpio();
    auto luciferonThread = initializeLuciferon(context);
    luciferonThread->join();
}

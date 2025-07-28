#include "Framework.h"

Framework::Framework() {
    event_manager = std::make_shared<EventManager>();
    scheduler = std::make_shared<RealTimeScheduler>(event_manager);
}

void Framework::start() {
    // Launch EventManager on Core 1
    multicore_launch_core1([]() {
        auto em = std::make_shared<EventManager>();
        em->run();
    });

    // Queue system initialization
    event_manager->queue_event({EventType::SYSTEM_INIT, 0, {} });

    // Run RealTimeScheduler on Core 0
    scheduler->run();
}

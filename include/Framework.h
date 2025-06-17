#ifndef PICO_CORE_FRAMEWORK_H__
#define PICO_CORE_FRAMEWORK_H__

#include "pico/multicore.h"
#include "EventManager.h"
#include "RealTimeScheduler.h"

#include <memory>

// Abstract Framework class
class Framework {
protected:
    std::shared_ptr<EventManager> event_manager;
    std::shared_ptr<RealTimeScheduler> scheduler;

    virtual void system_init() = 0; // Must be overridden by user

public:
    Framework() {
        event_manager = std::make_shared<EventManager>();
        scheduler = std::make_shared<RealTimeScheduler>(event_manager);
    }

    void start() {
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
};

#endif // PICO_CORE_FRAMEWORK_H__


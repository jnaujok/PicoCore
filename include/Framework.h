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
    Framework();

    void start();
};

#endif // PICO_CORE_FRAMEWORK_H__


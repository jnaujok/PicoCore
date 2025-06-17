#ifndef PICO_CORE_REAL_TIME_PLUGIN_H__
#define PICO_CORE_REAL_TIME_PLUGIN_H__

#include "Event.h"

// Abstract real-time plugin interface
class RealTimePlugin {
public:
    virtual ~RealTimePlugin() = default;
    virtual void execute() = 0; // Called by scheduler
    virtual void push_event(const Event& event) = 0; // Push event to event manager
};

#endif // PICO_CORE_REAL_TIME_PLUGIN_H__

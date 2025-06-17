#ifndef PICO_CORE_EVENT_H__
#define PICO_CORE_EVENT_H__

#include <vector>

// Forward Definition
class IEventHandler;

// Event type enumeration
enum class EventType {
    SYSTEM_INIT,
    SYSTEM_SHUTDOWN,
    SYSTEM_SLEEP,
    SYSTEM_ERROR,
    DEVICE_RESPONSE,
    DEVICE_NOTIFICATION,
    REAL_TIME_EVENT,
    USER_EVENT,
    NOTIFICATION,
};

// Event structure
struct Event {
    EventType type;
    uint8_t device_address;
    std::vector<uint8_t> data;
};

#endif // PICO_CORE_EVENT_H__

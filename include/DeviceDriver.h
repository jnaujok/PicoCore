#ifndef __PICO_CORE_DEVICE_DRIVER_H__
#define __PICO_CORE_DEVICE_DRIVER_H__

#include <vector>
#include "Event.h"

// Abstract driver interface for devices
class DeviceDriver {
public:
    virtual ~DeviceDriver() = default;
    virtual void handle_event(const Event& event) = 0; // Process incoming events
    virtual void send_command(const std::vector<uint8_t>& command) = 0; // Send command to device
    virtual void queue_notification(const std::vector<uint8_t>& data) = 0; // Queue notification for user code
};

#endif // __PICO_CORE_DEVICE_DRIVER_H__

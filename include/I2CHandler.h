#ifndef PICO_CORE_I2CHANDLER_H__
#define PICO_CORE_I2CHANDLER_H__

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/sync.h>
#include <map>
#include "InterfaceHandler.h"
#include "DeviceDriver.h"

// I2C DMA Handler (placeholder implementation)
class I2CHandler : public InterfaceHandler {
    std::map<uint8_t, std::shared_ptr<DeviceDriver>> devices;
    // Assume DMA channel and I2C peripheral are configured
public:
    virtual ~I2CHandler(void) override {}

    void register_device(uint8_t address, std::shared_ptr<DeviceDriver> driver) override {
        devices[address] = driver;
    }

    void handle_dma_complete() override {
        // Read data from I2C, create event
        std::vector<uint8_t> data; // Placeholder: read from I2C
        Event event{EventType::DEVICE_RESPONSE, 0, data};
        for (auto& [addr, driver] : devices) {
            event.device_address = addr;
            driver->handle_event(event);
        }
    }
};

#endif // PICO_CORE_I2CHANDLER_H__

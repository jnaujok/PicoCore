#ifndef PICO_CORE_INTERFACE_HANDLER_H__
#define PICO_CORE_INTERFACE_HANDLER_H__

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/sync.h>
#include <memory>
#include "DeviceDriver.h"

// Abstract handler interface for I2C/SPI DMA
class InterfaceHandler {
protected:
    mutex_t queue_mutex;
public:
    InterfaceHandler() { mutex_init(&queue_mutex); }
    virtual ~InterfaceHandler() = default;
    virtual void register_device(uint8_t address, std::shared_ptr<DeviceDriver> driver) = 0;
    virtual void handle_dma_complete() = 0; // DMA completion callback
};

#endif // PICO_CORE_INTERFACE_HANDLER_H__



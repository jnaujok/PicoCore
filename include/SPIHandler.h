#ifndef PICO_CORE_SPI_HANDLER_H__
#define PICO_CORE_SPI_HANDLER_H__

#include "InterfaceHandler.h"

// SPI DMA Handler (similar structure, placeholder)
class SPIHandler : public InterfaceHandler {
    // Similar to I2CHandler
public:
    void register_device(uint8_t address, std::shared_ptr<DeviceDriver> driver) override {}
    void handle_dma_complete() override {}
};

#endif // PICO_CORE_SPI_HANDLER_H__

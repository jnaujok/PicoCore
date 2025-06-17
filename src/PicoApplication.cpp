#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/sync.h>
#include <vector>
#include <queue>
#include <memory>
#include <functional>
#include <map>

#include "DeviceDriver.h"
#include "Event.h"
#include "EventManager.h"
#include "RealTimePlugin.h"
#include "Framework.h"

// Example concrete driver (for demonstration)
class ExampleDriver : public DeviceDriver {
    std::shared_ptr<EventManager> event_manager;
public:
    ExampleDriver(std::shared_ptr<EventManager> em) : event_manager(em) {}
    void handle_event(const Event& event) override {
        // Process event
        if (event.type == EventType::DEVICE_RESPONSE) {
            queue_notification({0xAA}); // Example notification
        }
    }
    void send_command(const std::vector<uint8_t>& command) override {
        // Send command via I2C/SPI (placeholder)
    }
    void queue_notification(const std::vector<uint8_t>& data) override {
        event_manager->queue_event({EventType::NOTIFICATION, 0, data });
    }
};

// Example real-time plugin
class ExampleGPIOPlugin : public RealTimePlugin {
    std::shared_ptr<EventManager> event_manager;
public:
    ExampleGPIOPlugin(std::shared_ptr<EventManager> em) : event_manager(em) {}
    void execute() override {
        // Toggle GPIO pin (placeholder)
        Event event{EventType::REAL_TIME_EVENT, 0, {0x01}};
        push_event(event);
    }
    void push_event(const Event& event) override {
        event_manager->queue_event(event);
    }
};

// Example user framework
class MyFramework : public Framework {
protected:
    void system_init() override {
        // Register a device
        auto driver = std::make_shared<ExampleDriver>(event_manager);
        event_manager->register_device(0x10, driver, true); // I2C device

        // Register a real-time plugin
        auto plugin = std::make_shared<ExampleGPIOPlugin>(event_manager);
        scheduler->register_plugin(plugin, 1000); // Run every 1ms
    }
};

int main() {
    stdio_init_all();
    auto framework = std::make_unique<MyFramework>();
    framework->start();
    return 0;
}

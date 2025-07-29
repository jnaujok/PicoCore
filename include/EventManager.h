#ifndef PICO_CORE_EVENT_MANAGER_H__
#define PICO_CORE_EVENT_MANAGER_H__

#include "Event.h"
#include "EventHandler.h"
#include "InterfaceHandler.h"
#include "I2CHandler.h"
#include "SPIHandler.h"
#include <queue>

// Event Manager (runs on Core 1)
class EventManager {
    std::deque<Event> event_queue;
    mutex_t queue_mutex;
    std::map<uint8_t, std::shared_ptr<DeviceDriver>> devices;
    std::unique_ptr<InterfaceHandler> i2c_handler;
    std::unique_ptr<InterfaceHandler> spi_handler;
    std::map<EventType, std::vector<std::shared_ptr<IEventHandler>>> handlers;

public:
    EventManager() {
        mutex_init(&queue_mutex);
        i2c_handler = std::make_unique<I2CHandler>();
        spi_handler = std::make_unique<SPIHandler>();
    }

    void register_device(uint8_t address, std::shared_ptr<DeviceDriver> driver, bool use_i2c) {
        mutex_enter_blocking(&queue_mutex);
        devices[address] = driver;
        mutex_exit(&queue_mutex);

        if (use_i2c) {
            i2c_handler->register_device(address, driver);
        } else {
            spi_handler->register_device(address, driver);
        }
    }

    void queue_event(const Event& event) {
        mutex_enter_blocking(&queue_mutex);
        event_queue.push_back(event);
        mutex_exit(&queue_mutex);
    }

    void register_event_handler(EventType eventType, std::shared_ptr<IEventHandler> handler ) {
        if( handlers.count(eventType) == 0 ) {
            handlers[eventType] = std::vector<std::shared_ptr<IEventHandler>>();
        }

        handlers[eventType].push_back( handler );
    }

    void run() {
        while (true) {
            if (!event_queue.empty()) {
                mutex_enter_blocking(&queue_mutex);
                Event event = event_queue.front();
                event_queue.pop_front();
                mutex_exit(&queue_mutex);

                if ( handlers.count(event.type) > 0 )
                {
                    for ( std::shared_ptr<IEventHandler> handler : handlers[event.type] ) {
                        handler->handleEvent(event);
                    }
                }
                
                if (devices.count(event.device_address)) {
                    devices[event.device_address]->handle_event(event);
                }
            }
            tight_loop_contents(); // Idle loop handler
        }
    }
};

#endif // PICO_CORE_EVENT_MANAGER_H__


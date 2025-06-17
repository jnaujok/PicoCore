#ifndef PICO_CORE_REAL_TIME_SCHEDULER_H__
#define PICO_CORE_REAL_TIME_SCHEDULER_H__

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/sync.h>
#include <memory>

#include "RealTimePlugin.h"
#include "EventManager.h"


// Real-Time Scheduler (runs on Core 0)
class RealTimeScheduler {
    struct ScheduledTask {
        std::shared_ptr<RealTimePlugin> plugin;
        uint32_t interval_us;
        uint64_t last_run_us;
    };

    std::vector<ScheduledTask> tasks;
    std::shared_ptr<EventManager> event_manager;
    mutex_t task_mutex;

public:
    RealTimeScheduler(std::shared_ptr<EventManager> em) : event_manager(em) {
        mutex_init(&task_mutex);
    }

    void register_plugin(std::shared_ptr<RealTimePlugin> plugin, uint32_t interval_us = 0) {
        mutex_enter_blocking(&task_mutex);
        tasks.push_back({plugin, interval_us, 0});
        mutex_exit(&task_mutex);
    }

    void run() {
        while (true) {
            uint64_t now_us = time_us_64();
            mutex_enter_blocking(&task_mutex);
            for (auto& task : tasks) {
                if (task.interval_us == 0 || now_us - task.last_run_us >= task.interval_us) {
                    task.plugin->execute();
                    task.last_run_us = now_us;
                }
            }
            mutex_exit(&task_mutex);
            tight_loop_contents(); // Yield
        }
    }
};

#endif // PICO_CORE_REAL_TIME_SCHEDULER_H__

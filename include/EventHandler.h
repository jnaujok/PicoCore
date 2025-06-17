#ifndef __PICO_CORE_EVENT_HANDLER_H__
#define __PICO_CORE_EVENT_HANDLER_H__

#include "Event.h"

class IEventHandler {
    public:
        virtual void handleEvent(Event &event) = 0;
};

#endif // __PICO_CORE_EVENT_HANDLER_H__


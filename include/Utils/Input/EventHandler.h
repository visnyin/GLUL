#ifndef UTILS_INPUT_EVENTHANDLER_H_INCLUDED
#define UTILS_INPUT_EVENTHANDLER_H_INCLUDED

#include <Utils/Input/Event.h>
#include <Utils/Input/Types.h>

#include <set>
#include <unordered_map>

namespace Util {

    namespace Input {

        class EventAggregator;

        class EventHandler {
            friend class EventAggregator;

            public:
                virtual void handleInputEvent(const Event& inputEvent) const = 0;

            private:
                void _unregisterNotifications();

                std::unordered_map<Event::Type, std::set<EventAggregator*>> _aggregators;
        };

    }

}

#endif

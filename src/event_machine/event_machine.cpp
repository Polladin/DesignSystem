
#include "event_machine.h"

#include "event_receiver.h"


namespace eventmachine{


void EventMachine::send_event(events_list event)
{
    for (auto & el : receivers)
        el->on_event(event);
}


}//namespace eventmachine

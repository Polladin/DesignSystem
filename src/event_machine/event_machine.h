
#pragma once

#include "events_list.h"

#include <vector>


namespace eventmachine{


// Forward declaration
class EventReceiver;


/**
 *      EventMachine
 *
 */
class EventMachine
{
public:

    //
    void send_event(events_list event);

    //
    void add_receiver(EventReceiver * rcv) { receivers.push_back(rcv); }

private:

    std::vector<EventReceiver *> receivers;

};


}//namespace eventmachine

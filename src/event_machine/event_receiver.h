
#pragma once

#include "events_list.h"


namespace eventmachine{


class EventReceiver
{
public:

    virtual void on_event(events_list event) = 0;

    virtual ~EventReceiver() {}
};


}//namespace eventmachine

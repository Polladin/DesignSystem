

#include "calc_fps.h"

#include "event_machine/event_machine.h"

#include <iostream>


namespace engine{


CalcFps::CalcFps( eventmachine::EventMachine * i_eventMachine )
    : prevTimePoint  { t_time::now() }
    , p_eventMachine { i_eventMachine }
{}


void CalcFps::step()
{
    // Increase frame counter
    ++framesShown;

    // Get new time point
    t_time_point newTimePoint = t_time::now();

    // Calc duration between previous and current time points
    t_duration_interval elapsed_interval = std::chrono::duration_cast<t_duration_interval>(newTimePoint - prevTimePoint);

    // If (current time point - last time point) < duration to update then do nothing
    if (elapsed_interval < DURATION_TO_UPDATE_FPS)
        return;

    // Update fps
    fps =   (decltype(elapsed_interval)::period::den * framesShown)
          / (float(elapsed_interval.count()) * decltype(elapsed_interval)::period::num);

    // Notify a subscriber
    if (p_eventMachine)
        p_eventMachine->send_event(eventmachine::events_list::UPDATE_FPS);

    // Reset counter and previous time stamp
    framesShown = 0;
    prevTimePoint = newTimePoint;
}


}//namespace engine

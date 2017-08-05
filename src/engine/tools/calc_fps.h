
#pragma once

#include "tool.h"

#include <chrono>
#include <ctime>
#include <functional>
#include <iostream>


namespace eventmachine{


// Forward declaration
class EventMachine;


}//namespace eventmachine

namespace engine{


/**
 *
 */
class CalcFps : public Tool
{
private:

    using t_time = std::chrono::high_resolution_clock;
    using t_time_point = std::chrono::time_point<t_time>;

    using t_duration_interval = std::chrono::microseconds;

    // Default duration to update fps
    const t_duration_interval DURATION_TO_UPDATE_FPS { std::chrono::milliseconds(500) }; // in seconds

public:

    CalcFps(eventmachine::EventMachine * i_eventMachine = nullptr);

    ~CalcFps() {std::cout << "Dstor CalcFps" << std::endl;}

    virtual void step() override;

    // Return FPS
    float get_fps() { return fps; }

private:

    float fps {0.0f};

    long long framesShown {0};

    t_time_point prevTimePoint { t_time::now() };

    eventmachine::EventMachine * p_eventMachine { nullptr };
};


}//namespace engine

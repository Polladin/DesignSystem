
#pragma once

#include "tool.h"

#include <chrono>
#include <ctime>
#include <functional>
#include <iostream>

namespace engine{

// Forward declaration
class Engine;


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

    CalcFps(Engine * parent_engine = nullptr);

    ~CalcFps() {std::cout << "Dstor CalcFps" << std::endl;}

    virtual void step() override;

    // Return FPS
    float get_fps() { return fps; }

private:

    float fps {0.0f};

    long long framesShown {0};

    t_time_point prevTimePoint { t_time::now() };

    Engine * p_engine;

};


}//namespace engine

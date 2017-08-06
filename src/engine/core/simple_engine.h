
#pragma once

#include "engine/core/engine.h"

#include "engine/tools/calc_fps.h"
#include "engine/map/map.h"

#include <memory>
#include <iostream>


namespace eventmachine{


// Forward declaration
class EventMachine;


}//namespace eventmachine


namespace engine{


// Forward declaration
class CalcFps;


/**
 *
 */
class SimpleEngine : public Engine
{
public:
    const size_t MAX_X = 10;
    const size_t MAX_Y = 10;

public:

    SimpleEngine(std::shared_ptr<eventmachine::EventMachine> & i_eventMachine);

    // do a STEP
    void step() override;

    // get fps
    float get_fps() const override;

private:

    std::shared_ptr<CalcFps> fpsCalculator;


    std::shared_ptr<eventmachine::EventMachine> eventMachine;

    std::unique_ptr<map::Map> p_mapObj;
};


}//namespace engine

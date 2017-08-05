
#pragma once

#include "engine/core/engine.h"

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

    SimpleEngine(std::shared_ptr<eventmachine::EventMachine> & i_eventMachine);

    // do a STEP
    void step() override;

    // get fps
    float get_fps() const override;

    // Destructor
    virtual ~SimpleEngine() {std::cout << "Dstor SimpleEngine" << std::endl;}

private:

    std::shared_ptr<CalcFps> fpsCalculator;

    std::shared_ptr<eventmachine::EventMachine> eventMachine;
};


}//namespace engine


#include "simple_engine.h"

#include "event_machine/event_machine.h"
#include "engine/tools/calc_fps.h"


namespace engine{


SimpleEngine::SimpleEngine(std::shared_ptr<eventmachine::EventMachine> & i_eventMachine)
    : eventMachine { i_eventMachine }
{
    // Create FPS calculator
    fpsCalculator.reset(new CalcFps(eventMachine.get()));
}


void SimpleEngine::step()
{
    if (fpsCalculator)
        fpsCalculator->step();
}


float SimpleEngine::get_fps() const
{
    return fpsCalculator->get_fps();
}


}//namespace engine

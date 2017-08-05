
#include "simple_engine.h"

#include "event_machine/event_machine.h"
#include "engine/tools/calc_fps.h"


namespace engine{


<<<<<<< HEAD
SimpleEngine::SimpleEngine(std::shared_ptr<eventmachine::EventMachine> & i_eventMachine)
    : eventMachine { i_eventMachine }
{
    // Create FPS calculator
    fpsCalculator.reset(new CalcFps(eventMachine.get()));
=======
    // Map initialize
    p_mapObj.reset(new map::Map(MAX_X, MAX_Y));

    // Path Example
    p_mapObj->place_connectivity(2, 2, map::connectivity_type::RIGHT);
    p_mapObj->place_connectivity(2, 3, map::connectivity_type::RIGHT);
    p_mapObj->place_connectivity(2, 4, map::connectivity_type::RIGHT);

    p_mapObj->place_connectivity(4, 2, map::connectivity_type::LEFT);
    p_mapObj->place_connectivity(4, 3, map::connectivity_type::LEFT);
    p_mapObj->place_connectivity(4, 4, map::connectivity_type::LEFT);

    p_mapObj->place_connectivity(3, 2, map::connectivity_type::TOP);
    p_mapObj->place_connectivity(3, 4, map::connectivity_type::BOT);

    // Debug
    p_mapObj->print_map();
>>>>>>> 1f611940277455169fd32a9c6ad69aac62dc2bab
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

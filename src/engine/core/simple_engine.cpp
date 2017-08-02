
#include "simple_engine.h"

namespace engine{


SimpleEngine::SimpleEngine()
{
    //
    mediator.reset(new mediator::Mediator());

    //
    fpsCalculator.reset(new CalcFps(this));

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
}


void SimpleEngine::step()
{
    if (fpsCalculator)
        fpsCalculator->step();
}


}//namespace engine

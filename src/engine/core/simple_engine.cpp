
#include "simple_engine.h"

#include "event_machine/event_machine.h"
#include "engine/tools/calc_fps.h"
#include "engine/vehicles/vehicle_unit.h"


namespace engine{


SimpleEngine::SimpleEngine(std::shared_ptr<eventmachine::EventMachine> & i_eventMachine)
    : eventMachine { i_eventMachine }
{
    // Create FPS calculator
    fpsCalculator.reset(new CalcFps(eventMachine.get()));

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

    // Create Active Objects
    auto * activeObject = new VehicleUnit();
    activeObjects.emplace_back(activeObject, std::make_pair(p_mapObj->slots[5][5], 0));
    p_mapObj->slots[5][5]->add_active_object(activeObject);
}

void SimpleEngine::step_active()
{
    for (auto & activeObj : activeObjects)
    {
        // Do a step
        activeObj.first->step();

        // Change slot if move across a bound
        if (activeObj.first->is_out_of_bound())
            active_object_change_slot(activeObj);

    }
}


void SimpleEngine::active_object_change_slot(t_vehicle_info & activeObj)
{
    vehicle::VehicleUnit::t_border xBound = activeObj->is_out_of_x_bound();
    vehicle::VehicleUnit::t_border yBound = activeObj->is_out_of_y_bound();

    // X bound

    if (xBound == vehicle::VehicleUnit::t_border::LEFT)
    {
        if (activeObj.second.first->x != 0)
        {
            p_mapObj->slots[activeObj.second.first->x][activeObj.second.first->y].del_active_object(activeObj.first);
            p_mapObj->slots[activeObj.second.first->x - 1][activeObj.second.first->y].add_active_object(activeObj.first);

            activeObj.second.first = p_mapObj->slots[activeObj.second.first->x - 1][activeObj.second.first->y].get();
            activeObj.first->step_to_next_slot(vehicle::VehicleUnit::t_border::LEFT);
        }
        else
        {
            activeObj.first->set_vx(0);
        }
    }

    if (xBound == vehicle::VehicleUnit::t_border::RIGHT)
    {
        if (activeObj.second.first->x +1 < p_mapObj->maxX)
        {
            p_mapObj->slots[activeObj.second.first->x][activeObj.second.first->y].del_active_object(activeObj.first);
            p_mapObj->slots[activeObj.second.first->x + 1][activeObj.second.first->y].add_active_object(activeObj.first);

            activeObj.second.first = p_mapObj->slots[activeObj.second.first->x + 1][activeObj.second.first->y].get();
            activeObj.first->step_to_next_slot(vehicle::VehicleUnit::t_border::RIGHT);
        }
        else
        {
            activeObj.first->set_vx(0);
        }
    }
    // Y bound

    if (yBound == vehicle::VehicleUnit::t_border::TOP)
    {
        if (activeObj.second.first->y + 1 < p_mapObj->maxY)
        {
            p_mapObj->slots[activeObj.second.first->x][activeObj.second.first->y].del_active_object(activeObj.first);
            p_mapObj->slots[activeObj.second.first->x][activeObj.second.first->y + 1].add_active_object(activeObj.first);

            activeObj.second.first = p_mapObj->slots[activeObj.second.first->x][activeObj.second.first->y + 1].get();
            activeObj.first->step_to_next_slot(vehicle::VehicleUnit::t_border::TOP);
        }
        else
        {
            activeObj.first->set_vy(0);
        }
    }

    if (yBound == vehicle::VehicleUnit::t_border::BOT)
    {
        if (activeObj.second.first->y != 0)
        {
            p_mapObj->slots[activeObj.second.first->x][activeObj.second.first->y].del_active_object(activeObj.first);
            p_mapObj->slots[activeObj.second.first->x][activeObj.second.first->y - 1].add_active_object(activeObj.first);

            activeObj.second.first = p_mapObj->slots[activeObj.second.first->x][activeObj.second.first->y - 1].get();
            activeObj.first->step_to_next_slot(vehicle::VehicleUnit::t_border::BOT);
        }
        else
        {
            activeObj.first->set_vy(0);
        }
    }
}


void SimpleEngine::step()
{
    if (fpsCalculator)
        fpsCalculator->step();

    step_active();
}


float SimpleEngine::get_fps() const
{
    return fpsCalculator->get_fps();
}


}//namespace engine

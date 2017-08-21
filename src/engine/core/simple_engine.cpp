
#include "simple_engine.h"

#include "event_machine/event_machine.h"
#include "engine/tools/calc_fps.h"
#include "engine/vehicles/vehicle_unit.h"
#include "engine/buildings/factory.h"


namespace engine{


void SimpleEngine::add_example1()
{
    // Map [10][10]
    // . . . . . . . . . .
    // . O > > > L . . . .
    // . . . . . L . . . .
    // . . . . . O . . . .
    // . . . . . . . . . .
    // . . . . . . . . . .
    // . . . . . . . . . .
    // . . . . . . . . . .
    // . . . . . . . . . .
    // . . . . . . . . . .


    // [1][1] - Factory (produce)
    // [1][2] - right belt
    // [1][3] - right belt
    // [1][4] - right belt
    // [1][5] - bot belt
    // [2][5] - bot belt
    // [3][5] - Factory (sell)

    // [1][1] - Factory (produce)
    objects.emplace_back(new objects::Factory());
    p_map->slots[1][1]->add_object(objects.back().get());

    // [1][2] - right belt
    objects.emplace_back(new objects::Belt(common::connectivity_type::RIGHT));
    p_map->slots[1][2]->add_object(objects.back().get());

    // [1][3] - right belt
    objects.emplace_back(new objects::Belt(common::connectivity_type::RIGHT));
    p_map->slots[1][3]->add_object(objects.back().get());

    // [1][4] - right belt
    objects.emplace_back(new objects::Belt(common::connectivity_type::RIGHT));
    p_map->slots[1][4]->add_object(objects.back().get());

    // [1][5] - bot belt
    objects.emplace_back(new objects::Belt(common::connectivity_type::BOT));
    p_map->slots[1][5]->add_object(objects.back().get());

    // [2][5] - bot belt
    objects.emplace_back(new objects::Belt(common::connectivity_type::BOT));
    p_map->slots[2][5]->add_object(objects.back().get());

    // [3][5] - Factory (sell)
    objects.emplace_back(new objects::BuildSell());
    p_map->slots[3][5]->add_object(objects.back().get());

}

SimpleEngine::SimpleEngine(std::shared_ptr<eventmachine::EventMachine> & i_eventMachine)
    : eventMachine { i_eventMachine }
{
    p_map = map::Map::get_instance();

    // Create FPS calculator
    fpsCalculator.reset(new CalcFps(eventMachine.get()));

//     // Map initialize
//    p_map.reset(new map::Map(MAX_X, MAX_Y));

    // Path Example
    p_map->place_connectivity(2, 2, map::connectivity_type::RIGHT);
    p_map->place_connectivity(2, 3, map::connectivity_type::RIGHT);
    p_map->place_connectivity(2, 4, map::connectivity_type::RIGHT);

    p_map->place_connectivity(4, 2, map::connectivity_type::LEFT);
    p_map->place_connectivity(4, 3, map::connectivity_type::LEFT);
    p_map->place_connectivity(4, 4, map::connectivity_type::LEFT);

    p_map->place_connectivity(3, 2, map::connectivity_type::TOP);
    p_map->place_connectivity(3, 4, map::connectivity_type::BOT);

    // Debug
    p_map->print_map();

    // Create Active Objects
    vehicle::VehicleUnit * activeObject = new vehicle::VehicleUnit();
    activeObject->set_vx(0.01);

    activeObjects.push_back(std::pair<t_vehicle_pointer, t_slot_info>(activeObject, std::pair<map::Slot*, int>(p_map->slots[5][5].get(), 0)));
    p_map->slots[5][5]->add_active_object(activeObject);
}

void SimpleEngine::step_active()
{
    for (auto & activeObj : activeObjects)
    {
        // Do a step
        activeObj.first->step();

        // Change slot if move across a bound
        if (activeObj.first->is_out_of_bound())
        {
            active_object_change_slot(activeObj);
            p_map->print_map();
        }

    }
}


void SimpleEngine::active_object_change_slot(t_vehicle_info & activeObj)
{
    vehicle::VehicleUnit::t_border xBound = activeObj.first->is_out_of_x_bound();
    vehicle::VehicleUnit::t_border yBound = activeObj.first->is_out_of_y_bound();

    // X bound

    if (xBound == vehicle::VehicleUnit::t_border::LEFT)
    {
        if (activeObj.second.first->x != 0)
        {
            p_map->slots[activeObj.second.first->x][activeObj.second.first->y]->del_active_object(activeObj.first);
            p_map->slots[activeObj.second.first->x - 1][activeObj.second.first->y]->add_active_object(activeObj.first);

            activeObj.second.first = p_map->slots[activeObj.second.first->x - 1][activeObj.second.first->y].get();
            activeObj.first->step_to_next_slot(vehicle::VehicleUnit::t_border::LEFT);
        }
        else
        {
            activeObj.first->set_vx(0);
            activeObj.first->set_pos_x(-1.0f);
        }
    }

    if (xBound == vehicle::VehicleUnit::t_border::RIGHT)
    {
        if (activeObj.second.first->x +1 < p_map->maxX)
        {
            p_map->slots[activeObj.second.first->x][activeObj.second.first->y]->del_active_object(activeObj.first);
            p_map->slots[activeObj.second.first->x + 1][activeObj.second.first->y]->add_active_object(activeObj.first);

            activeObj.second.first = p_map->slots[activeObj.second.first->x + 1][activeObj.second.first->y].get();
            activeObj.first->step_to_next_slot(vehicle::VehicleUnit::t_border::RIGHT);
        }
        else
        {
            activeObj.first->set_vx(0);
            activeObj.first->set_pos_x(1.0f);
        }
    }
    // Y bound

    if (yBound == vehicle::VehicleUnit::t_border::TOP)
    {
        if (activeObj.second.first->y + 1 < p_map->maxY)
        {
            p_map->slots[activeObj.second.first->x][activeObj.second.first->y]->del_active_object(activeObj.first);
            p_map->slots[activeObj.second.first->x][activeObj.second.first->y + 1]->add_active_object(activeObj.first);

            activeObj.second.first = p_map->slots[activeObj.second.first->x][activeObj.second.first->y + 1].get();
            activeObj.first->step_to_next_slot(vehicle::VehicleUnit::t_border::TOP);
        }
        else
        {
            activeObj.first->set_vy(0);
            activeObj.first->set_pos_y(1.0f);
        }
    }

    if (yBound == vehicle::VehicleUnit::t_border::BOT)
    {
        if (activeObj.second.first->y != 0)
        {
            p_map->slots[activeObj.second.first->x][activeObj.second.first->y]->del_active_object(activeObj.first);
            p_map->slots[activeObj.second.first->x][activeObj.second.first->y - 1]->add_active_object(activeObj.first);

            activeObj.second.first = p_map->slots[activeObj.second.first->x][activeObj.second.first->y - 1].get();
            activeObj.first->step_to_next_slot(vehicle::VehicleUnit::t_border::BOT);
        }
        else
        {
            activeObj.first->set_vy(0);
            activeObj.first->set_pos_y(-1.0f);
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

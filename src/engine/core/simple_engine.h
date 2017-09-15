
#pragma once

#include "engine/core/engine.h"

#include "engine/tools/calc_fps.h"
#include "engine/map/map.h"

#include "engine/vehicles/vehicle_unit.h"

#include <memory>
#include <iostream>
#include <vector>


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

    using t_vehicle_pointer = vehicle::VehicleUnit *;
    using t_slot_info = std::pair<map::Slot*, int>;
    using t_vehicle_info = std::pair<t_vehicle_pointer, t_slot_info>;

    const size_t MAX_X = 10;
    const size_t MAX_Y = 10;

public:

    SimpleEngine(std::shared_ptr<eventmachine::EventMachine> & i_eventMachine);

    // do a STEP
    void step() override;

    // get fps
    float get_fps() const override;

private:

    void add_example1();

    void step_active();

    void active_object_change_slot(t_vehicle_info & activeObj);

private:

    std::shared_ptr<CalcFps> fpsCalculator;

    std::shared_ptr<eventmachine::EventMachine> eventMachine;

//    std::unique_ptr<map::Map> p_mapObj;

    map::Map * p_map;

    std::vector<t_vehicle_info> activeObjects;
    std::vector<std::shared_ptr<objects::Build>> objects;
};


}//namespace engine

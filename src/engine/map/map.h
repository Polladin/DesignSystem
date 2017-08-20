
#pragma once

#include <vector>
#include <memory>
#include <list>

#include "engine/common.h"


namespace vehicle{

// Forward declaration
class VehicleUnit;

}//


namespace map{


// Forward declaration
class Slot;

enum class connectivity_type
{
      UNDEFINED = 0
    , LEFT
    , RIGHT
    , TOP
    , BOT
};


/**
 *
 */
class Connectivity
{
public:

    Connectivity(connectivity_type i_type)
        : connType { i_type }
    {
//        // Base connectivity initialization
//        for (size_t i = 0; i < connectivityBase.size(); ++i)
//            connectivityBase[i] = nullptr;
    }


    bool add_new_slot(Slot * slot);

public:

    // List of connected with current slots
    std::vector<Slot *> connected;

    // type of connectivity
    connectivity_type connType { connectivity_type::UNDEFINED };

    //
//    std::array<Slot *, common::connectivity_type::COUNT_CONNECTIVITY_TYPES> connectivityBase;
};


/**
 *
 */
class Slot
{
public:

    Slot(size_t i_x, size_t i_y)
        : x {i_x}
        , y {i_y}
    {}

    bool add_connect_to_slot(Slot * slot);

    void add_active_object(vehicle::VehicleUnit * obj);
    bool del_active_object(vehicle::VehicleUnit * obj);

public:
    std::unique_ptr<Connectivity> connectivity { nullptr };

    std::list<vehicle::VehicleUnit*> activeObjects;

    size_t x;
    size_t y;
};


/**
 *
 */
class Map
{
public:

    Map(size_t i_maxX, size_t i_maxY);

    bool place_connectivity(size_t x, size_t y, connectivity_type connType);

    //
    void print_map();

private:

    //
    void update_neighbor_connectivity(size_t x, size_t y, connectivity_type connType);


public:

    size_t maxX { 0 };
    size_t maxY { 0 };

    std::vector<std::vector<std::unique_ptr<Slot>>> slots;
};


}//namespace map

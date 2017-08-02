
#pragma once

#include <vector>
#include <memory>


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
    {}


    bool add_new_slot(Slot * slot);

public:

    // List of connected with current slots
    std::vector<Slot *> connected;

    // type of connectivity
    connectivity_type connType { connectivity_type::UNDEFINED };
};


/**
 *
 */
class Slot
{
public:

    bool add_connect_to_slot(Slot * slot);

public:
    std::unique_ptr<Connectivity> connectivity { nullptr };
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
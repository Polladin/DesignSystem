
#include "map.h"

#include <stdexcept>
#include <algorithm>

#include <iostream>


namespace map {

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Connectivity

bool Connectivity::add_new_slot(Slot * slot)
{
    if (std::find(connected.begin(), connected.end(), slot) != connected.end())
        return false;

    connected.push_back(slot);

    return true;
}

//                             END Connectivity
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
//                               Slot

bool Slot::add_connect_to_slot(Slot * slot)
{
    if (connectivity.get() == nullptr)
        return false;

    return connectivity->add_new_slot(slot);
}

void Slot::add_active_object(vehicle::VehicleUnit * obj)
{
    activeObjects.push_back(obj);
}

bool Slot::del_active_object(vehicle::VehicleUnit * obj)
{
    auto foundIt = std::find(activeObjects.begin(), activeObjects.end(), obj);

    if (foundIt != activeObjects.end())
    {
        activeObjects.erase(foundIt);
        return true;
    }

    return false;
}

//                             END Slot
////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////
//                               Map

Map::Map(size_t i_maxX, size_t i_maxY)
    : maxX { i_maxX }
    , maxY { i_maxY }
{
    // Set X size
    slots.resize(maxX);

    // For each row
    for (size_t i = 0; i < maxX; ++i)
    {
        // Set Y size
        slots[i].resize(maxY);

        // Init slot
        for (size_t j = 0; j < maxY; ++j)
            slots[i][j].reset(new Slot(i, j));
    }

}


bool Map::place_connectivity(size_t x, size_t y, connectivity_type connType)
{
    // Check bounds
    if (x > maxX || y > maxY)
        throw std::runtime_error("Outbound X or Y in place_connectivity");

    // Any connectivity should not be placed
    if (slots[x][y]->connectivity.get() != nullptr)
        return false;

    // Place a connectivity
    slots[x][y]->connectivity.reset(new Connectivity(connType));

    // Update connectivity of neighboring slots
    update_neighbor_connectivity(x, y, connType);

    return true;
}


void Map::update_neighbor_connectivity(size_t x, size_t y, connectivity_type connType)
{
    if (x != 0 && connType != connectivity_type::TOP)
        slots[x - 1][y]->add_connect_to_slot(slots[x][y].get());

    if (x != maxX && connType != connectivity_type::BOT)
        slots[x + 1][y]->add_connect_to_slot(slots[x][y].get());

    if (y != 0 && connType != connectivity_type::LEFT)
        slots[x][y - 1]->add_connect_to_slot(slots[x][y].get());

    if (y != maxY && connType != connectivity_type::RIGHT)
        slots[x][y + 1]->add_connect_to_slot(slots[x][y].get());
}


void Map::print_map()
{
    std::cout << "\nStart map dumping ...\n";

    for (size_t i = 0; i < maxX; ++i)
    {
        for (size_t j = 0; j < maxY; ++j)
        {
            if (!slots[i][j]->activeObjects.empty())
            {
                std::cout << "A";
            }
            else if (slots[i][j]->connectivity.get() != nullptr)
            {
                if (slots[i][j]->connectivity->connType == connectivity_type::LEFT)
                    std::cout << "<";
                if (slots[i][j]->connectivity->connType == connectivity_type::RIGHT)
                    std::cout << ">";
                if (slots[i][j]->connectivity->connType == connectivity_type::TOP)
                    std::cout << "T";
                if (slots[i][j]->connectivity->connType == connectivity_type::BOT)
                    std::cout << "L";
            }
            else
            {
                std::cout << "_";
            }
        }
        std::cout << std::endl;
    }
}

//                             END Map
////////////////////////////////////////////////////////////////////////////////////////////////


}//namespace map

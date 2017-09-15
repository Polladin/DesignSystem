
#include "vehicle_unit.h"

#include <stdexcept>

#include "engine/map/map.h"


namespace vehicle{

// ---------------------------------- MoveableObject -----------------------------

void MoveableObject::step()
{
    pos.first  += vx;
    pos.second += vy;

    while (is_out_of_bound())
    {
        move_across_slot();
    }    
}

void MoveableObject::move_across_slot()
{
    // Remove from slot
    map::Map::get_instance()->slots[X][Y]->del_active_object(this);

    // Calc slot offset
    int x_offset = 0;
    int y_offset = 0;

    // Right
    while (pos.first > 1.0)
    {
        ++x_offset;
        pos.first -= 1.0;
    }

    // Left
    while (pos.first < -1.0)
    {
        --x_offset;
        pos.first += 1.0;
    }

    // Top
    while (pos.second > 1.0)
    {
        ++y_offset;
        pos.second -= 1.0;
    }

    // Bot
    while (pos.second < -1.0)
    {
        --y_offset;
        pos.second += 1.0;
    }

    // Get max X and Y
    size_t max_x = map::Map::get_instance()->maxX;
    size_t max_y = map::Map::get_instance()->maxY;

    // Calc new x and y
    int new_x = static_cast<int>(X) + x_offset;
    int new_y = static_cast<int>(Y) + y_offset;

    // Compare with border
    if (new_x < 0)
    {
        new_x = 0;
        pos.first = -1.0;
    }
    else if (new_x >= max_x)
    {
        new_x = max_x - 1;
        pos.first = 1.0;
    }

    if (new_y < 0)
    {
        new_y = 0;
        pos.second = -1.0;
    }
    else if (new_y >= max_y)
    {
        new_y = max_y - 1;
        pos.second = 1.0;
    }

    X = new_x;
    Y = new_y;

    // Place on new Slot
    map::Map::get_instance()->slots[X][Y]->add_active_object(this);
}


bool MoveableObject::is_out_of_bound() const
{
    if (pos.first > 1.0f || pos.first < -1.0f || pos.second > 1.0f || pos.second < -1.0f)
        return true;

    return false;
}


MoveableObject::t_border MoveableObject::is_out_of_x_bound() const
{
    if (pos.first > 1.0f)
        return t_border::RIGHT;

    if (pos.first < -1.0f)
        return t_border::LEFT;

    return t_border::UNREACHED;
}

MoveableObject::t_border MoveableObject::is_out_of_y_bound() const
{
    if (pos.second > 1.0f)
        return t_border::TOP;

    if (pos.second < -1.0f)
        return t_border::BOT;

    return t_border::UNREACHED;
}



// ---------------------------------- VehicleUnit ------------------------------

void VehicleUnit::step()
{
    pos.first += vx;
    pos.second += vy;

    vx += ax;
    vy += ay;
}

bool VehicleUnit::is_out_of_bound() const
{
    if (pos.first > 1.0f || pos.first < -1.0f || pos.second > 1.0f || pos.second < -1.0f)
        return true;

    return false;
}

VehicleUnit::t_border VehicleUnit::is_out_of_x_bound() const
{
    if (pos.first > 1.0f)
        return t_border::RIGHT;

    if (pos.first < -1.0f)
        return t_border::LEFT;

    return t_border::UNREACHED;
}

VehicleUnit::t_border VehicleUnit::is_out_of_y_bound() const
{
    if (pos.second > 1.0f)
        return t_border::TOP;

    if (pos.second < -1.0f)
        return t_border::BOT;

    return t_border::UNREACHED;
}

void VehicleUnit::step_to_next_slot(t_border border)
{
    switch (border)
    {
    case t_border::LEFT:
        pos.first = 1.0f;
        break;

    case t_border::RIGHT:
        pos.first = -1.0f;
        break;

    case t_border::TOP:
        pos.second = -1.0f;
        break;

    case t_border::BOT:
        pos.second = 1.0f;
        break;

    default:
        throw std::runtime_error("Bad border type");
    }
}

int VehicleUnit::pop(int amount)
{
    if (amount <= storage)
    {
        storage -= amount;
        return amount;
    }

    // amount > storage
    amount = storage;

    // pop all
    storage = 0;

    return amount;
}


int VehicleUnit::push(int amount)
{
    int notPushed { 0 };

    if (storage + amount > maxStorageSize)
    {
        notPushed = amount - (maxStorageSize - storage);
        amount = maxStorageSize;
    }
    else
    {
        storage += amount;
    }

    return notPushed;
}


}//namespace vehicle




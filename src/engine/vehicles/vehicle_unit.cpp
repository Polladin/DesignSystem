
#include "vehicle_unit.h"

#include <stdexcept>


namespace vehicle{


void VehicleUnit::step()
{
    pos.first += vx;
    pos.second = vy;

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





#include "vehicle_unit.h"


namespace vehicle{


void VehicleUnit::step()
{

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




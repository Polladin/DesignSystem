
#pragma once

#include "vehicle.h"


namespace vehicle{


/**
 *
 */
class VehicleUnit : public Vehicle
{
public:

    virtual void step() override;

    int count() const { return storage; }

    int pop(int amount);

    int push(int amount);

private:

    int storage { 0 };
    int maxStorageSize { 10 };
};


}//namespace vehicle

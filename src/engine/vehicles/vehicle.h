
#pragma once


namespace vehicle{


class Vehicle
{
public:

	virtual void step() = 0;

	virtual ~Vehicle() {}
};


}//namespace vehicle


#pragma once

#include <vector>


namespace vehicle{


using t_inner_position = std::pair<float, float>;


class Vehicle
{
public:
    
    enum class t_border
    {
        UNDEFINED
        , UNREACHED
        , LEFT
        , RIGHT
        , TOP
        , BOT
    };

public:

	virtual void step() = 0;

	virtual ~Vehicle() {}
};


}//namespace vehicle

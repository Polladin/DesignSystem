
#pragma once

#include "build.h"
#include "engine/common/common.h"


namespace objects{


/**
 *  Belt :
 *      Move objects
 */
class Belt : public Build
{

public:

    Belt(common::connectivity_type i_connType)
        : connType {i_connType}
    {}

    virtual void step() override {};

    virtual bool is_movable() override { return true; }

    common::connectivity_type next_slot_direction() { return connType; }

private:

    common::connectivity_type connType;

};


/**
 *  BuildSell :
 *      Sell
 */
class BuildSell : public Build
{
public:

    virtual void step() override {};

    void push(unsigned incoming) { countGoods += incoming; }

    unsigned countGoods {0};
};



/**
 *  Factory :
 *      Produced
 */
class Factory : public Build
{
public:

	virtual void step() override;

	int pop(int amount);

	int push(int amount);

private:

    unsigned long long stepCount {0};

	int count_in { 0 };
	int count_out { 0 };

	int maxPopByStep { 1 };
	int maxPushByStep { 10 };

};


}//namespace objects




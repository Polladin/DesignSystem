
#pragma once

#include "build.h"


namespace objects{


class Factory : public Build
{
public:

	virtual void step() override;

	int pop(int amount);

	int push(int amount);

private:

	int count_in { 0 };
	int count_out { 0 };

	int maxPopByStep { 1 };
	int maxPushByStep { 10 };

};


}//namespace objects




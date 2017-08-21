
#include "factory.h"



namespace objects{


void Factory::step()
{
	if (count_in > 0)
	{
		--count_in;
		++count_out;
	}

	++stepCount;

	if (stepCount % 60)
    {
        // produce a new Action Object

    }

}


int Factory::pop(int amount)
{
	//
	amount = (amount > maxPopByStep) ? maxPopByStep : amount;

	if (count_out >= amount)
	{
		count_out -= amount;
		return amount;
	}

	// count < amount
	int remains = count_out;

	// get all
	count_out = 0;

	return remains;

}


int Factory::push(int amount)
{
	if (maxPushByStep)

	count_in += amount;

    return 0;
}


}//namespace objects

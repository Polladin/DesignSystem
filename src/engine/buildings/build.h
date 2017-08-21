
#pragma once


namespace objects{


class Build
{
public:

	virtual void step() = 0;

	virtual ~Build() {}

	virtual bool is_movable() { return false; }

};


}//namespace objects


#pragma once


namespace mediator{


/**
 *
 */
class Observer
{
public:
    virtual ~Observer() {}
};


/**
 *
 */
class ObserverCalcFps : public Observer
{
public:
    virtual void update_fps(float fps) = 0;
};


}//namespace mediator

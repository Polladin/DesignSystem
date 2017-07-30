
#pragma once


#include "graphics/mediator.h"


namespace engine{


/**
 *
 */
class Engine
{
public:

    //////////////////////////////////////////////////
    //            Mandatory functions

    virtual void step() = 0;



    //          End  Mandatory functions
    //////////////////////////////////////////////////


    //////////////////////////////////////////////////
    //            Optional functions

    //
    virtual mediator::Mediator * get_mediator() { return nullptr; }

    //
    virtual float get_fps() const { return 0.0f; };



    //           End Optional functions
    //////////////////////////////////////////////////


    //////////////////////////////////////////////////
    //

    virtual void on_update_fps(float fps) {}

    //
    //////////////////////////////////////////////////


    virtual ~Engine() {}

};


}//namespace engine

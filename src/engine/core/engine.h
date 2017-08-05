
#pragma once


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
    virtual float get_fps() const { return 0.0f; };



    //           End Optional functions
    //////////////////////////////////////////////////


    virtual ~Engine() {}

};


}//namespace engine

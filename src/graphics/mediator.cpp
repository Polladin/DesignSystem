
#include "mediator.h"
#include "graphics/observers.h"


namespace mediator{


void Mediator::on_update_fps(float fps)
{
    for (auto & el : calcFpsObservers)
        el->update_fps(fps);
}



}//namespace mediator

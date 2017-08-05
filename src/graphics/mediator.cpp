
#include "mediator.h"

#include "graphics/observers.h"
#include "engine/core/engine.h"

#include <stdexcept>


namespace mediator{


Mediator::Mediator(engine::Engine * i_engine)
    : engine { i_engine }
{}


void Mediator::on_event(eventmachine::events_list event)
{
    if (engine == nullptr)
        return;

    switch(event)
    {

    case eventmachine::events_list::UNDEFINED:
        throw std::runtime_error("Received Undefined event");

    case eventmachine::events_list::UPDATE_FPS:
        on_update_fps(engine->get_fps());

    }
}


void Mediator::on_update_fps(float fps)
{
    for (auto & el : calcFpsObservers)
        el->update_fps(fps);
}



}//namespace mediator

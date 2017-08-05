
#pragma once

#include <vector>
#include <memory>

#include "graphics/observers.h"

#include "event_machine/event_receiver.h"


namespace engine{


// Forward declaration
class Engine;


}//namespace engine


namespace mediator{


/**
 *
 */
class Mediator : public eventmachine::EventReceiver
{
public:

    //
    Mediator(engine::Engine * i_engine = nullptr);

    //
    void on_event(eventmachine::events_list event) override;

    //
    void add_observer_calc_fps(std::shared_ptr<ObserverCalcFps> & obs) { calcFpsObservers.push_back(obs); }

private:

    // CalcFps
    void on_update_fps(float fps);

private:

    //
    engine::Engine * engine;

    //
    std::vector<std::shared_ptr<ObserverCalcFps>> calcFpsObservers;

};


}//namespace mediator

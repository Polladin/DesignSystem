
#pragma once

#include <vector>
#include <memory>

#include "graphics/observers.h"


namespace mediator{


/**
 *
 */
class Mediator
{
public:

    //
    void add_observer_calc_fps(std::shared_ptr<ObserverCalcFps> & obs) { calcFpsObservers.push_back(obs); }

    // CalcFps
    void on_update_fps(float fps);

private:
    std::vector<std::shared_ptr<ObserverCalcFps>> calcFpsObservers;

};


}//namespace mediator

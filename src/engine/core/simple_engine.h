
#pragma once

#include "engine/core/engine.h"

#include "engine/tools/calc_fps.h"

#include <memory>
#include <iostream>


namespace engine{


/**
 *
 */
class SimpleEngine : public Engine
{
public:

    SimpleEngine();

    // do a STEP
    void step() override;

    // get fps
    float get_fps() const override { return fpsCalculator->get_fps(); }

    // On update FPS
    virtual void on_update_fps(float fps) { mediator->on_update_fps(fps); }

    // Get pointer to mediator
    virtual mediator::Mediator * get_mediator() { return mediator.get(); }

    // Destructor
    virtual ~SimpleEngine() {std::cout << "Dstor SimpleEngine" << std::endl;}

private:

    std::unique_ptr<CalcFps> fpsCalculator;

    std::shared_ptr<mediator::Mediator> mediator;
};


}//namespace engine


#include "simple_engine.h"

namespace engine{


SimpleEngine::SimpleEngine()
{
    //
    mediator.reset(new mediator::Mediator());

    //
    fpsCalculator.reset(new CalcFps(this));

}


void SimpleEngine::step()
{
    if (fpsCalculator)
        fpsCalculator->step();
}


}//namespace engine

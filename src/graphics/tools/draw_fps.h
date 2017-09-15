
#pragma once

#include <iostream>

#include "event_machine/observers.h"

namespace graphics{


class DrawFps : public mediator::ObserverCalcFps
{
public:

    virtual void update_fps(float fps) override;

private:

    float fps { 0.0f };
};


}//namespace graphics

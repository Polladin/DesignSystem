
#pragma once

#include <iostream>

#include "graphics/observers.h"

namespace graphics{


class DrawFps : public mediator::ObserverCalcFps
{
public:

    virtual void update_fps(float fps) override;

private:

    float fps { 0.0f };
};


}//namespace graphics

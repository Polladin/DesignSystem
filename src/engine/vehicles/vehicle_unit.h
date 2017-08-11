
#pragma once

#include "vehicle.h"


namespace vehicle{


/**
 *
 */
class VehicleUnit : public Vehicle
{
public:
    enum class t_border
    {
          UNDEFINED
        , UNREACHED
        , LEFT
        , RIGHT
        , TOP
        , BOT
    };

public:

    virtual void step() override;

    int count() const { return storage; }

    int pop(int amount);

    int push(int amount);

    bool is_out_of_bound() const;

    t_border is_out_of_x_bound() const;
    t_border is_out_of_y_bound() const;

    void step_to_next_slot(t_border border);

    void set_vx(float v) { vx = v; }
    void set_vy(float v) { vy = v; }

private:

    int storage { 0 };
    int maxStorageSize { 10 };

    t_inner_position pos {0.0f, 0.0f};

    float vx, vy;
    float ax, ay;
};


}//namespace vehicle

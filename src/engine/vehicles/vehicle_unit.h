
#pragma once

#include "vehicle.h"


namespace vehicle{


/**
*
*/
class MoveableObject : public Vehicle
{
public:

    virtual void step() override;

    void set_vx(float v) { vx = v; }
    void set_vy(float v) { vy = v; }

    void set_pos_x(float x) { pos.first = x; };
    void set_pos_y(float y) { pos.second = y; };

private:

    bool is_out_of_bound() const;

    t_border is_out_of_x_bound() const;
    t_border is_out_of_y_bound() const;

    void move_across_slot();

private:

    // Position in slot
    t_inner_position pos{ 0.0f, 0.0f };

    // Speed in slot
    float vx, vy;

    // position in Map
    size_t X, Y;

    // Goal slot
    size_t goalX, goalY;
};



/**
 *
 */
class VehicleUnit : public Vehicle
{

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

    void set_pos_x(float x) {pos.first = x;};
    void set_pos_y(float y) {pos.second = y;};

private:

    int storage { 0 };
    int maxStorageSize { 10 };

    t_inner_position pos {0.0f, 0.0f};

    float vx, vy;
    float ax, ay;
};


}//namespace vehicle

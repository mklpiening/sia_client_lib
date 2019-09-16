#include "sialib/Sialib.hpp"

#include <iostream>

namespace sialib
{

void Sialib::handleMessage(SiaMsg& msg)
{
    if (throttleHandler)
    {
        throttleHandler(msg.throttle);
    }

    if (brakeHandler)
    {
        brakeHandler(msg.brake);
    }

    if (steeringWheelHandler)
    {
        steeringWheelHandler(msg.steeringwheel_angle);
    }

    if (leftLeverHandler)
    {
        leftLeverHandler(msg.steeringwheel_peripheral_left);
    }

    if (rightLeverHandler)
    {
        leftLeverHandler(msg.steeringwheel_peripheral_right);
    }

    if (driveStateHandler)
    {
        driveStateHandler(msg.shifter_state);
    }

    if (shiftUpHandler)
    {
        if (msg.shifter_state == SHIFT_UP && m_lastDriveState != SHIFT_UP)
        {
            shiftUpHandler();
        }
    }

    if (shiftDownHandler)
    {
        if (msg.shifter_state == SHIFT_DOWN && m_lastDriveState != SHIFT_DOWN)
        {
            shiftDownHandler();
        }
    }

    m_lastDriveState = msg.shifter_state;
}

} // namespace sialib
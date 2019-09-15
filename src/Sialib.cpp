#include "sialib/Sialib.hpp"

#include <iostream>

namespace sialib
{

void Sialib::handleMessage(SiaMsg& msg)
{
    if (throttleHandler)
    {
        throttleHandler(msg.throttle);
        std::cout << "throttle: " << (int)msg.throttle << std::endl;
    }

    if (brakeHandler)
    {
        brakeHandler(msg.brake);
        std::cout << "brake: " << (int)msg.brake << std::endl;
    }

    if (steeringWheelHandler)
    {
        steeringWheelHandler(msg.steeringwheel_angle);
        std::cout << "steeringWheel: " << (int)msg.steeringwheel_angle << std::endl;
    }

    if (leftLeverHandler)
    {
        leftLeverHandler(msg.steeringwheel_peripheral_left);
        std::cout << "left: " << (bool)msg.steeringwheel_peripheral_left << std::endl;
    }

    if (rightLeverHandler)
    {
        leftLeverHandler(msg.steeringwheel_peripheral_right);
        std::cout << "right: " << (bool)msg.steeringwheel_peripheral_right << std::endl;
    }

    if (driveStateHandler)
    {
        driveStateHandler(msg.shifter_state);
        std::cout << "driveState: " << (int)msg.shifter_state << std::endl;
    }

    if (shiftUpHandler)
    {
        if (msg.shifter_state == SHIFT_UP && m_lastDriveState != SHIFT_UP)
        {
            shiftUpHandler();
            std::cout << "shiftUp" << std::endl;
        }
    }

    if (shiftDownHandler)
    {
        if (msg.shifter_state == SHIFT_DOWN && m_lastDriveState != SHIFT_DOWN)
        {
            shiftDownHandler();
            std::cout << "shiftDown" << std::endl;
        }
    }

    m_lastDriveState = msg.shifter_state;
}

} // namespace sialib
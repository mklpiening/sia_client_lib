#ifndef SIALIB_HPP
#define SIALIB_HPP

#include <functional>

namespace sialib
{

enum driveState_t : uint8_t
{
    DRIVE      = 0, // Position D
    NEUTRAL    = 1, // Position N
    REVERSE    = 2, // Position R
    MANUAL     = 3, // Manual shifting mode
    SHIFT_UP   = 4, // Manual shift up
    SHIFT_DOWN = 5  // Manual shift down

};

#pragma pack(push, 1)
typedef struct ethernet_msg
{
    int32_t steeringwheel_angle;
    bool steeringwheel_peripheral_left;
    bool steeringwheel_peripheral_right;
    enum driveState_t shifter_state;
    uint8_t throttle;
    uint8_t brake;
} ethernet_msg_t, *Pethernet_msg_t; // Message type to send over ethernet
#pragma pack(pop)

class Sialib
{
  public:
    Sialib() {}
    ~Sialib() {}

    // event handlers
    std::function<void(int)> m_throttleHandler;
    std::function<void(int)> m_brakeHandler;

    std::function<void(int)> m_steeringWheelHandler;
    std::function<void(bool)> m_leftLeverHandler;
    std::function<void(bool)> m_rightLeverHandler;

    std::function<void(driveState_t)> m_driveStateHandler;
    std::function<void()> m_shiftUpHandler;
    std::function<void()> m_shiftDownHandler;
};

} // namespace sialib

#endif

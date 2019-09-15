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
    Sialib() : m_lastDriveState(NEUTRAL) {}
    ~Sialib() {}

    // event handlers
    std::function<void(int)> throttleHandler;
    std::function<void(int)> brakeHandler;

    std::function<void(int)> steeringWheelHandler;
    std::function<void(bool)> leftLeverHandler;
    std::function<void(bool)> rightLeverHandler;

    std::function<void(driveState_t)> driveStateHandler;
    std::function<void()> shiftUpHandler;
    std::function<void()> shiftDownHandler;

  protected:
    void handleMessage(ethernet_msg& msg);

  private:
    driveState_t m_lastDriveState;
};

} // namespace sialib

#endif

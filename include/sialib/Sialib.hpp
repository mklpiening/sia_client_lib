#ifndef SIALIB_HPP
#define SIALIB_HPP

#include <functional>

namespace sialib
{

/**
 * @brief state of the shifter
 */
enum DriveState : uint8_t
{
    DRIVE      = 0, // Position D
    NEUTRAL    = 1, // Position N
    REVERSE    = 2, // Position R
    MANUAL     = 3, // Manual shifting mode
    SHIFT_UP   = 4, // Manual shift up
    SHIFT_DOWN = 5  // Manual shift down

};

/**
 * @brief message that is being sent over uart or udp
 */
#pragma pack(push, 1)
struct SiaMsg
{
    int32_t steeringwheel_angle;
    bool steeringwheel_peripheral_left;
    bool steeringwheel_peripheral_right;
    enum DriveState shifter_state;
    uint8_t throttle;
    uint8_t brake;
    bool shifter_sport_button;
    bool shifter_park_button;
    bool shifter_left_button;
};
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

    std::function<void(DriveState)> driveStateHandler;
    std::function<void()> shiftUpHandler;
    std::function<void()> shiftDownHandler;

  protected:
    /**
     * @brief handles an incoming message and calls the handlers
     * 
     * @param msg incoming message to handle
     */
    void handleMessage(SiaMsg& msg);

  private:
    DriveState m_lastDriveState;
};

} // namespace sialib

#endif

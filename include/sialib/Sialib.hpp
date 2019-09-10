#ifndef SIALIB_HPP
#define SIALIB_HPP

#include <functional>

namespace sialib
{

enum driveState_t : int
{
    NEUTRAL = 0,
    DRIVE   = 1,
    REVERSE = 2
};

class Sialib
{
  public:
    Sialib();

    // event handlers
    std::function<void(int)> m_throttleHandler;
    std::function<void(int)> m_breakHandler;

    std::function<void(int)> m_steeringWheelHandler;
    std::function<void(bool)> m_leftLeverHandler;
    std::function<void(bool)> m_rightLeverHandler;

    std::function<void(driveState_t)> m_driveStateHandler;
    std::function<void()> m_shiftUpHandler;
    std::function<void()> m_shiftDownHandler;
};

} // namespace sialib

#endif

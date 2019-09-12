#include "sialib/SialibUart.hpp"

#include <boost/bind.hpp>
#include <iostream>

namespace sialib
{

SialibUart::SialibUart(std::string port, int baudRate) : m_io(), m_serial(m_io, port), m_nBytes(0), m_rcvOk(false)
{
    m_serial.set_option(boost::asio::serial_port_base::baud_rate(baudRate));

    readUart();

    boost::thread t(boost::bind(&boost::asio::io_service::run, &m_io));
    m_ioThread.swap(t);
}

void SialibUart::readUart()
{
    m_serial.async_read_some(boost::asio::buffer(m_receiveBuffer, 48),
                             boost::bind(&SialibUart::onMessageReceived,
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void SialibUart::onMessageReceived(const boost::system::error_code& error,
                                 std::size_t bytes_transferred)
{
    Pethernet_msg_t msg;

    for (int i = 0; i < bytes_transferred; i++)
    {
        if (!m_rcvOk) 
        {
            if (m_receiveBuffer[i] == ':')
            {
                m_rcvOk = true;
            }
        }
        else
        {
            if (m_nBytes >= sizeof(ethernet_msg_t))
            {
                break;
            }

            m_messageBuffer[m_nBytes] = m_receiveBuffer[i];
            m_nBytes++;
        }
    }   

    if (!error && m_nBytes >= sizeof(ethernet_msg_t))
    {
        msg = (Pethernet_msg_t) m_messageBuffer;

        m_nBytes = 0;
        m_rcvOk = false;

        if (m_leftLeverHandler)
        {
            m_leftLeverHandler(msg->steeringwheel_peripheral_left);
            std::cout << "left: " << (bool) msg->steeringwheel_peripheral_left << std::endl;
        }

        if (m_rightLeverHandler)
        {
            m_leftLeverHandler(msg->steeringwheel_peripheral_right);
            std::cout << "right: " << (bool) msg->steeringwheel_peripheral_right << std::endl;
        }

        if (m_brakeHandler)
        {
            m_brakeHandler(msg->brake);
            std::cout << "brake: " << (int) msg->brake << std::endl;
        }

        if (m_throttleHandler)
        {
            m_throttleHandler(msg->throttle);
            std::cout << "throttle: " << (int) msg->throttle << std::endl;
        }

        if (m_steeringWheelHandler)
        {
            m_steeringWheelHandler(msg->steeringwheel_angle);
            std::cout << "steeringWheel: " << (int) msg->steeringwheel_angle << std::endl;
        }

        if (m_driveStateHandler)
        {
            m_driveStateHandler(msg->shifter_state);
            std::cout << "driveState: " << (int) msg->shifter_state << std::endl;
        }
    }

    readUart();
}

} // namespace sialib

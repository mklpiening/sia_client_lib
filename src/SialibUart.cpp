#include "sialib/SialibUart.hpp"

#include <boost/bind.hpp>
#include <iostream>

namespace sialib
{

SialibUart::SialibUart(std::string port, int baudRate) : m_io(), m_serial(m_io, port)
{
    m_serial.set_option(boost::asio::serial_port_base::baud_rate(baudRate));

    readUart();

    boost::thread t(boost::bind(&boost::asio::io_service::run, &m_io));
    m_ioThread.swap(t);
}

void SialibUart::readUart()
{
    m_serial.async_read_some(boost::asio::buffer(m_receiveBuffer, 17),
                             boost::bind(&SialibUart::onMessageReceived,
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void SialibUart::onMessageReceived(const boost::system::error_code& error,
                                 std::size_t bytes_transferred)
{
    if (!error && bytes_transferred > 0)
    {
        if (bytes_transferred == 1)
        {
            if (m_receiveBuffer[0] == 'a')
            {
                if (m_leftLeverHandler)
                {
                    m_leftLeverHandler(true);
                    std::cout << "left lever: 1" << std::endl;
                }
            }
            else if (m_receiveBuffer[0] == 'b')
            {
                if (m_leftLeverHandler)
                {
                    m_leftLeverHandler(false);
                    std::cout << "left lever: 0" << std::endl;
                }
            }
            else if (m_receiveBuffer[0] == 'c')
            {
                if (m_rightLeverHandler)
                {
                    m_rightLeverHandler(true);
                    std::cout << "right lever: 1" << std::endl;
                }
            }
            else if (m_receiveBuffer[0] == 'd')
            {
                if (m_rightLeverHandler)
                {
                    m_rightLeverHandler(false);
                    std::cout << "right lever: 0" << std::endl;
                }
            }
        }
        else
        {
            m_receiveBuffer[bytes_transferred] = '\0';
            int angle = atoi((char*) m_receiveBuffer);

            if (m_steeringWheelHandler)
            {
                m_steeringWheelHandler(-angle);
                std::cout << "steering angle: " << angle << std::endl;
            }
        }
    }

    readUart();
}

} // namespace sialib

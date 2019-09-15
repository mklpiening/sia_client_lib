#include "sialib/SialibUart.hpp"

#include <boost/bind.hpp>

namespace sialib
{

SialibUart::SialibUart(std::string port, int baudRate)
    : m_io(), m_serial(m_io, port), m_nBytes(0), m_rcvOk(false)
{
    m_serial.set_option(boost::asio::serial_port_base::baud_rate(baudRate));

    readUart();

    boost::thread t(boost::bind(&boost::asio::io_service::run, &m_io));
    m_ioThread.swap(t);
}

void SialibUart::readUart()
{
    m_serial.async_read_some(boost::asio::buffer(m_receiveBuffer, 9),
                             boost::bind(&SialibUart::onMessageReceived,
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void SialibUart::onMessageReceived(const boost::system::error_code& error,
                                   std::size_t bytes_transferred)
{
    // wait for synchronizer and add all following bytes of the receive buffer to the message buffer
    for (int i = 0; i < bytes_transferred; i++)
    {
        if (!m_rcvOk)
        {
            if (m_receiveBuffer[i] == UART_SYNCHRONIZER_BYTE)
            {
                m_rcvOk = true;
            }
        }
        else
        {
            if (m_nBytes >= sizeof(SiaMsg))
            {
                break;
            }

            m_messageBuffer[m_nBytes] = m_receiveBuffer[i];
            m_nBytes++;
        }
    }

    // handle message if the message buffer is complete
    if (!error && m_nBytes >= sizeof(SiaMsg))
    {
        m_nBytes = 0;
        m_rcvOk  = false;

        SiaMsg* msg = (SiaMsg*)m_messageBuffer;
        handleMessage(*msg);
    }

    // receive the next uart message
    readUart();
}

} // namespace sialib

#ifndef SIALIB_UART_HPP
#define SIALIB_UART_HPP

#include "sialib/Sialib.hpp"

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace sialib
{

class SialibUart : public Sialib
{
  public:
    /**
     * @param port serial port to listen to
     * @param baudRate baud rate for uart communication
     */
    SialibUart(std::string port, int baudRate);

  private:
    /**
     * @brief readUart reads one uart message and calls onMessageReceived when the message got
     * received
     */
    void readUart();

    /**
     * @brief onMessageReceived gets called for each incoming uart message
     *
     * handles the incoming uart message and listenes to the next message
     *
     * @param error uart error
     * @param bytes_transferred amount of bytes that got transfered
     */
    void onMessageReceived(const boost::system::error_code& error, std::size_t bytes_transferred);

    boost::thread m_ioThread;
    boost::asio::io_service m_io;
    boost::asio::serial_port m_serial;

    uint8_t m_receiveBuffer[16];
};

} // namespace sialib

#endif

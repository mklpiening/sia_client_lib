#ifndef SIALIB_UART_HPP
#define SIALIB_UART_HPP

#include "sialib/Sialib.hpp"

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#define UART_SYNCHRONIZER_BYTE ':'

namespace sialib
{

class SialibUdp : public Sialib
{
  public:
    /**
     * @param port udp port to listen to
     */
    SialibUdp(int port);

  private:
    /**
     * @brief readUdp reads one udp packet
     */
    void readUdp();

    /**
     * @brief onMessageReceived gets called for each incoming udp message
     *
     * handles the incoming udp message and listenes to the next message
     *
     * @param error udp error
     * @param bytes_transferred amount of bytes that got transfered
     */
    void onMessageReceived(const boost::system::error_code& error, std::size_t bytes_transferred);

    boost::thread m_ioThread;
    boost::asio::io_service m_io;
    boost::asio::ip::udp::socket m_socket;

    boost::asio::ip::udp::endpoint m_remoteEndpoint;
    uint8_t m_receiveBuffer[sizeof(SiaMsg)];
};

} // namespace sialib

#endif

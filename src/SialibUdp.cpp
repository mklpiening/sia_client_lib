#include "sialib/SialibUdp.hpp"

#include <boost/bind.hpp>

namespace sialib
{

SialibUdp::SialibUdp(int port) : m_io(), m_socket(m_io)
{
    m_socket.open(boost::asio::ip::udp::v4());
    m_socket.bind(
        boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("0.0.0.0"), port));

    readUdp();
    boost::thread t(boost::bind(&boost::asio::io_service::run, &m_io));
    m_ioThread.swap(t);
}

void SialibUdp::readUdp()
{
    m_socket.async_receive_from(boost::asio::buffer(m_receiveBuffer),
                                m_remoteEndpoint,
                                boost::bind(&SialibUdp::onMessageReceived,
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
}

void SialibUdp::onMessageReceived(const boost::system::error_code& error,
                                  std::size_t bytes_transferred)
{
    // handle message if the message buffer is complete
    if (!error && bytes_transferred >= sizeof(SiaMsg))
    {
        SiaMsg* msg = (SiaMsg*)m_receiveBuffer;
        handleMessage(*msg);
    }

    // receive the next udp message
    readUdp();
}

} // namespace sialib

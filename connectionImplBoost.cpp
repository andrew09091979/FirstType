#include "connectionImplBoost.h"
void connect_handler(const boost::system::error_code & ec)
 {
    qDebug() << "connected";

}
ConnectionImplBoost::ConnectionImplBoost(const std::string& ip, unsigned short port, const ConnectionCallback *c)
    : ConnectionImpl(ip, port, c), bConnected(false)
{
    qDebug()<<"ConnectionImplBoost user ctor" << ip.c_str() << ":" << port;
    io_service_.reset(new boost::asio::io_service());
    socket_.reset(new tcp::socket(*io_service_));

}

int ConnectionImplBoost::connect_()
{
    qDebug()<<"ConnectionImplBoost::connect_";
    try
    {
//       boost::asio::ip::tcp::endpoint endpoint(
//                   boost::asio::ip::address::from_string(ConnectionImpl::ip_), ConnectionImpl::port_);
        boost::asio::ip::tcp::endpoint endpoint(
                    boost::asio::ip::address::from_string("81.19.70.1"), 80);
       socket_->async_connect(endpoint, boost::bind(&ConnectionImplBoost::handle_connect,
                                                    this, boost::asio::placeholders::error));
//        socket_->async_connect(endpoint, boost::bind(connect_handler,_1));
        io_service_->run();
       return 0;

    }
    catch (std::exception& e)
    {
       std::cerr << e.what() << std::endl;
       return 1;
    }
}

void ConnectionImplBoost::handle_connect(const boost::system::error_code& e)
{
       qDebug()<<"handle_connect";
  if (!e)
  {
    // Successfully established connection. Start operation to read the list
    // of stocks. The connection::async_read() function will automatically
    // decode the data that is read from the underlying socket.
//    ConnectionImplBoost.async_read(stocks_,
//        boost::bind(&ConnectionImplBoost::handle_read, this,
//          boost::asio::placeholders::error));
  }
  else
  {
    std::cerr << e.message() << std::endl;
  }
}

void ConnectionImplBoost::handle_read(const boost::system::error_code& e)
{
  if (!e)
  {
  }
  else
  {
  }
}

ConnectionImplBoost::RetType ConnectionImplBoost::getAnsver(int length)
{
    qDebug()<<"ConnectionImplBoost::getAnsver";
    BufferType * bfr = nullptr;
    std::auto_ptr< BufferType > res(bfr);
    bfr_.clear();
    if (bConnected)
    {
        bfr = new BufferType(50, ' ');
        res.reset(bfr);
        int low = 0; int high = 100;
        T randomValue = 0;
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        int i =0;
        for( i= 0; i< 50; ++i)
        {
            randomValue =  qrand() % ((high + 1) - low) + low;
            res->push_back(randomValue);
        }
    }
    else
    {
        if (connect_()==0)
            bConnected = true;
    }
    return res;
}

int ConnectionImplBoost::sendCommand(const QByteArray &)
{
    if (bConnected)
    {

    }
    else
    {
        if (connect_()==0)
            bConnected = true;
    }
    return 0;
}


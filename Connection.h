/*
 * Connection.h
 *
 *  Created on: Apr 3, 2018
 *      Author: bxn50
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <boost/asio.hpp>

class Connection
{
public:
    Connection(boost::asio::io_service& io_service): socket (io_service)
    {    }

    void readHandler();
    boost::asio::streambuf& getStrBuf() { return stream_buffer; }
    boost::asio::ip::tcp::socket& getSock() { return socket; }

private:
    void readRequest(const boost::system::error_code& ec, size_t);
    void respond(const std::string& s);
    void postWrite(const boost::system::error_code& ec, size_t );
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf stream_buffer;

    std::string response;
};

#endif /* CONNECTION_H_ */

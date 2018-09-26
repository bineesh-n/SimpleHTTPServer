
#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>

#include "Connection.h"

class HTTPServer {

public:
    HTTPServer(unsigned port = 80): _port(port),io_service(),
    acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("172.24.145.245"), _port)) {}
    void start();
private:
    void doAccept();
    void handleRequest(const boost::system::error_code& ec);

    unsigned _port;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor;

    std::vector<std::shared_ptr<Connection>> connections;
};


#include "Server.h"
#include <iostream>
#include <thread>

#define NUM_WORKER_THREADS 2

void HTTPServer::start()
{
   // boost::asio::ip::tcp::resolver resolver(io_service);
    // endpoint(boost::asio::ip::tcp::v4(), _port);

    //acceptor.open(endpoint.protocol());
    //acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    //acceptor.bind(endpoint);
    acceptor.listen();

    doAccept();
    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_WORKER_THREADS; ++i) {
        threads.push_back(std::thread(boost::bind(&boost::asio::io_service::run, &io_service)));
    }

    io_service.run();
}

void HTTPServer::doAccept()
{
    connections.push_back(std::make_shared<Connection>(io_service));
    acceptor.async_accept(connections[connections.size() - 1]->getSock(), boost::bind(&HTTPServer::handleRequest, this, boost::asio::placeholders::error));
}

void HTTPServer::handleRequest(const boost::system::error_code& ec)
{
    if (!ec)
    {
        std::cout << "Connected device " << connections[connections.size() - 1]->getSock().remote_endpoint().address().to_string() << std::endl;
        connections[connections.size() - 1]->readHandler();
        doAccept();
    }
    else
        std::cout << "Error occured. " << std::endl;

    //doAccept();
}

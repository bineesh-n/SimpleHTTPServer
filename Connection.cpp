/*
 * Connection.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: bxn50
 */

#include "Connection.h"
#include <iostream>
#include <boost/bind.hpp>
#include <fstream>
#include "Utility.h"

void Connection::readHandler()
{
    boost::asio::async_read_until(
                        socket,
                        stream_buffer,
                        '\n',   // null-char is a delimiter
                        boost::bind(&Connection::readRequest, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
}

void Connection::readRequest(const boost::system::error_code& ec, size_t bytes_tr)
{
    if (!ec)
    {
        std::istream is(&stream_buffer);
        std::string s;
        std::getline(is, s, '\n');
        std::cout << "Read:" << s << std::endl;
        if (s.find("GET") != std::string::npos)
        {
            respond(s);
        }
        readHandler();
    }
    else
    {
        std::cout << "Message read error. " << std::endl;
        socket.shutdown(boost::asio::socket_base::shutdown_both);
        socket.close();
    }
}

void Connection::postWrite(const boost::system::error_code& ec, size_t )
{
    if (!ec)
        std::cout << "We sent some data!" << std::endl;
    else
        std::cout << "Ohh... it fails again!!" << std::endl;
}

void Connection::respond(const std::string& s)
{
    std::string tmp = s.substr(s.find("GET") + 4);
    std::string req = tmp.substr(0, tmp.find(' '));
    response = "HTTP/1.1 200 OK\r\nServer: Honeycomb\r\nContent-Type: text/html";
    std::string message;
    if (req == "/team")
    {
        message = Utility::getContents("pages/team.html");
    }
    else if (Utility::stringStartsWith(req, "/submit") && req.length() > 10)
    {
        std::ofstream os ("data/data.txt", std::ios::app);
        os << req << std::endl;
        std::cout << req << std::endl;
        message = "<!DOCTYPE html><html><body>Submitted successfully.</body> </html>";
    }
    else
        return;

    response += "\r\nContent-Length: " + std::to_string(message.length()) + "\r\n\r\n" + message;
    //std::cout << "Sending: " << response << std::endl;
    boost::asio::async_write(
                socket,
                boost::asio::buffer(response.c_str(), response.size()+1),
                boost::bind(&Connection::postWrite, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

/*
 * Main.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: bxn50
 */
#include "Server.h"
#include <iostream>

int main()
{
    try{
        HTTPServer hs (8080);
        hs.start();
    } catch (...)
    {
        std::cout << "Exception " << std::endl;
    }
}



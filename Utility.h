/*
 * Utility.h
 *
 *  Created on: Feb 26, 2018
 *      Author: bxn50
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sstream>
#include <sys/types.h>
#include <vector>

/**
 * Some of the functions for general purpose
 */
class Utility
{
public:
    static std::string getWorkingDirectory();

    static std::string getContents(const std::string& fileName);
    static bool isNumber(const std::string& str_);
    static std::string getExecutablePath();
    static std::vector<std::string> split(const std::string str_, char c);
    static bool fileExists(const std::string& absPath_);

    static bool stringEndsWith(const std::string& theString_, const std::string& endsWithWhat_);
    static bool stringStartsWith(const std::string& theString_, const std::string& startsWithWhat_);
};


#endif /* UTILITY_H_ */

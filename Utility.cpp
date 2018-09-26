/*
 * Utility.cpp
 *
 *  Created on: Feb 26, 2018
 *      Author: bxn50
 */

#include "Utility.h"
#include "fstream"

std::string Utility::getWorkingDirectory()
{
    char cwd[1024] =
    { 0 };
    getcwd(cwd, sizeof(cwd));
    return std::string(cwd);
}

bool Utility::stringEndsWith(const std::string& theString_,
        const std::string& endsWithWhat_)
{
    int i, j;
    for (i = theString_.length() - 1, j = endsWithWhat_.length() - 1;
            i >= 0 && j >= 0; i--, j--)
    {
        if (theString_[i] != endsWithWhat_[j])
        {
            return false;
        }
    }
    if (j != -1)
        return false;

    return true;
}

bool Utility::stringStartsWith(const std::string& theString_,
        const std::string& startsWithWhat_)
{
    int i, j;
    for (i = 0, j = 0;
            i < theString_.length() && j < startsWithWhat_.length(); i++, j++)
    {
        if (theString_[i] != startsWithWhat_[j])
        {
            return false;
        }
    }
    if (j != startsWithWhat_.length())
        return false;

    return true;
}

std::string Utility::getContents(const std::string& fileName)
{
    std::ifstream input(fileName);
    //if (!input) {
    //    throw std::exception("Error opening file");
    //}
    std::stringstream sstr;
    while (input >> sstr.rdbuf())
        ;
    return sstr.str();
}

bool Utility::isNumber(const std::string& str_)
{
    for (unsigned i = 0; i < str_.length(); i++)
        if (!isdigit(str_[i]))
        {
            return false;
        }

    return true;
}

std::string Utility::getExecutablePath()
{
    char buf[1024];
    readlink("/proc/self/exe", buf, 1024);
    std::string s(buf);
    size_t pos;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if (s[i] == '/')
        {
            pos = i;
            break;
        }
    }

    s = s.substr(0, pos);
    return s;
}

std::vector<std::string> Utility::split(const std::string str_, char c)
{
    std::vector<std::string> ret;
    std::string temp = "";
    for (int i = 0; i < str_.length(); i++)
    {
        if (str_[i] == c)
        {
            ret.push_back(temp);
            temp = "";
        }
        else
        {
            temp += str_[i];
        }
    }

    if (temp != "")
        ret.push_back(temp);

    return ret;
}

bool Utility::fileExists(const std::string& absPath_)
{
    std::ifstream is(absPath_);
    if (!is)
        return false;

    return true;
}

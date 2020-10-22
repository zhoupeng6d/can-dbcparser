/*
 * @Date: 2020-10-22 19:24:15
 * @LastEditors: Dash Zhou
 * @LastEditTime: 2020-10-22 20:33:46
 */
/*
 * main.cpp
 *
 *  Created on: 04.10.2013
 *      Author: downtimes
 */

#include <iostream>
#include <stdexcept>

#include "header/dbciterator.hpp"

const std::string usage = ""
                          "This parser is meant to be used via CLI at the moment\n"
                          "	./parser <FILE>\n"
                          "	\n"
                          "example:\n"
                          "	./parser /home/downtimes/kit13.dbc\n";

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << usage << std::endl;
        return 0;
    }

    try
    {
        DBCIterator dbc(argv[1]);
        for (auto message : dbc)
        {
            std::cout << message.second.getName() << " " << message.second.getId() << std::endl;
            for (auto sig : message.second)
            {
                std::cout << "Signal: " << sig.second.getName() << "  ";
                std::cout << "To: ";
                for (auto to : sig.second.getTo())
                {
                    std::cout << to << ", ";
                }
                std::cout << sig.second.getStartbit() << "," << sig.second.getLength() << std::endl;
                std::cout << "(" << sig.second.getFactor() << ", " << sig.second.getOffset() << ")" << std::endl;
                std::cout << "[" << sig.second.getMinimum() << "," << sig.second.getMaximum() << "]" << std::endl;
                if (sig.second.getMultiplexor() == Multiplexor::MULTIPLEXED)
                {
                    std::cout << "#" << sig.second.getMultiplexedNumber() << "#" << std::endl;
                }
                else if (sig.second.getMultiplexor() == Multiplexor::MULTIPLEXOR)
                {
                    std::cout << "+Multiplexor+" << std::endl;
                }
                std::cout << std::endl;
            };
        }
    }
    catch (std::invalid_argument &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    //	return 0;
}

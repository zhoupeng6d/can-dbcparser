/*
 * @Date: 2020-10-22 19:24:15
 * @LastEditors: Dash Zhou
 * @LastEditTime: 2020-10-22 20:18:23
 */
/*
 * dbctree.cpp
 *
 *  Created on: 04.10.2013
 *      Author: downtimes
 */

#include "header/dbciterator.hpp"

#include <limits>
#include <fstream>
#include <stdexcept>
#include <unordered_map>

DBCIterator::DBCIterator(const std::string &filePath)
{
	std::ifstream file(filePath);
	if (file)
	{
		init(file);
	}
	else
	{
		throw std::invalid_argument("The File could not be opened");
	}
	file.close();
}

DBCIterator::DBCIterator(std::istream &stream)
{
	init(stream);
}

void DBCIterator::init(std::istream &stream)
{
	messageMap.clear();
	do
	{
		Message msg;
		stream >> msg;
		if (stream.fail())
		{
			stream.clear();
			stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			messageMap[msg.getId()] = msg;
		}
	} while (!stream.eof());
}

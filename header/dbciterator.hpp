/*
 * @Date: 2020-10-22 19:24:15
 * @LastEditors: Dash Zhou
 * @LastEditTime: 2020-10-22 20:23:37
 */
/*
 * dbctree.hpp
 *
 *  Created on: 04.10.2013
 *      Author: downtimes
 */

#ifndef DBCTREE_HPP_
#define DBCTREE_HPP_

#include <vector>
#include <iosfwd>
#include <unordered_map>
#include "message.hpp"

/**
 * This is the Top class of the dbclib and the interface to the user.
 * It enables its user to iterate over the Messages of a DBC-File
 */

class DBCIterator
{

	using MessageMap = std::unordered_map<MessageId, Message>;

	//This list contains all the messages which got parsed from the DBC-File
	MessageMap messageMap;

public:
	using const_iterator = MessageMap::const_iterator;

	//Constructors taking either a File or a Stream of a DBC-File
	explicit DBCIterator(const std::string &filePath);
	explicit DBCIterator(std::istream &stream);

	/*
	 * Functionality to access the Messages parsed from the File
	 * either via the iterators provided by begin() and end() or by
	 * random access operator[]
	 */
	const_iterator begin() const { return messageMap.begin(); }
	const_iterator end() const { return messageMap.end(); }
	Message operator[](MessageId id)
	{
		return messageMap[id];
	}

private:
	void init(std::istream &stream);
};

#endif /* DBCTREE_HPP_ */

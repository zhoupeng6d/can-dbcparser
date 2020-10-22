/*
 * @Date: 2020-10-22 19:24:15
 * @LastEditors: Dash Zhou
 * @LastEditTime: 2020-10-22 20:30:11
 */
/*
 * message.hpp
 *
 *  Created on: 04.10.2013
 *      Author: downtimes
 */

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <string>
#include <vector>
#include <iosfwd>
#include <cstdint>
#include <unordered_map>
#include <set>

#include "signal.hpp"

using MessageId = uint32_t;
/**
 * Class representing a Message in the DBC-File. It allows its user to query
 * Data and to iterate over the Signals contained in the Message
 */
class Message
{

	//typedef std::vector<Signal> signals_t;
	// signalName to signal
	using SignalMap = std::unordered_map<std::string, Signal>;
	//Name of the Message
	std::string name;
	//The CAN-ID assigned to this specific Message
	std::uint32_t id;
	//The length of this message in Bytes. Allowed values are between 0 and 8
	std::size_t dlc;
	//String containing the name of the Sender of this Message if one exists in the DB
	std::string from;
	//List containing all Signals which are present in this Message
	SignalMap signalMap;

public:
	//typedef signals_t::const_iterator const_iterator;
	using const_iterator = SignalMap::const_iterator;
	//Overload of operator>> to enable parsing of Messages from streams of DBC-Files
	friend std::istream &operator>>(std::istream &in, Message &msg);

	//Getter functions for all the possible Data one can request from a Message
	std::string getName() const { return name; }
	std::uint32_t getId() const { return id; }
	std::size_t getDlc() const { return dlc; }
	std::string getFrom() const { return from; }
	std::set<std::string> getTo() const;

	/*
	 * Functionality to access the Signals contained in this Message
	 * either via the iterators provided by begin() and end() or by
	 * random access operator[]
	 */
	const_iterator begin() const { return signalMap.begin(); }
	const_iterator end() const { return signalMap.end(); }
	Signal operator[](const std::string &signal_name)
	{
		return signalMap[signal_name];
	}
};

#endif /* MESSAGE_HPP_ */

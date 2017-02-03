#pragma once
#include "src/DebugSystem.h"
#include "src/TouchingButts.hpp"
#include <string>
/**
Handles LUA script calls to the DebugSystem.
*/
class LuaDebugSystemHandler {
public:
	/**
	Write to debug console window.
	*/
	static void writeToDebug(std::string str/**Debug message.*/);
	/**
	Write to a debug channel. The channel will be created if not there already
	*/
	static void writeToDebugChannel(std::string channel /**Channel to write to*/, std::string msg/**Message to be written*/);

	/**
	Set a file that can be outputted to
	*/
	static void createDebugFile(std::string filename/**Name of the file to write the debug to.*/);

	/**
	Add channel filter - default is everything
	*/
	static void addChannelFilter(std::string channel/**Channel filter to be added*/);

	/**
	Remove channel filter
	*/
	static void removeChannelFilter(std::string channel/**Channel filter to be removed*/);
};
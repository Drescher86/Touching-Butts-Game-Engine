#include "LuaDebugSystemHandler.h"

void LuaDebugSystemHandler::writeToDebug(std::string str)
{
	g_debugSystem->writeToDebug(str);
}

void LuaDebugSystemHandler::writeToDebugChannel(std::string channel, std::string msg)
{
	g_debugSystem->writeToDebugChannel(channel, msg);
}

void LuaDebugSystemHandler::createDebugFile(std::string filename)
{
	g_debugSystem->createDebugFile(filename);
}

void LuaDebugSystemHandler::addChannelFilter(std::string channel)
{
	g_debugSystem->addChannelFilter(channel);
}

void LuaDebugSystemHandler::removeChannelFilter(std::string channel)
{
	g_debugSystem->removeChannelFilter(channel);
}

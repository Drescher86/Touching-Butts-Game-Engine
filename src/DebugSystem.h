#pragma once

#include "EngineSystem.h"
#include <SDL.h>
#include <imgui.h>
#include <SRE/imgui_sre.hpp>
#include <memory>
#include "IEventListener.h"
#include "Scene.h"
#include <string>
#include <cstdarg>
#include <fstream>
#include <vector>


/**
Debug system for displaying debug info window. And writing to debug console.4
*/
class DebugSystem : public EngineSystem, public IEventListener
{
public:
	/**
	Write to current debug console window.
	*/
    void writeToDebug(std::string msg/**Message to be written.*/);

	/**
	Write to a debug channel. The channel will be created if not there already
	*/
	void writeToDebugChannel(std::string channel /**Channel to write to*/, std::string msg/**Message to be written*/);

	/**
	Set a file that can be outputted to
	*/
	void createDebugFile(std::string filename/**Name of the file to write the debug to.*/);

	/**
	Add channel filter - default is everything
	*/
	void addChannelFilter(std::string channel/**Channel filter to be added*/);

	/**
	Remove channel filter
	*/
	void removeChannelFilter(std::string channel/**Channel filter to be removed*/);

	/**
	Set SDL window to debug system.
	*/
	void setWindow(SDL_Window* window/**Game window.*/);

	void removeDebugWindow();

	DebugSystem();
	~DebugSystem();
protected:
	virtual bool init() override;
	virtual void postInit() override;
	virtual void shutdown() override;
	virtual void onEvent(BaseEventData ev) override;
	void update(float deltaTime, int physicsAlloc, int sceneAllocs, int particleAllocs, float physicsTimer, float sceneUpdateTimer, float renderTimer, float postRenderTimer);
	friend class TouchingButts;
private:
	void writeToFile(std::string timeString, std::string channel, std::string msg);
	
	SDL_Window* m_window;
	std::shared_ptr<Scene> m_currentScene;
	long m_peakMemoryUsage;
	bool m_isDebugWindowRunning;
	bool m_debugDrawOn;
	bool m_wasPaused;
	std::vector<std::string> m_channels;
	std::vector<std::string> m_channelFilter;
	std::ofstream m_outputFile;
};
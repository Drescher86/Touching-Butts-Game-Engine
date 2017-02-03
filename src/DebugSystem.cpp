#include "DebugSystem.h"
#include <iostream>
#include "windows.h";
#include "TouchingButts.hpp";
#include "DebugDraw.h";
#include "psapi.h"
#include <iomanip>
#include <ctime>

using namespace std;

void DebugSystem::writeToDebug(std::string msg)
{
#ifdef _DEBUG
	writeToDebugChannel("General", msg);
#endif
}

void DebugSystem::writeToDebugChannel(std::string channel, std::string msg)
{
#ifdef _DEBUG
	if (m_channelFilter.size() < 1) {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		cout << "[" << std::put_time(&tm, "%H:%M:%S") << "][" << channel << "]: " << msg << endl;
		if (m_outputFile.is_open()) {
			std::ostringstream oss;
			oss << std::put_time(&tm, "[%H:%M:%S]");
			auto time = oss.str();
			writeToFile(time, channel, msg);
		}
}
	else {
		for (int i = 0; i < m_channelFilter.size(); i++) {
			if (m_channelFilter[i] == channel)
			{
				auto t = std::time(nullptr);
				auto tm = *std::localtime(&t);
				cout << "[" << std::put_time(&tm, "%H:%M:%S") << "][" << channel <<"]: " << msg << endl;
				if (m_outputFile.is_open()) {
					std::ostringstream oss;
					oss << std::put_time(&tm, "[%H:%M:%S]");
					auto time = oss.str();
					writeToFile(time, channel, msg);
				}
				break;
			}
		}
	}
#endif
}

void DebugSystem::createDebugFile(std::string filename)
{
#ifdef _DEBUG
	if (m_outputFile.is_open())
	{
		m_outputFile.flush();
		m_outputFile.close();
	}
	m_outputFile.open(filename);
#endif
}

void DebugSystem::addChannelFilter(std::string channel)
{
#ifdef _DEBUG
	for (int i = 0; i < m_channelFilter.size(); i++) {
		if (m_channelFilter[i] == channel)
			return;
	}
	m_channelFilter.push_back(channel);
#endif
}

void DebugSystem::removeChannelFilter(std::string channel)
{
#ifdef _DEBUG
	int index = -1;
	for (int i = 0; i < m_channelFilter.size(); i++) {
		if (m_channelFilter[i] == channel) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		m_channelFilter.erase(m_channelFilter.begin() + index);
	}
#endif
}

void DebugSystem::setWindow(SDL_Window * window) {
	m_window = window;
}

void DebugSystem::removeDebugWindow(){
	m_isDebugWindowRunning = false;
}

bool DebugSystem::init() {
	m_isDebugWindowRunning = false;
	m_debugDrawOn = false;
	EngineSystem::init();
	initCheck();
	return true;
}

void DebugSystem::postInit() {
	g_eventSystem->listenToEventType(std::shared_ptr<IEventListener>(this), "toggleDebugWindow");
	DebugDraw* debugDraw = new DebugDraw();
	debugDraw->SetFlags(b2Draw::e_shapeBit);
	g_physicsSystem->getWorld()->SetDebugDraw(debugDraw);
	m_wasPaused = false;
}

void DebugSystem::shutdown()
{
	if (m_outputFile.is_open()) {
		m_outputFile.flush();
		m_outputFile.close();
	}
	EngineSystem::shutdown();
}

void DebugSystem::onEvent(BaseEventData ev) {
	if (m_isDebugWindowRunning) {
		
		m_isDebugWindowRunning = false;
	}
	else {
		
		m_isDebugWindowRunning = true;
	}
	
}

void DebugSystem::update(float deltaTime, int physicsAlloc, int sceneAllocs, int particleAllocs, float physicsTimer, 
						float sceneUpdateTimer, float renderTimer, float postRenderTimer) {
	initCheck();
	if (m_isDebugWindowRunning) {
		ImGui_SRE_NewFrame(m_window);
		ImGui::SetNextWindowFocus();
		ImGui::SetNextWindowPos(ImVec2(50, 50));
		{
			ImGui::GetIO();
			ImGui::BeginGroup();
			ImGui::Text("Memory");
			ImGui::Separator();

			PROCESS_MEMORY_COUNTERS pmc;
			GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
			long virtualMemUsedByMe = pmc.WorkingSetSize / 1024 / 1024;
			if (virtualMemUsedByMe > m_peakMemoryUsage) {
				m_peakMemoryUsage = virtualMemUsedByMe;
			}
			ImGui::Text("Current memory usage: %d MB", virtualMemUsedByMe);
			ImGui::Text("Peak memory usage: %d MB", m_peakMemoryUsage);
			ImGui::Text("Current allocations: %i", physicsAlloc + sceneAllocs + particleAllocs > 0 ? physicsAlloc + sceneAllocs + particleAllocs : 0);
			ImGui::Text("Current physics allocations: %i", physicsAlloc > 0 ? physicsAlloc : 0);
			ImGui::Text("Current scene allocations: %i", sceneAllocs > 0 ? sceneAllocs : 0);
			ImGui::Text("Current render allocations: %i", particleAllocs > 0 ? particleAllocs : 0);
			ImGui::EndGroup();
			ImGui::Separator();

			ImGui::BeginGroup();
			ImGui::Text("Timers");
			ImGui::Separator();
			ImGui::Text("Physics Timer: %.1f ms", physicsTimer * 1000);
			ImGui::Text("Update Timer: %.1f ms", sceneUpdateTimer * 1000);
			ImGui::Text("Render Timer: %.1f ms", renderTimer * 1000);
			ImGui::Text("Post Render Update Timer: %.1f ms", postRenderTimer * 1000);
			ImGui::EndGroup();
			ImGui::Separator();
			
			ImGui::BeginGroup();
			ImGui::Text("Scene elements");
			ImGui::Separator();
			if (g_sceneSystem->getCurrentScene() != nullptr) {
				ImGui::Text("Game objects: %i", g_sceneSystem->getCurrentScene()->getSize());
			}
			ImGui::EndGroup();
			ImGui::BeginGroup();
			ImGui::Text("Performance");
			ImGui::Separator();
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::EndGroup();
			ImGui::Separator();
			ImGui::Text("Functions");
			ImGui::BeginGroup();
			ImGui::Separator();
			ImGui::Checkbox("Debug draw", &m_debugDrawOn);
			bool pauseGameLogic = m_wasPaused;
			ImGui::Checkbox("Pause game logic", &pauseGameLogic);
			if (m_wasPaused != pauseGameLogic) {
				g_eventSystem->fireEvent(BaseEventData("togglepause"));
				m_wasPaused = pauseGameLogic;
			}
			ImGui::EndGroup();
		}
		if (m_debugDrawOn) {
			g_physicsSystem->getWorld()->DrawDebugData();
		}
		ImGui::Render();
	}
}

void DebugSystem::writeToFile(std::string timeString, std::string channel, std::string msg) {
	m_outputFile << timeString << "[" << channel << "]: " << msg << endl;
	m_outputFile.flush();
}

DebugSystem::DebugSystem()
{
	//Do nothing!
}

DebugSystem::~DebugSystem()
{
	//Do nothing!
}

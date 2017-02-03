#include <SRE/Shader.hpp>
#include "TouchingButts.hpp"
#include "SDL.h"
#include "glm/gtc/matrix_transform.hpp"
#include "SRE/Debug.hpp"
#include "SRE/Texture.hpp"
#include "DebugDraw.h"
#include <iostream>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/closest_point.hpp>
#include <time.h>       /* time */
#include "Components/TransformComponent.h"
#include "Components/Box2DColliderComponent.h"
#include "Components/ScriptableComponent.h"
#include <new>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#define SDL_MAIN_HANDLED
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "SDL.h"
#include "SRE/SimpleRenderEngine.hpp"


extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }


using namespace glm;
using namespace SRE;

PhysicsSystem* g_physicsSystem = new PhysicsSystem();
ParticleSystem* g_particleSystem = new ParticleSystem();
DebugSystem* g_debugSystem = new DebugSystem();
EventSystem* g_eventSystem = new EventSystem();
InputSystem* g_inputSystem = new InputSystem();
SpriteSystem* g_spriteSystem = new SpriteSystem();
DrawingSystem* g_drawingSystem = new DrawingSystem();
SceneSystem* g_sceneSystem = new SceneSystem();
ScriptingSystem* g_scriptingSystem = new ScriptingSystem();
SDL_Window* g_window;

Vector2 g_windowSize(0,0);

int number_of_allocs = 0;
int number_of_deallocs = 0;

void* operator new(std::size_t size) throw(std::bad_alloc) {
	++number_of_allocs;
	void *p = malloc(size);
	if (!p) throw std::bad_alloc();
	return p;
}

void* operator new  [](std::size_t size) throw(std::bad_alloc) {
	++number_of_allocs;
	void *p = malloc(size);
	if (!p) throw std::bad_alloc();
	return p;
}

void* operator new  [](std::size_t size, const std::nothrow_t&) throw() {
	++number_of_allocs;
	return malloc(size);
}
void* operator new   (std::size_t size, const std::nothrow_t&) throw() {
	++number_of_allocs;
	return malloc(size);
}


void operator delete(void* ptr) throw() { free(ptr); ++number_of_deallocs; }
void operator delete (void* ptr, const std::nothrow_t&) throw() { free(ptr); ++number_of_deallocs;
}
void operator delete[](void* ptr) throw() { free(ptr);  ++number_of_deallocs; }
void operator delete[](void* ptr, const std::nothrow_t&) throw() { free(ptr);  ++number_of_deallocs; }



TouchingButts::TouchingButts(int width, int height, TouchingButtsGame * game, string gameName) {
	m_width = width;
	m_height = height;
	m_updateTimer = 0;
	
	g_windowSize = Vector2(m_width, m_height);

	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	
	
	// Create an application window with the following settings:
	g_window = SDL_CreateWindow(
		gameName.c_str(),                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		m_width,               // width, in pixels
		m_height,              // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);
	// Check that the window was successfully made
	if (g_window == NULL) {
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
	}
	m_sre = new SRE::SimpleRenderEngine{ g_window };

	initializeEngineSystems();
	
	setupEngineValues();
	g_windowSize = Vector2(m_width, m_height);
	SDL_SetWindowSize(g_window, m_width, m_height);
	SDL_SetWindowFullscreen(g_window, m_fullsize ? SDL_WINDOW_FULLSCREEN : 0);
	
	//Disable VSYNC
	int success = SDL_GL_SetSwapInterval(0);

	m_game = game;
	postInitializeEngineSystems();
}

TouchingButts::~TouchingButts() {
	g_particleSystem->shutdown();
	g_physicsSystem->shutdown();
	g_eventSystem->shutdown();
	g_inputSystem->shutdown();
	g_debugSystem->shutdown();
}

void TouchingButts::startGameLoop() {
    // delta time from http://gamedev.stackexchange.com/a/110831
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    m_quit = 0;
    float deltaTimeSec = 0;
	m_fixedTimeStep = 0;
	ImGui_SRE_Init(g_window);
	float updateTimer = 0;
	int i = 0;
    while (m_quit == 0){
		g_sceneSystem->performUpdates();
		int start(number_of_allocs);
		int end = 0;
		
		int pStart = 0;
		int pEnd = 0;
		int sStart = 0;
		int sEnd = 0;
		int paStart = 0;
		int paEnd = 0;
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

		

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);
		updateEngineValues(deltaTimeSec);
		
		if (m_isPaused)
			deltaTimeSec = 0;
        
		
		m_fixedTimeStep += deltaTimeSec;
		float physicsTimer = 0.f;
		clock_t t;
		if (m_fixedTimeStep >= 1 / 60.f)
		{
			pStart = number_of_allocs;
			t = clock();
			fixedTimeStep();
			t = clock() - t;
			physicsTimer = ((float)t) / CLOCKS_PER_SEC;
			m_fixedTimeStep = 0;
			pEnd = number_of_allocs;

		}
		sStart = number_of_allocs;
		t = clock();
		update(deltaTimeSec);
		t = clock() - t;
		sEnd = number_of_allocs;
		float updateTimer = ((float)t) / CLOCKS_PER_SEC;

		preRenderUpdate();
		paStart = number_of_allocs;
		t = clock();
		g_drawingSystem->begin();
		render();
		g_drawingSystem->end();
		t = clock() - t;
		paEnd = number_of_allocs;
		float renderTimer = ((float)t) / CLOCKS_PER_SEC;
		t = clock();
		postRenderUpdate();
		t = clock() - t;
		float postRenderTimer = ((float)t) / CLOCKS_PER_SEC;

		m_quit = m_game->update(deltaTimeSec) ? 0 : 1;

		end = number_of_deallocs;
		int diff = start - end;
		g_debugSystem->update(deltaTimeSec, pEnd - pStart, sEnd - sStart, paEnd - paStart, physicsTimer, updateTimer, renderTimer, postRenderTimer);
		m_sre->swapWindow();
		
    }
	ImGui_SRE_Shutdown();
	// Close and destroy the window
	SDL_DestroyWindow(g_window);

	// Clean up
	SDL_Quit();

}

void TouchingButts::onEvent(BaseEventData eventData) {
	m_isPaused = !m_isPaused;
}
void TouchingButts::initializeEngineSystems() {
	if (g_debugSystem->init()) {
		g_debugSystem->writeToDebug("Debug System Initialized");
	}
	if (g_inputSystem->init()) {
		g_debugSystem->writeToDebug("Input System Initialized");
	}
	if (g_eventSystem->init()) {
		g_debugSystem->writeToDebug("Event System Initialized");
		std::shared_ptr<IEventListener> sharedThis(this);
		g_eventSystem->listenToEventType(sharedThis, "togglepause");
	}
	if (g_physicsSystem->init()) {
		g_debugSystem->writeToDebug("Physics System Initialized");
	}
	if (g_particleSystem->init()) {
		g_debugSystem->writeToDebug("Particle System Initialized");
		g_particleSystem->setSize(512);
	}
	if (g_drawingSystem->init()) {
		g_debugSystem->writeToDebug("Drawing System Initialized");
	}
	if (g_spriteSystem->init()) {
		g_debugSystem->writeToDebug("Sprite System Initialized");
	}
	if (g_sceneSystem->init()) {
		g_debugSystem->writeToDebug("Scene System Initialized");
	}
	if (g_scriptingSystem->init()) {
		g_debugSystem->writeToDebug("Scripting System Initialized");
	}
}

void TouchingButts::postInitializeEngineSystems() {
	
	g_debugSystem->setWindow(g_window);
	m_isPaused = false;
	g_debugSystem->postInit();
	m_game->init();
}

void TouchingButts::fixedTimeStep() {
	prePhysicsUpdate();
	g_physicsSystem->update(1/60.f);
	postPhysicsUpdate();
}

void TouchingButts::prePhysicsUpdate()
{
	g_sceneSystem->prePhysicsUpdate();
}

void TouchingButts::preRenderUpdate() {
	g_sceneSystem->preRenderUpdate();
}

void TouchingButts::update(float deltaTime) {
	g_sceneSystem->updateCurrentScene(deltaTime);
	g_particleSystem->update(deltaTime);
	g_inputSystem->handleInput();
}

void TouchingButts::render() {
	m_sre->clearScreen(vec4(0.3f, 0.3f, 0.3f, 1));
	g_sceneSystem->renderCurrentScene();
	g_particleSystem->render();
}

void TouchingButts::postRenderUpdate() {
	g_sceneSystem->postRenderUpdate();
}

void TouchingButts::postPhysicsUpdate()  {
	g_sceneSystem->postPhysicsUpdate();
}

void TouchingButts::setupEngineValues()
{
	const char * valueFile = "tbvalues.lua";
	auto L = g_scriptingSystem->getState();
	if (luaL_dofile(L, valueFile) == 0) //succeeded
	{
		lua_pcall(L, 0, 0, 0);
		auto window = luabridge::getGlobal(L, "window");
		if (window.isTable()) {
			auto fullsize = window["fullsize"];
			if (fullsize.isString()) {
				if (fullsize.cast<std::string>() == "true")
				{
					m_fullsize = true;
				}
				else
					m_fullsize = false;
			}
			else
				m_fullsize = false;
			auto width = window["width"];
			if (width.isNumber()) {
				m_width = width.cast<int>();
			}
			auto height = window["height"];
			if (height.isNumber()) {
				m_height = height.cast<int>();
			}
		}
		else {
			m_fullsize = false;
		}
		auto debug = luabridge::getGlobal(L, "debug");
		if (debug.isTable())
		{
			auto updateLuaOnTheFly = debug["enableLuaOnTheFly"];
			if (updateLuaOnTheFly.isString()) {
				if (updateLuaOnTheFly.cast<std::string>() == "true")
				{
					g_scriptingSystem->m_luaOnTheFlyEnabled = true;
					auto updateTime = debug["luaUpdateTime"];
					if (updateTime.isNumber()) {
						g_scriptingSystem->m_luaOnTheFlyUpdateTimer = updateTime.cast<float>();
					}
				}
				else
					g_scriptingSystem->m_luaOnTheFlyEnabled = false;

			}
			auto debugDraw = debug["enableDebugDraw"];
			if (debugDraw.isString()) {
				if (debugDraw.cast<std::string>() == "true")
				{
					g_debugSystem->m_debugDrawOn = true;
				}
				else
					g_debugSystem->m_debugDrawOn = false;
			}
			else
				g_debugSystem->m_debugDrawOn = false;
		}
		else {
			g_debugSystem->m_debugDrawOn = false;
			g_scriptingSystem->m_luaOnTheFlyEnabled = false;
		}
	}
	else {
		g_debugSystem->m_debugDrawOn = false;
		m_fullsize = false;
		g_scriptingSystem->m_luaOnTheFlyEnabled = false;
	}
}

void TouchingButts::updateEngineValues(float deltaTime)
{
	if (g_scriptingSystem->isLuaOnTheFlyEnabled()) {
		m_updateTimer += deltaTime;
		if (g_scriptingSystem->getLuaUpdateTimer() <= m_updateTimer) {
			auto width = m_width;
			auto height = m_height;
			auto fullsize = m_fullsize;
			setupEngineValues();
			if (width != m_width)
			{
				SDL_SetWindowSize(g_window, m_width, m_height);
				g_windowSize = Vector2(m_width, m_height);
			}
			else if (height != m_height) {
				SDL_SetWindowSize(g_window, m_width, m_height);
				g_windowSize = Vector2(m_width, m_height);
			}
			if (fullsize != m_fullsize) {
				if (m_fullsize) {
					SDL_SetWindowFullscreen(g_window, SDL_WINDOW_FULLSCREEN);
				}
				else {
					SDL_SetWindowFullscreen(g_window, 0);
				}

			}
		}
	}
}


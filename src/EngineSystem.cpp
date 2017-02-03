#include "EngineSystem.h"
#include <assert.h>

EngineSystem::EngineSystem()
{
	//Do nothing!
}

bool EngineSystem::init() {
	m_initialized = true;
	return true;
}

void EngineSystem::shutdown()
{
	m_initialized = false;
}

EngineSystem::~EngineSystem()
{
	//Do nothing!
}

void EngineSystem::initCheck()
{
	//Write to debug log etc. Right now we just assert.

	assert(m_initialized);
}


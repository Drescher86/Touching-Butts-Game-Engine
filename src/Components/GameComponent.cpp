#include "GameComponent.h"

void GameComponent::render()
{
}

void GameComponent::update(float deltaTime)
{
}

void GameComponent::preRenderUpdate()
{
}

void GameComponent::prePhysicsUpdate()
{
}

void GameComponent::postRenderUpdate()
{
}

void GameComponent::postPhysicsUpdate()
{
}

void GameComponent::postInit()
{
}

int GameComponent::getId()
{
	return m_componentId; 
}

GameComponent::GameComponent(GameObject *gameObject)
	:gameObject(gameObject), m_componentId(nextComponentId++)
{
}

void GameComponent::onRemove()
{
}

GameComponent::~GameComponent() {
}

GameObject *GameComponent::getGameObject() {
	return gameObject;
}
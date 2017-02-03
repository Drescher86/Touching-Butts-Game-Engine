#pragma once
#include <cstdint>

class GameObject;

static int nextComponentId;
/**
Base game component.
*/
class GameComponent {
public:
	virtual ~GameComponent();
	/**
	Get the game object the component is attached to.
	*/
	GameObject* getGameObject();
	/**
	Get component ID.
	*/
	int getId();
protected:
	virtual void render();
	virtual void update(float deltaTime);
	virtual void preRenderUpdate();
	virtual void prePhysicsUpdate();
	virtual void postRenderUpdate();
	virtual void postPhysicsUpdate();

	virtual void postInit();
	GameComponent(GameObject *gameObject);
	GameObject *gameObject;
	int m_componentId;
	virtual void onRemove();
	friend class GameObject;
};
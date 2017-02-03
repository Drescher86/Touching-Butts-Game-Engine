#pragma once
#include "GameComponent.h"
#include "src/GameObject.h"
#include "src/Sprite.h"
#include <map>
#include <string>
/**
Animation 2D component. Used for animated objects in 2D space.
*/
class Animation2DComponent: public GameComponent{
public:
	/**
	Set animation speed. Defaults to 
	*/
	void setAnimationSpeed(float animationSpeed/**Animation speed in seconds.*/);
	/**
	Play animation by name if added.
	*/
	void playAnimation(std::string name/**Name of animation.*/);
	/**
	Add animation by name if exists.
	*/
	void addAnimation(std::string name/**Name of animation.*/);

	/**
	Get the width of the sprite
	*/
	int width();
	/**
	Get the height of the sprite
	*/
	int height();
	/**
	Set sorting order,
	*/
	void setSortingOrder(int order);
	std::shared_ptr<SRE::Mesh> getMesh();
protected:
	Animation2DComponent(GameObject * gameObject);
	void update(float deltaTime) override;
	void render() override;
private:
	float m_timer;
	int m_frameCount;
	int m_frameCounter;
	float m_animationSpeed;
	int m_sortingOrder;
	std::string m_activeAnimation;
	std::map<std::string, std::shared_ptr<Sprite>> m_spriteMap;
	friend class GameObject;
};

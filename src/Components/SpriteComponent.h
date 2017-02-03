#pragma once

#include "GameComponent.h"
#include "src/Sprite.h"
#include "src/GameObject.h"
#include <memory>
#include <SRE/Mesh.hpp>
/**
Sprite component, used to represent a 2D game object in game.
*/
class SpriteComponent : public GameComponent {
public:
	/**
	Get width of sprite.
	*/
	int width();
	/**
	Get height of sprite.
	*/
	int height();
	/**
	Get mesh of sprite.
	*/
	std::shared_ptr<SRE::Mesh> getMesh();
	/**
	Set sprite from name.
	*/
	void setSpriteFromName(std::string name/**Name of sprite.*/);
	/**
	Set sprite.
	*/
	void setSprite(std::shared_ptr<Sprite> sprite/**Shared pointer of the sprite to set.*/);
	/**
	Set sorting order
	*/
	void setSortingOrder(int order);
protected:
	void render() override;
	SpriteComponent(GameObject * gameObject);
private:
	std::shared_ptr<Sprite> m_sprite;
	int m_sortingOrder = 1;

	friend class GameObject;
};
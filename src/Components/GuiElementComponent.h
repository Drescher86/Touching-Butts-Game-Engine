#pragma once
#include "GameComponent.h"
#include "src/GameObject.h"
#include "TransformComponent.h"
#include <memory>
#include "src/Sprite.h"
/**
Gui Element base class.
*/
class GuiElementComponent : public GameComponent {
public:
	/**
	Set if Element is to follow camera. Default true.
	*/
	void setFollowCamera(bool followCamera/**Boolean whether to follow camera or not.*/);
	/**
	Set sprite by name.
	*/
	void setSprite(std::string name/**Name of sprite.*/);
protected:
	virtual void render() override;
	virtual void update(float deltaTime) override = 0;
	bool m_followCamera = true;
	std::shared_ptr<TransformComponent> m_transform;
	GuiElementComponent(GameObject *gameObject);
	std::shared_ptr<Sprite> m_sprite;
private:
	friend class GameObject;
};
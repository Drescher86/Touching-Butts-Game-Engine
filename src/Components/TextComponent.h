#pragma once
#include "GameComponent.h"
#include "GuiElementComponent.h"
#include "SRE/Mesh.hpp"
#include <memory>
#include <string>
#include "src/GameObject.h"
/**
Text component used to display text in the game.
*/
class TextComponent : public GuiElementComponent {
public:
	/**
	Set the text.
	*/
	void setText(std::string text/**Text to be displayed.*/);
protected:
	void update(float deltaTime) override {};
	void render() override;
	TextComponent(GameObject * gameObject);
private:
	friend class GameObject;
	std::shared_ptr<TransformComponent> m_transform;
	std::string m_text;
};
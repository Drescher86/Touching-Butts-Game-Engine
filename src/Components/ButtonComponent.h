#pragma once
#include "GuiElementComponent.h"
#include "src/GameObject.h"
#include "LuaBridge.h"
#include <functional>
/**
Button component.
*/
class ButtonComponent : public GuiElementComponent {
public:
	/**
	On click event.
	*/
	std::function<void()> onClick;
protected:
	ButtonComponent(GameObject* gameObject);
	void update(float deltaTime) override;
private:
	bool withinBoundaries();
	friend class GameObject;
};
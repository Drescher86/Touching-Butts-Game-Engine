#pragma once
#include "src/EngineSystem.h"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "Sprite.h"
#include <map>
/**
Drawing system responsible for batching 2D elements.
*/
class DrawingSystem : public EngineSystem {
public:
	/**
	Batch drawing call for drawing sprite.
	*/
	void draw(std::shared_ptr<Sprite> sprite/**Pointer to sprite.*/, glm::mat4 transform/**Transform of where sprite is to be drawn.*/, int frame = 0/**Frame to be drawn. Defaults to 0.*/, int sorting = 1);
	/**
	Batch drawing call for drawing UI elements.
	*/
	void drawUI(std::shared_ptr<Sprite> sprite/**Pointer to sprite.*/, glm::mat4 transform/**Transform of where sprite is to be drawn.*/, int frame = 0/**Frame to be drawn. Defaults to 0.*/);
	/**
	Batch drawing call for drawing text.
	*/
	void drawText(std::string text/**Text to be drawn.*/, glm::vec2 position/**Screen position to be drawn at.*/);
	
	DrawingSystem();
	~DrawingSystem();
protected:
	virtual bool init() override;
	virtual void postInit() override;
	virtual void shutdown() override;
	friend class TouchingButts;
private:
	void begin();
	void end();
	std::map<int, std::map<std::shared_ptr<Sprite>, std::vector<std::pair<int, glm::mat4>>>> m_spriteMap;
	std::map<std::shared_ptr<Sprite>, std::vector<std::pair<int, glm::mat4>>> m_uiMap;
	std::map<std::string, std::vector<glm::vec2>> m_textMap;
	bool m_begun;
	SRE::Shader * m_shader;

	friend class TouchingButts;
};

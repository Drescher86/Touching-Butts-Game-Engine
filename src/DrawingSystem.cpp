#include "DrawingSystem.h"
#include "SRE/SimpleRenderEngine.hpp"
#include <glm/gtx/transform.hpp>
#include "TouchingButts.hpp"
#include <imgui.h>
#include <SRE/imgui_sre.hpp>

void DrawingSystem::draw(std::shared_ptr<Sprite> sprite, glm::mat4 transform, int frame, int sorting)
{
	assert(m_begun && "Draw has not begun");
	auto pair = std::pair<int, glm::mat4>(frame, transform);
	auto map = m_spriteMap.find(sorting);
	if (map != m_spriteMap.end()) {
		auto sprit = map->second.find(sprite);
		if (sprit != map->second.end()) {
			sprit->second.push_back(pair);
		}
		else {
			auto vec = std::vector<std::pair<int, glm::mat4>>();
			vec.push_back(pair);
			map->second.insert(std::pair<std::shared_ptr<Sprite>, std::vector<std::pair<int, glm::mat4>>>(sprite, vec));
		}
	}
	else {
		auto vec = std::vector<std::pair<int, glm::mat4>>();
		vec.push_back(pair);
		auto ma = std::map<std::shared_ptr<Sprite>, std::vector<std::pair<int, glm::mat4>>>();
		ma.insert(std::pair<std::shared_ptr<Sprite>, std::vector<std::pair<int, glm::mat4>>>(sprite, vec));
		auto pa = std::pair<int, std::map<std::shared_ptr<Sprite>, std::vector<std::pair<int, glm::mat4>>>>(sorting, ma);
		m_spriteMap.insert(pa);
	}

}

void DrawingSystem::drawUI(std::shared_ptr<Sprite> sprite, glm::mat4 transform, int frame)
{
	assert(m_begun && "Draw has not begun");
	auto pair = std::pair<int, glm::mat4>(frame, transform);
	m_uiMap[sprite].push_back(pair);
}

void DrawingSystem::drawText(std::string text, glm::vec2 position)
{
	assert(m_begun && "Draw has not begun");
	m_textMap[text].push_back(position);
}


void DrawingSystem::begin()
{
	auto spriteIt = m_spriteMap.begin();
	for (; spriteIt != m_spriteMap.end(); spriteIt++) {
		auto innerIt = spriteIt->second.begin();
		for (; innerIt != spriteIt->second.end(); innerIt++) {
			innerIt->second.clear();
		}
		spriteIt->second.clear();
	}
	m_spriteMap.clear();
	auto uiIt = m_uiMap.begin();
	for (; uiIt != m_uiMap.end(); uiIt++) {
		uiIt->second.clear();
	}
	m_uiMap.clear();
	m_textMap.clear();
	m_begun = true;
}

void DrawingSystem::end()
{
	auto spriteIt = m_spriteMap.begin();
	for (; spriteIt != m_spriteMap.end(); spriteIt++) {
		auto inner = spriteIt->second.begin();
		for (; inner != spriteIt->second.end(); inner++) {
			m_shader->setTexture("tex", inner->first->getTexture().get());
			auto transIt = inner->second.begin();
			for (; transIt != inner->second.end(); transIt++) {
				auto m = inner->first->getMesh(transIt->first).get();
				SRE::SimpleRenderEngine::instance->draw(m, transIt->second, m_shader);
			}
		}
	}

	auto uiIt = m_uiMap.begin();
	for (; uiIt != m_uiMap.end(); uiIt++) {
		m_shader->setTexture("tex", uiIt->first->getTexture().get());
		auto transUiIt = uiIt->second.begin();
		for (; transUiIt != uiIt->second.end(); transUiIt++) {
			SRE::SimpleRenderEngine::instance->draw(uiIt->first->getMesh(transUiIt->first).get(), transUiIt->second, m_shader);
		}
	}
	if (m_textMap.size() > 0) {
		
		auto textIt = m_textMap.begin();
		for (; textIt != m_textMap.end(); textIt++) {
			auto vecIt = textIt->second.begin();
			for (; vecIt != textIt->second.end(); vecIt++) {
				bool open = true;
				ImGui_SRE_NewFrame(g_window);
				
				auto vx = vecIt->x + 5;
				auto vy = g_windowSize.y() - (vecIt->y + 5) - 0.05555f * g_windowSize.y(); //magic number to offset text correctly according to window height
				ImGui::SetNextWindowSize(ImVec2(textIt->first.size()*15, 10));
				ImGui::SetNextWindowPos(ImVec2(vx, vy));
				ImGui::Begin("", &open, ImVec2(textIt->first.size() * 15, 10), 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
				ImGui::TextColored(ImVec4(0,0,0,1), textIt->first.c_str());
				ImGui::End();
				ImGui::Render();
			}
		}
	}
	m_begun = false;
}

bool DrawingSystem::init() {
	EngineSystem::init();
	m_begun = false;
	m_shader = SRE::Shader::getUnlitSprite();
	initCheck();
	return true;
}

void DrawingSystem::postInit()
{
}

void DrawingSystem::shutdown()
{
	EngineSystem::shutdown();
}

DrawingSystem::DrawingSystem()
{
	//  Do nothing!
}

DrawingSystem::~DrawingSystem()
{
	//  Do nothing!
}
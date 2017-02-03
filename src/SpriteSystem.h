#pragma once

#include <vector>
#include <memory>
#include "Sprite.h"
#include "SRE/Texture.hpp"
#include "EngineSystem.h"
#include <map>
/**
Sprite system loads and creates sprites from json and holds all references to loaded sprites.
*/
class SpriteSystem : EngineSystem {
public:
	/**
	Get a loaded sprite by name. Returns nullptr if not found.
	*/
	std::shared_ptr<Sprite> getSprite(std::string name);
	/**
	Load sprites from a json file.
	*/
	void loadJsonFile(std::string dataDir /**Path to json file. */, std::string jsonDataFile /** Name of json file with extension.*/);
	
	SpriteSystem();
	~SpriteSystem();
protected:
	virtual bool init() override;
	virtual void postInit() override;
	virtual void shutdown() override;
	friend class TouchingButts;
private:
	 std::map<std::string,std::shared_ptr<Sprite>> m_spriteMap;
};
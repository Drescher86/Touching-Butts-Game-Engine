#include "SpriteSystem.h"
#include <memory>
#include "SRE/Texture.hpp"
#include "SpriteSystem.h"
#include "picojson.h"
#include <fstream>

std::shared_ptr<Sprite> SpriteSystem::getSprite(std::string name)
{
	return m_spriteMap.at(name);
}

void SpriteSystem::loadJsonFile(std::string dataDir, std::string jsonDataFile)
{
	picojson::value jsonFile;
	std::string relativePath = dataDir + "/" + jsonDataFile;
	std::ifstream stream(relativePath);
	stream >> jsonFile;

	std::string err = picojson::get_last_error();
	if (err != "") {
		std::cout << err << std::endl;
		return;
	}

	std::string textureFileName = jsonFile.get("meta").get("image").get<std::string>();

	SRE::Texture* texture = SRE::Texture::createFromFile((dataDir + "/" + textureFileName).c_str(), false);
	std::shared_ptr<SRE::Texture> sharedTex(texture);

	int textureHeight = texture->getHeight();
	int textureWidth = texture->getWidth();

	int numberOfObjects = jsonFile.get("frames").get<picojson::array>().size();

	for (int i = 0; i < numberOfObjects; i++) {
		picojson::value currentObject = jsonFile.get("frames").get<picojson::array>()[i];
		std::string name = currentObject.get("filename").get<std::string>();
		int x = currentObject.get("frame").get("x").get<double>();
		int y = currentObject.get("frame").get("y").get<double>();
		int width = currentObject.get("frame").get("w").get<double>();
		int height = currentObject.get("frame").get("h").get<double>();
		float anchorX = currentObject.get("pivot").get("x").get<double>();
		float anchorY = currentObject.get("pivot").get("y").get<double>();
		int frameCounter = 0;
		bool animation = false;
		if (currentObject.contains("frameCount")) {
			frameCounter = currentObject.get("frameCount").get<double>();
			if (frameCounter > 0) {
				animation = true;
			}
		}
		Sprite* sprite = new Sprite(x, textureHeight - y - height, width, height,sharedTex, animation, frameCounter);
		m_spriteMap.insert(std::pair<std::string, std::shared_ptr<Sprite>>(name, sprite));
	}
}

bool SpriteSystem::init()
{
	EngineSystem::init();
	initCheck();
	return true;
}

void SpriteSystem::postInit()
{
}

void SpriteSystem::shutdown()
{
	auto it = m_spriteMap.begin();
	for (; it != m_spriteMap.end(); it++) {
		delete it->second.get();
	}
	m_spriteMap.clear();
	EngineSystem::shutdown();
}

SpriteSystem::SpriteSystem()
{
	//Do nothing!
}

SpriteSystem::~SpriteSystem()
{
	//Do nothing!
}

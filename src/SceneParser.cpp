#include "SceneParser.h"
#include <fstream>
#include "picojson.h"
#include "SpriteSystem.h"
#include "TouchingButts.hpp"

glm::vec4 to_vec4(picojson::value v) {
	glm::vec4 res;
	auto array = v.get<picojson::array>();
	for (int i = 0; i < 4; i++) {
		res[i] = (float)array[i].get<double>();
	}
	return res;
}

glm::vec3 to_vec3(picojson::value v) {
	glm::vec3 res;
	auto array = v.get<picojson::array>();
	for (int i = 0; i < 3; i++) {
		res[i] = (float)array[i].get<double>();
	}
	return res;
}



std::vector<GameObjectDescriptor> SceneParser::parse3DFile(std::string filename) {
	std::vector<GameObjectDescriptor> res;

	std::fstream file(filename);
	if (file.is_open()) {
		picojson::value v;
		file >> v;


		for (auto o : v.get("gameobjects").get<picojson::array>()) {
			GameObjectDescriptor d;
			d.uniqueId = (int)o.get("uniqueId").get<double>();
			d.meshName = o.get("meshName").get<std::string>();
			d.color = to_vec4(o.get("color"));
			d.position = to_vec3(o.get("position"));
			d.rotationEuler = to_vec3(o.get("rotationEuler"));
			d.scale = to_vec3(o.get("scale"));
			d.parentId = (int)o.get("parentId").get<double>();
			d.name = o.get("name").get<std::string>();
			if (o.contains("script")) {
				d.script = o.get("script").get<std::string>();
				d.scriptTable = o.get("scriptTable").get<std::string>();
			}
			res.push_back(d);
		}
	}
	return res;
}

std::vector<GameObjectDescriptor> SceneParser::parse2DFile(std::string filename) {
	std::vector<GameObjectDescriptor> res;

	std::fstream file(filename);
	if (file.is_open()) {
		picojson::value v;
		file >> v;

		for (auto meta : v.get("meta").get<picojson::array>()) {
			g_spriteSystem->loadJsonFile(meta.get("spriteAtlasJsonDir").get<std::string>(),meta.get("spriteAtlasJsonFile").get<std::string>());
		}

		for (auto o : v.get("gameobjects").get<picojson::array>()) {
			GameObjectDescriptor d;
			d.uniqueId = (int)o.get("uniqueId").get<double>();
			d.spriteName = "";
			if (o.contains("spriteName"))
			{
				d.spriteName = o.get("spriteName").get<std::string>();
			}
			if (o.contains("animations")) {
				for (auto ani : o.get("animations").get<picojson::array>()) {
						d.animationNames.push_back(ani.get("animationName").get<std::string>());
				}
			}
			d.color = to_vec4(o.get("color"));
			d.position = to_vec3(o.get("position"));
			d.rotationEuler = to_vec3(o.get("rotationEuler"));
			d.scale = to_vec3(o.get("scale"));
			d.parentId = (int)o.get("parentId").get<double>();
			d.name = o.get("name").get<std::string>();
			if (o.contains("script")) {
				d.script = o.get("script").get<std::string>();
				d.scriptTable = o.get("scriptTable").get<std::string>();
			}
			res.push_back(d);
		}

	}
	return res;
}

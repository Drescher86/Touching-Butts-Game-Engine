#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "SRE/Mesh.hpp"
#include "GameObject.h"

/**
Holds all translatable fiels from json to C++.
*/
class GameObjectDescriptor {
public:
	/** Uniquely defines a game object*/
	int uniqueId;

	/** valid values are: "plane", "cube" and "sphere"*/
	std::string meshName;
	/**Sprite name. Used as reference.*/
	std::string spriteName;
	/**Name of animation. Used as reference.*/
	std::vector<std::string> animationNames;

	/**object color*/
	glm::vec4 color;

	/** transform
	 position relative to parent if any.*/
	glm::vec3 position;

	/** rotation relative to parent if any.*/
	glm::vec3 rotationEuler;
	/** scale relative to parent if any.*/
	glm::vec3 scale;
	/**Name of game object. Used as reference.*/
	std::string name;
	/**Filename and path of script.*/
	std::string script;
	/**Script table name.*/
	std::string scriptTable;
	/** parent id (-1 means no parent)*/
	int parentId;
};

/**Parses scenes from json files to GameObjectDescriptors.*/
class SceneParser {
public:
	/**Parse a 3D scene from json.*/
	static std::vector<GameObjectDescriptor> parse3DFile(std::string filename/**Filename and path of json file.*/);
	/**Parse a 2D scene from json.*/
	static std::vector<GameObjectDescriptor> parse2DFile(std::string filename/**Filename and path of json file.*/);
};

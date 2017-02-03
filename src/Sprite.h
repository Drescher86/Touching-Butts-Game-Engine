#pragma once

#include <memory>
#include <vector>
#include "SRE/Mesh.hpp"
#include "SRE/Texture.hpp"
/**
Sprite class used to store one or more meshes. Used internally by components.
*/
class Sprite {
public:
	/**
	Get the sprite's texture.
	*/
	std::shared_ptr<SRE::Texture> getTexture();
	/**
	Get a specified mesh of the sprite.
	*/
	std::shared_ptr<SRE::Mesh> getMesh(int frame = 0/** Frame of the sprite if any. Defaults to 0*/);
	/**
	Get width of the sprite in pixels.
	*/
	int width();
	/**
	Get the height of the sprite in pixels.
	*/
	int height();
	/**
	Get the frame count; amount of meshes.
	*/
	int frameCount();
private:
	Sprite(int sourceX, int sourceY, int sourceWidth, int sourceHeight, std::shared_ptr<SRE::Texture> texture, bool isAnimation, int frameCount);
	int m_sourceX;
	int m_frameCount;
	int m_frameCounter;
	int m_sourceY;
	int m_sourceWidth;
	int m_sourceHeight;
	std::shared_ptr<SRE::Texture> m_texture;
	std::vector<std::shared_ptr<SRE::Mesh>> m_meshes;
	bool m_isAnimation;
	friend class SpriteSystem;
};
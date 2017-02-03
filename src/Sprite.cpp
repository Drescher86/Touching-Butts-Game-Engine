#include "Sprite.h"
#include <vector>
#include "glm/glm.hpp"

std::shared_ptr<SRE::Texture> Sprite::getTexture()
{
	return m_texture;
}

std::shared_ptr<SRE::Mesh> Sprite::getMesh(int frame)
{
	return m_meshes[frame];
}

int Sprite::width()
{
	return m_sourceWidth;
}

int Sprite::height()
{
	return m_sourceHeight;
}

int Sprite::frameCount()
{
	return m_frameCount;
}

Sprite::Sprite(int sourceX, int sourceY, int sourceWidth, int sourceHeight, std::shared_ptr<SRE::Texture> texture, bool isAnimation, int frameCount) {
	m_frameCount = frameCount;
	m_sourceX = sourceX;
	m_sourceY = sourceY;
	m_sourceWidth = sourceWidth;
	m_sourceHeight = sourceHeight;
	m_texture = texture;
	
	float rightX = ((float)sourceX + sourceWidth) / texture->getWidth();
	float lowerY = (float)sourceY / texture->getHeight();
	float upperY = ((float)sourceY + sourceHeight) / texture->getHeight();
	float leftX = (float)sourceX / texture->getWidth();

	std::vector<glm::vec2> uvs({
		glm::vec2{ rightX, lowerY },
		glm::vec2{ rightX, upperY },
		glm::vec2{ leftX, lowerY },
		glm::vec2{ leftX, lowerY },
		glm::vec2{ rightX, upperY },
		glm::vec2{ leftX, upperY }
	});

	std::vector<glm::vec3> vertices({
		glm::vec3{ sourceWidth, 0, 0 },
		glm::vec3{ sourceWidth , sourceHeight, 0 },
		glm::vec3{ 0, 0,0 },
		glm::vec3{ 0, 0,0 },
		glm::vec3{ sourceWidth ,sourceHeight ,0 },
		glm::vec3{ 0, sourceHeight, 0 }
	});

	std::vector<glm::vec3> normals;
	std::shared_ptr<SRE::Mesh> mesh(new SRE::Mesh(vertices, normals, uvs));
	m_meshes.push_back(mesh);
	for (int i = 1; i < frameCount; i++) {
		rightX = ((float)sourceX + sourceWidth + sourceWidth * i) / texture->getWidth();
		leftX = ((float)sourceX + sourceWidth * i) / texture->getWidth();
		uvs.clear();
		uvs = std::vector<glm::vec2>({
			glm::vec2{ rightX, lowerY },
			glm::vec2{ rightX, upperY },
			glm::vec2{ leftX, lowerY },
			glm::vec2{ leftX, lowerY },
			glm::vec2{ rightX, upperY },
			glm::vec2{ leftX, upperY }
		});
		std::shared_ptr<SRE::Mesh> tmp(new SRE::Mesh(vertices, normals, uvs));
		m_meshes.push_back(tmp);
	}
}
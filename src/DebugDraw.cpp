#include "DebugDraw.h"
#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Debug.hpp>
#include "glm/glm.hpp"
#include <math.h>

void DebugDraw::DrawPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
{
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));
	for (int i = 1; i < vertexCount; i++)
	{
		SRE::Debug::drawLine(glm::vec3(vertices[i - 1].x, vertices[i - 1].y, 0), glm::vec3(vertices[i].x, vertices[i].y, 0));
	}
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
{
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));
	for (int i = 1; i < vertexCount; i++)
	{
		SRE::Debug::drawLine(glm::vec3(vertices[i - 1].x, vertices[i - 1].y, 0), glm::vec3(vertices[i].x, vertices[i].y, 0));
		if(i == vertexCount - 1) {
			SRE::Debug::drawLine(glm::vec3(vertices[i].x, vertices[i].y, 0), glm::vec3(vertices[0].x, vertices[0].y, 0));
		}
	}
}

void DebugDraw::DrawCircle(const b2Vec2 & center, float32 radius, const b2Color & color)
{

}

void DebugDraw::DrawSolidCircle(const b2Vec2 & center, float32 radius, const b2Vec2 & axis, const b2Color & color)
{
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));
	for (int i = 0; i < 361; i++)
	{
		float x = center.x + sin(glm::radians(i + 0.0f)) * radius;
		float y = center.y + cos(glm::radians(i + 0.0f)) * radius;
		SRE::Debug::drawLine(glm::vec3(x, y, 0), glm::vec3(x + 1, y, 0));
	}
}

void DebugDraw::DrawSegment(const b2Vec2 & p1, const b2Vec2 & p2, const b2Color & color)
{
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));

	SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0), glm::vec3(p2.x, p2.y, 0));
}

void DebugDraw::DrawTransform(const b2Transform & xf)
{
}

void DebugDraw::DrawPoint(const b2Vec2 & p, float32 size, const b2Color & color)
{
}

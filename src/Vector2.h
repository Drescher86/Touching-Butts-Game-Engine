#pragma once
#include <string>
#include <sstream>
/**
2D vector exposed to LUA scripts.
*/
class Vector2 {
public:
	/**
	New vector 2.
	*/
	Vector2(float x/**X value.*/, float y/**Y value.*/);
	/**
	Get y.
	*/
	float x();
	/**
	Get x.
	*/
	float y();
	/**
	To string.
	*/
	std::string toString();
private:
	float m_x;
	float m_y;
};
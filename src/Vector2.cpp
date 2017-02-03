#include "Vector2.h"

Vector2::Vector2(float x, float y) {
	m_x = x;
	m_y = y;
}

float Vector2::x() {
	return m_x;
}

float Vector2::y() {
	return m_y;
}

std::string Vector2::toString()
{
	std::ostringstream stream;
	stream << "(" << m_x << ", " << m_y << ")";
	return stream.str();
}

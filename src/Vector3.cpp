#include "Vector3.h"

Vector3::Vector3(float x, float y, float z):m_x(x), m_y(y), m_z(z)
{
}

float Vector3::x()
{
	return m_x;
}

float Vector3::y()
{
	return m_y;
}

float Vector3::z()
{
	return m_z;
}

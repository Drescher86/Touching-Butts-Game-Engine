#pragma once
/**
3D vector.
*/
class Vector3 {
public:
	/**
	New vector 3.
	*/
	Vector3(float x/**X value.*/, float y/**Y value.*/, float z/**Z value.*/);
	/**
	Get x.
	*/
	float x();
	/**
	Get y.
	*/
	float y();
	/**
	Get z.
	*/
	float z();
private:
	float m_x;
	float m_y;
	float m_z;
};
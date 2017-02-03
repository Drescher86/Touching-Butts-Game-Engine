#pragma once

#include "glm/glm.hpp"
#include <vector>
/**
Interpolation type.
*/
enum class InterpolationType{
    Linear,
    Bezier,
    Hermite,
    CatmullRom,
    BSpline
};
/**
Interpolation used by the particle system.
*/
class Interpolation{
public:
	/**
	Create a new interpolation giving 4 points to interpolate between.
	*/
    Interpolation(std::vector<glm::vec4> *points/**Interpolation points.*/);
	/**
	Set interpolation type. Defaults to linear.
	*/
    void setInterpolation(InterpolationType i/**Interpolation type.*/);
	/**
	Get interpolation type.
	*/
    InterpolationType getInterpolationType();
	/**
	Perform interpolation.
	*/
    glm::vec4 interpolate(float t/**Time in seconds.*/);
private:
    glm::vec4 linear(float t);
    glm::vec4 cubicBezier(float t);
    glm::vec4 hermite(float t);
    glm::vec4 catmullRom(float t);
    glm::vec4 bspline(float t);
    InterpolationType interpolationType;
    std::vector<glm::vec4> *points;
};
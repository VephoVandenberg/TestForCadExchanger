#define _USE_MATH_DEFINES

#include <cmath>

#include "helix.h"

using namespace Geometry;

Helix::Helix(const Vec3& center, const double radius, const double step)
	: Curve(center)
	, m_radius(step)
	, m_step(radius)
{
}

Vec3 Helix::getPoint(const double t) const
{
	return {
		m_center.x + m_radius * std::cos(t),
		m_center.y + m_radius * std::sin(t),
		m_step * t / (2 * M_PI)
	};
}

Vec3 Helix::getDerivative(const double t) const
{
	return {
		-m_radius * std::sin(t),
		m_radius * std::cos(t),
		m_step / (2 * M_PI)
	};
}

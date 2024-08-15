#include "ellipse.h"

using namespace Geometry;

Ellipse::Ellipse(const Vec3& center, const double xRadius, const double yRadius)
	: Curve(center)
	, m_xRadius(xRadius)
	, m_yRadius(yRadius)
{
}

Vec3 Ellipse::getPoint(const double t) const
{
	return {
		m_center.x + m_xRadius * std::cos(t),
		m_center.y + m_yRadius * std::sin(t),
		0.0
	};
}

Vec3 Ellipse::getDerivative(const double t) const
{
	return {
		-m_xRadius * std::sin(t),
		m_yRadius * std::cos(t),
		0.0
	};
}

Circle::Circle(const Vec3& center, const double radius)
	: Ellipse(center, radius, radius)
{

}

bool Circle::operator<(const Circle& circle) const
{
	return m_xRadius < circle.m_xRadius;
}
#pragma once

#include "curve.h"

namespace Geometry
{
	class __declspec(dllexport) Ellipse : public Curve
	{
	public:
		Ellipse(const Vec3& center, const double xRad, const double yRad);
		~Ellipse() { std::cout << "Ellipse" << '\n'; }

		Vec3 getPoint(const double t) const override;
		Vec3 getDerivative(const double t) const override;

	protected:
		double m_xRadius;
		double m_yRadius;
	};

	class __declspec(dllexport) Circle final : Ellipse
	{
	public:
		Circle(const Vec3& center, const double radius);
		~Circle() = default;

		inline double getRadius() const { return m_xRadius; }
	};
}
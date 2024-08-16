#pragma once

#include "curve.h"

namespace Geometry
{
	class __declspec(dllexport) Helix final : public Curve
	{
	public:
		Helix(const Vec3& vec, const double radius, const double step);
		~Helix() = default;

		Vec3 getPoint(const double t) const override;
		Vec3 getDerivative(const double t) const override;

	private:
		double m_radius;
		double m_step;
	};
}
#pragma once

#include <iostream>

namespace Geometry
{
	struct __declspec(dllexport) Vec3
	{
		double x, y, z;

		friend std::ostream& operator<<(std::ostream& o, const Vec3& p)
		{
			o << "{x: " << p.x << ", y: " << p.y << ", z: " << p.z << '}';
			return o;
		}
	};

	class __declspec(dllexport) Curve
	{
	public:
		  
		Curve(const Vec3& center);

		virtual ~Curve() = default;

		virtual Vec3 getPoint(const double t) const = 0;
		virtual Vec3 getDerivative(const double t) const = 0;

		inline const Vec3& getCenter() const { return m_center; }

	protected:
		Vec3 m_center;
	};
}

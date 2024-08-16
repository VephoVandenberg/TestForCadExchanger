#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <omp.h>

#include <curve.h>
#include <ellipse.h>
#include <helix.h>

constexpr size_t g_numberOfCurves = 30;
constexpr double g_radiusMax = 800.0;
constexpr double g_stepMax = 10.0;
constexpr Geometry::Vec3 g_minPos = { -1000.0, -1000.0, 0.0 };
constexpr Geometry::Vec3 g_maxPos = { 1000.0, 1000.0, 0.0 };

std::string getType(const std::shared_ptr<Geometry::Curve>& curve);

int main(int argc, char** argv)
{
	// 1. Populate a container(e.g.vector or list) of objects of these types created in random manner
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<double> posXDist(g_minPos.x, g_maxPos.x);
	std::uniform_real_distribution<double> posYDist(g_minPos.y, g_maxPos.y);
	std::uniform_real_distribution<double> radiusDist(0.001, g_radiusMax);
	std::uniform_real_distribution<double> stepDist(0.001, g_stepMax);
	std::uniform_int_distribution<int32_t> curveTypeDist(1, 3);

	std::vector<std::shared_ptr<Geometry::Curve>> curves;
	for (size_t iCurve = 0; iCurve < g_numberOfCurves; iCurve++)
	{
		int32_t curveType = curveTypeDist(generator);
		Geometry::Vec3 center = { posXDist(generator), posYDist(generator), 0.0 };

		switch (curveType)
		{
		case 1: {
			curves.push_back(
				std::make_shared<Geometry::Ellipse>(center, radiusDist(generator), radiusDist(generator)));
		} break;

		case 2: {
			curves.push_back(
				std::make_shared<Geometry::Circle>(center, radiusDist(generator)));
		} break;

		case 3: {
			curves.push_back(
				std::make_shared<Geometry::Helix>(center, radiusDist(generator), stepDist(generator)));
		} break;
		}
	}

	// 2. Print coordinates of points and derivatives of all curves in the container at t=PI/4.
	for (const auto& curve : curves)
	{
		auto p = curve->getPoint(M_PI / 4);
		auto d = curve->getDerivative(M_PI / 4);

		std::cout << "------------" << '\n';
		std::cout << getType(curve) << '\n';
		std::cout << "Derivative " << d << '\n';
		std::cout << "Point " << p << '\n';
		std::cout << "------------" << '\n';
	}

	std::cout << '\n';

	// 3. Populate a second container that would contain only circles from the first container,
	// make sure the second container shares circles of the first one, via pointers.
	std::vector<std::shared_ptr<Geometry::Circle>> circles;
	for (const auto& curve : curves)
	{
		auto circle = std::dynamic_pointer_cast<Geometry::Circle>(curve);
		if (circle)
		{
			circles.push_back(circle);
			std::cout << "Circle in point " << circle->getCenter() << ", R: " << circle->getRadius() << '\n';
		}
	}

	std::cout << '\n';

	// 4. Sort the second container in the ascending order of circles’ radii.
	std::sort(circles.begin(), circles.end(), 
		[](const auto& c1, const auto& c2) {
			return *c1 < *c2;
		});
	for (const auto& circle : circles)
	{
		std::cout << "Circle in point " << circle->getCenter() << ", R: " << circle->getRadius() << '\n';
	}

	// 5. Compute the total sum of radii of all curves in the second container
	std::cout << "Total sum of radii in second container" << std::endl;
	double total = 0;

	#pragma omp parallel for reduction(+:total)
	for (const auto& circle : circles)
	{
		total += circle->getRadius();
	}
	std::cout << "Total = " << total << '\n';

	return 0;
}

std::string getType(const std::shared_ptr<Geometry::Curve>& curve)
{
	if (std::dynamic_pointer_cast<Geometry::Circle>(curve))
	{
		return "Circle";
	}

	if (std::dynamic_pointer_cast<Geometry::Ellipse>(curve))
	{
		return "Ellipse";
	}

	if (std::dynamic_pointer_cast<Geometry::Helix>(curve))
	{
		return "Helix";
	}

	return "BaseCurve";
}

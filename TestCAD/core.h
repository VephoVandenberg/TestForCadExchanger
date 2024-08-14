#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include <curve.h>
#include <ellipse.h>
#include <helix.h>

namespace Constants
{
	constexpr unsigned int g_numberOfCurves = 1000;
	constexpr double g_radiusMax = 500.0f;
	constexpr double g_stepMax = 10.0f;
	constexpr Geometry::Vec3 g_minPos = { -400.0f, -400.0f, 0.0f };
	constexpr Geometry::Vec3 g_maxPos = { 800.0f, 800.0f, 0.0f };
}
// ReSharper disable CppUnusedIncludeDirective
#pragma once
#include "CubeOrder.h"
#include "DiamondOrder.h"
#include "TiltedCubeOrder.h"
#include "ShortOvalOrder.h"

enum class OrderType
{
	cube = 0,
	diamond,
	tiltedCube,
	shortOval
};
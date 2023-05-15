// ReSharper disable CppUnusedIncludeDirective
#pragma once
#include "application/layer/sandbox/world/chunks/order_type/cube_order.h"
#include "application/layer/sandbox/world/chunks/order_type/diamond_order.h"
#include "application/layer/sandbox/world/chunks/order_type/tilted_cube_order.h"
#include "application/layer/sandbox/world/chunks/order_type/short_oval_order.h"

enum class OrderType
{
	cube = 0,
	diamond,
	tiltedCube,
	shortOval
};
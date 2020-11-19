#pragma once

#include "Types.h"
#include <stdlib.h>

class Collisions
{
public:

	static bool ExistCollision(Vec2 p1, Vec2 p2, float offset);
	static bool ExistCollision(Vec2 p1, MyRect r1);
	static bool ExistCollision(MyRect r1, MyRect r2);
};
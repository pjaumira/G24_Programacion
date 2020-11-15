#include "Collisions.h"

bool Collisions::ExistCollision(Vec2 p1, Vec2 p2, float offset)
{
    return abs((long)(Vec2(p2 - p1)).mod()) < offset;
}

bool Collisions::ExistCollision(Vec2 p1, MyRect r1)
{
    return (p1.x > r1.x && p1.x < r1.x + r1.w) && (p1.y > r1.y && p1.y < r1.y + r1.h);
}


bool Collisions::ExistCollision(MyRect r1, MyRect r2)
{
    return ExistCollision(MyRect(r1.x, r1.y), r2)
        || ExistCollision(Vec2(r1.x + r1.w, r1.y), r2)
        || ExistCollision(Vec2(r1.x + r1.w, r1.y + r1.h), r2)
        || ExistCollision(Vec2(r1.x + r1.w, r1.y + r1.h), r2);
}
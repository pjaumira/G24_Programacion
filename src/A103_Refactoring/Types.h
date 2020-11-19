#pragma once

#include <math.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <time.h>

using Color = struct Color{

	int r, g, b, a;
	Color();
	Color(int _r, int _g, int _b, int _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
};

using Font = struct {

	std::string id;
	std::string path;
	int size;
};

using Text = struct {
	std::string id;
	std::string text;
	Color color;
	int w;
	int h;
};

struct Vec2 {
	int x, y;

	Vec2() : x(0), y(0) {};
	Vec2(int _xy) : x(_xy), y(_xy) {};
	Vec2(int _x, int _y) : x(_x), y(_y) {};

	inline bool operator== (const Vec2& v)const { return (x == v.x && y == v.y); };
	const Vec2 operator- (const Vec2& v) { return Vec2(x - v.x, y - v.y); };
	const Vec2 operator+ (const Vec2& v) { return Vec2(x + v.x, y + v.y); };
	Vec2 operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; };
	const Vec2 operator/ (const Vec2& v) { return Vec2(x / v.x, y / v.y); };
	const Vec2 operator/ (float a) const { return Vec2(static_cast<int>(x) / a, static_cast<int>(y) / a); };
	const Vec2 operator* (const Vec2& v) { return Vec2(x * v.x, y * v.y); };
	const Vec2 operator* (float a) const { return Vec2(static_cast<int>(x) * a, y * a); };
	const Vec2 operator* (int a) const { return Vec2(x * a, y * a); };
	const Vec2 operator*= (const Vec2& v) { return Vec2(x * v.x, y * v.y); };
	const Vec2 operator*= (const int& i) { return Vec2(x * i, y * i); };

	float mod() { return sqrt(x * x + y * y); };
};

struct MyRect {
	int x, y, w, h;

	MyRect() : x(0), y(0), w(0), h(0) {};
	MyRect(int x_, int y_) : x(x_), y(y_), w(0), h(0) {};
	MyRect(int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_) {};
};

enum class InputKeys {
	MOUSE_LEFT, W, A, S, D, UP, LEFT, DOWN, RIGHT, ESC, NONE, COUNT
};
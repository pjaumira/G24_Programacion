#pragma once
//Document per recopilar variables importants i que no molestin al document principal

#include <math.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <time.h>

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

	MyRect () : x(0), y(0), w(0), h(0) {};
	MyRect (int x_, int y_) : x(x_), y(y_), w(0), h(0) {};
	MyRect (int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_) {};
};

enum class InputKeys {
	MOUSE_LEFT, W, A, S, D, UP, LEFT, DOWN, RIGHT, ESC, NONE, COUNT
};

struct InputData {
	private :
		bool keyboardPressed [(int)InputKeys::COUNT] = {};
		bool keyboardKeyDown [(int)InputKeys::COUNT] = {};
		Vec2 mouse;
		Vec2 screenSize;

		//Time Control
		clock_t lastTime = clock();
		float deltaTime = 0.0f;

	public :
		void UpdateDeltaTime() {
			deltaTime = (clock() - lastTime);
			lastTime = clock();
			deltaTime /= CLOCKS_PER_SEC;	
		}

		Vec2 GetMouseCoord () { return mouse; }
		void SetScreenSize (Vec2 screenSize_) { screenSize = screenSize_; }
		const Vec2* getScreenSize() const { return &screenSize; }
		void SetMouseCoords(int x, int y) {
			mouse = { x,y };	
		}

		bool IsPressed(InputKeys key) {
			return keyboardPressed [(int)key];
		}

		bool JustPressed(InputKeys key) {
			return keyboardKeyDown [(int)key];
		}

		void SetKeyValue(InputKeys key, bool value) {
			if (!keyboardPressed[(int)key]) {
				keyboardKeyDown[(int)key] = value;
			}
			else {
				keyboardKeyDown[(int)key] = false;
			}
			keyboardPressed[(int)key] = value;
		}

		void SetFalseKeyDown() {
			for (int i = 0; i < (int)InputKeys::COUNT; i++) {
				keyboardKeyDown[i] = false;
			}
		}

	inline const float* GetDeltaTime() const { return &deltaTime; }
};

enum class EDirection { NONE = -1, UP, LEFT, DOWN, RIGHT, COUNT};
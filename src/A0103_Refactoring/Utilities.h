#pragma once

#include <string>
#include <vector>
#include "Types.h"
#include "Game.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const int FPS = 60;

static MyRect SDL2My(SDL_Rect rect) {
	return MyRect(rect.x, rect.y, rect.w, rect.h);
}

static SDL_Rect My2SDL(const MyRect* r) {
	return {
		r->x,
		r->y,
		r->w,
		r->h,
	};
}

static std::string F2StrFormat(float num, int decimals) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(decimals) << num;
	return static_cast <std::string> (stream.str());
}
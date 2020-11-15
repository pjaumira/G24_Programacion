#pragma once

#include "Collisions.h"
#include <map>

class Player {

public:
	enum class numPlayer { NONE = -1, P1, P2, COUNT};

private:
	// Independitzarlo de SDL
	MyRect position;
	MyRect frame;
	numPlayer pNum;
	EDirection dir = EDirection::NONE;

	int initCol, lastCol;
	int initRow, lastRow;
	float frameCount = 0;

	std::map <InputKeys, EDirection> bindInput;

public:
	Player();

	void Update(InputData);
	inline const MyRect* getPosition() { return &position; }
	inline const MyRect* getFrame() { return &frame; }

	void setPlayerValues(int texWidht, int texHeight, int nCol, int nRow, numPlayer num);

private:
	bool Move(InputData);
	void UpdateSprite();
};
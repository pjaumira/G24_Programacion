#include "Collisions.h"
#include <vector>

class Goldbag;

class Player {

public:
	enum class numPlayer { NONE = -1, P1, P2, COUNT };

private:
	// Independitzarlo de SDL

	struct DirectionMove {
		EDirection eD;
		Vec2 vD;

		DirectionMove() : eD(EDirection::NONE), vD(Vec2()) {};
		DirectionMove(EDirection e, Vec2 v)
		{
			eD = e;
			vD = v;
		};
	};

	int score;
	MyRect position;
	MyRect frame;
	numPlayer pNum;
	EDirection dir = EDirection::NONE;

	int initCol, lastCol;
	int initRow, lastRow;
	float frameCount = 0;

public:
	Player();
	~Player();

	void Update(InputData*, std::vector<Goldbag*>& goldBags);
	bool Move(InputData*);
	void UpdateSprite();
	void UpdateCollisions(std::vector <Goldbag*>& goldBags, InputData* input);

	void CheckCollision();

	inline const MyRect* getPosition() { return &position; }
	inline const MyRect* getFrame() { return &frame; }

	void setPlayerValues(int texWidht, int texHeight, int nCol, int nRow, numPlayer num);

	inline const int* getScore() const { return &score; }

private:
	bool Move(InputData);
	void UpdateSprite();
};
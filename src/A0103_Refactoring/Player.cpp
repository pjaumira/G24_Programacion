#include "Player.h"
#include "GoldBag.h"

// <>

Player::Player() : position({ 1,1,40,40 }), frame({ 0,0,20,20 }), pNum(numPlayer::NONE) {
	initCol = lastCol = 0;
	initRow = lastRow = 0;
	frameCount = 0;
	score = 0;
}

void Player::Update(InputData input) {
	Move(input);
	UpdateSprite();
	UpdateCollisions(goldBags, input);
}

bool Player::Move(InputData input) {

	dir = EDirection::NONE;
	Vec2 newPosition = { position.x, position.y };

	switch (pNum) {
	case Player::numPlayer::P1:
		if (input.IsPressed(InputKeys::UP)) {
			newPosition.y--;
			dir = EDirection::UP;
		}
		if (input.IsPressed(InputKeys::LEFT)) {
			newPosition.x--;
			dir = EDirection::LEFT;
		}
		if (input.IsPressed(InputKeys::DOWN)) {
			newPosition.y++;
			dir = EDirection::DOWN;
		}
		if (input.IsPressed(InputKeys::RIGHT)) {
			newPosition.x++;
			dir = EDirection::RIGHT;
		}
		break;
	case Player::numPlayer::P2:
		if (input.IsPressed(InputKeys::W)) {
			newPosition.y--;
			dir = EDirection::UP;
		}
		if (input.IsPressed(InputKeys::A)) {
			newPosition.x--;
			dir = EDirection::LEFT;
		}
		if (input.IsPressed(InputKeys::S)) {
			newPosition.y++;
			dir = EDirection::DOWN;
		}
		if (input.IsPressed(InputKeys::D)) {
			newPosition.x++;
			dir = EDirection::RIGHT;
		}
		break;
	default:
		return false;
		break;
	}

	// <>
	//Check for player Collision
	if (newPosition.x > input.getScreenSize()->x || newPosition.x < 0) newPosition.x = position.x;
	if (newPosition.y > input.getScreenSize()->y || newPosition.y < 150) newPosition.y = position.y;

	//Update Position
	if (newPosition.x != 0 || newPosition.y != 0) {
		position.x = newPosition.x;
		position.y = newPosition.y;
		return true;
	}

	return false;
}

void Player::UpdateSprite() {

	if (dir != EDirection::NONE) frameCount++;

	if (60 / frameCount <= 9) {

		frameCount = 0;
		frame.x += frame.w;
		if (frame.x >= frame.w * lastCol) frame.x = frame.w * initCol;
	}

	switch (dir) {

	case EDirection::UP:
		frame.y = (initRow + 3) * frame.h;
		break;
	case EDirection::LEFT:
		frame.y = (initRow + 1) * frame.h;
		break;
	case EDirection::DOWN:
		frame.y = (initRow + 0) * frame.h;
		break;
	case EDirection::RIGHT:
		frame.y = (initRow + 2) * frame.h;
		break;
	case EDirection::NONE:
		frame.y = (initRow + 0) * frame.h;
		break;
	default:
		frame.y = (initRow + 0) * frame.h;
		break;
	}
}

void Player::setPlayerValues(int texWidht, int texHeight, int nCol, int nRow, numPlayer	pNum_) {

	pNum = pNum_;

	frame.w = texWidht / nCol;
	frame.h = texHeight / nRow;

	switch (pNum_) {

	case Player::numPlayer::P1:

		initCol = 3;
		lastCol = initCol + 3;
		initRow = 0;
		lastRow = initRow + 4;
		frame.x = frame.w * initCol;
		frame.y = frame.h * initRow;

		position.x = 100;
		position.y = 250;
		break;

	case Player::numPlayer::P2:

		initCol = 6;
		lastCol = initCol + 3;
		initRow = 4;
		lastRow = initRow + 4;
		frame.x = frame.w * initCol;
		frame.y = frame.h * initRow;

		position.x = 600;
		position.y = 250;
		break;
	default:
		frame.x = 0;
		frame.y = 0;
		break;
	}
}

void Player::UpdateCollisions(std::vector<GoldBag*> goldBags, InputData* input) {
	for (GoldBag* g : goldBags) {
		if (Collisions::ExistCollision(position, *g->getPosition())) {
			Vec2 rPos = Vec2::rVec(150, input->getScreenSize()->x < input->getScreenSize()->y ?
				(input->getScreenSize()->x - 150) : (input->getScreenSize()->y - 150));
			g->SetPosition(rPos);
			score++;
		}
	}
}
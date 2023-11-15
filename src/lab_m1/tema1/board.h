#pragma once

#include "regpoly.h"
#include "colors.h"
#include "core/gpu/mesh.h"
#include "components/simple_scene.h"
#include "observer.h"
#include "gun.h"
#include "transform2d.h"
#include "enemy.h"
#include "constants.h"
#include "playerState.h"

#include <iostream>
#include <cmath>
#include <unordered_map>

#define BOARD_SIZE 3

namespace game
{
	class Board: Observer {
	private:
		float x, y;
		float tileSide;
		float margin;
		float gateWidth;
		Mesh* boardTile;
		Mesh* boardGate;
		void createBoard();
		PlayerState* playerState;
		gfxc::SimpleScene *ctx;
		float linesY[BOARD_SIZE];

	public:
		struct Tile {
			float x;
			float y;
			Gun* gun;
			Tile() : x(0), y(0), gun(NULL) {}
			Tile(float x, float y) : x(x), y(y), gun(NULL) {}
		};

		glm::vec2 boardGateCenter;
		std::vector<Enemy*> colorsPerLine[BOARD_SIZE][ENTITIES];
		Tile board[BOARD_SIZE][BOARD_SIZE];
		Board(float x, float y, float tileSide, float gateWidth, float margin, PlayerState* playerState, gfxc::SimpleScene*ctx);
		void draw();
		float* getLinesY();
		void alert(Enemy* enemy);
		virtual void update(int x, int y, int button, int type) override;
	};
}
#include "enemies.h"

using namespace game;

Enemies::Enemies(Board* board, float* linesY, gfxc::SimpleScene* ctx, PlayerState* playerState, ResizableViewport* viewport)
	: linesY(linesY), ctx(ctx), elapsedTime(0.0f), board(board), playerState(playerState), viewport(viewport) {
	RegPolygone* regpoly;
	std::vector<glm::vec3> colors = ColorSingleton::getInstance()->getEntitiesColors();
	
	for (int i = 0; i < colors.size(); i++) {
		regpoly = new RegPolygone(-1, 6, 30, 0.0f, true, 1);
		meshes[i][0] = regpoly->createMesh("outter", colors.at(i));
		delete regpoly;

		regpoly = new RegPolygone(-1, 6, 20, 0.0f, true, 1);
		meshes[i][1] = regpoly->createMesh("inner", ColorSingleton::getInstance()->getColor("tile"));
		delete regpoly;
	}
}

void Enemies::generate(float deltaTime) {
	elapsedTime += deltaTime;

	if (elapsedTime >= WAIT_TIME) {
		int lineIndex = rand() % BOARD_SIZE;
		int enemyId = rand() % ENEMIES;
		std::vector<glm::vec3> colors = ColorSingleton::getInstance()->getEntitiesColors();

		Enemy* newEnemy = new Enemy(
			viewport->originalX + 50.0f,
			linesY[lineIndex],
			3,
			meshes[enemyId][0],
			meshes[enemyId][1],
			lineIndex,
			enemyId,
			board,
			viewport,
			ctx
		);

		board->alert(newEnemy);

		elapsedTime = 0.0f;
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < ENTITIES; j++) {
			for (int k = 0; k < board->colorsPerLine[i][j].size(); k++) {
				board->colorsPerLine[i][j][k]->draw();
				glm::vec2 coord = board->colorsPerLine[i][j][k]->getPosition();
				board->colorsPerLine[i][j][k]->setPosition(coord.x - 50.0f * deltaTime, coord.y);
			}
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < ENTITIES; j++) {
			for (int k = 0; k < board->colorsPerLine[i][j].size(); k++) {
				glm::vec2 pos = board->colorsPerLine[i][j][k]->getPosition();
				if (pos.x < board->boardGateCenter.x) {
					playerState->setLives(playerState->getLives() - 1);
					playerState->resetLivesPoints();

					if (playerState->getLives() == 0) {
						exit(1);
					}

					board->colorsPerLine[i][j].erase(board->colorsPerLine[i][j].begin() + k);
					k--;
				}
			}
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < ENTITIES; j++) {
			std::vector<Enemy*> enemyVector = board->colorsPerLine[i][j];
			for (int k = 0; k < enemyVector.size(); k++) {
				for (int p = 0; p < BOARD_SIZE; p++) {
					Gun* gun = board->board[i][p].gun;

					if (gun != NULL) {
						glm::vec2 pos = enemyVector[k]->getPosition();
						float distance = glm::distance(glm::vec2(gun->x, gun->y), glm::vec2(pos.x, pos.y));

						if (distance <= 50.0f) {
							gun->doRemoveAnimation = &board->board[i][p].gun;
						}
					}
				}
			}
		}
	}
}
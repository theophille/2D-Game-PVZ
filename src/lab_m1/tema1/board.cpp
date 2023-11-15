#include "board.h"
#include "gun.h"
#include "service.h"

using namespace game;

Board::Board(float x, float y, float tileSide, float gateWidth, float margin, PlayerState* playerState, gfxc::SimpleScene *ctx)
	: x(x), y(y), tileSide(tileSide), gateWidth(gateWidth), margin(margin), playerState(playerState), ctx(ctx) {
	Service::getInstance()->mouseEvent->subscribe(this, 1);
	Service::getInstance()->mouseEvent->subscribe(this, 2);
	glm::vec3 color = ColorSingleton::getInstance()->getColor("tile");
	
	float radius = tileSide / sqrtf(2.0f);
	RegPolygone *tile = new RegPolygone(-1, 4, radius, 45, true, -1.0f);
	boardTile = tile->createMesh("boardTile", glm::vec3(color.x, color.y, color.z));

	color = ColorSingleton::getInstance()->getColor("red");
	RegPolygone *gate = new RegPolygone(-1, 4, 1.0f / sqrtf(2.0f), 45, true, -1.0f);
	boardGate = gate->createMesh("boardGate", glm::vec3(color.x, color.y, color.z));
	
	createBoard();

	delete tile;
	delete gate;
}

void Board::createBoard() {
	float step = tileSide + margin;

	boardGateCenter = glm::vec2(x - tileSide / 2.0f - margin - gateWidth / 2.0f, y + step);

	for (int i = 0; i < BOARD_SIZE; i++) {
		linesY[i] = y + (float)(BOARD_SIZE - i - 1) * step;

		for (int j = 0; j < BOARD_SIZE; j++) {
			float tileX = x + (float)j * step;
			float tileY = linesY[i];
			board[i][j] = Tile(tileX, tileY);
		}
	}
}

void Board::draw() {
	std::unordered_map<std::string, Shader*> shaders = ctx->getShaders();

	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(boardGateCenter.x, boardGateCenter.y);
	modelMatrix *= transform2D::Scale(gateWidth, 3 * tileSide + 2 * margin);
	ctx->RenderMesh2D(boardGate, shaders["VertexColor"], modelMatrix);

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(board[i][j].x, board[i][j].y);
			ctx->RenderMesh2D(boardTile, shaders["VertexColor"], modelMatrix);
			
			if (board[i][j].gun != NULL) {
				board[i][j].gun->draw();
			}
		}
	}
}

float* Board::getLinesY() {
	return linesY;
}

void Board::update(int x, int y, int button, int type) {
	Service* svc = Service::getInstance();
	int i, j;
	bool found = false;

	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (glm::distance(glm::vec2(board[i][j].x, board[i][j].y), glm::vec2(x, y)) <= tileSide / 2.0f) {
				found = true;
				break;
			}
		}

		if (found) {
			break;
		}
	}

	if (found) {
		if (button == 1 && svc->dragged != NULL) {
			if (board[i][j].gun == NULL && svc->dragged->cost <= playerState->getHP()) {
				playerState->setHP(playerState->getHP() - svc->dragged->cost);
				if (playerState->getHP() != MAX_STARS_NUM + 1) {
					playerState->setStarsPoints(playerState->getStarsPoints());
				}
				
				board[i][j].gun = new Gun(
					board[i][j].x,
					board[i][j].y,
					svc->dragged->cost,
					i,
					svc->dragged->mesh,
					svc->dragged->colorId,
					svc->dragged->guns,
					svc->dragged->board,
					svc->dragged->ctx
				);

				std::vector<Enemy*> enem = colorsPerLine[board[i][j].gun->line][board[i][j].gun->colorId];

				if (enem.size()) {
					board[i][j].gun->active = true;
				}
			}

		}
		else if (button == 2 && type == 1) {
			board[i][j].gun->doRemoveAnimation = &board[i][j].gun;
		}
	}
}

void Board::alert(Enemy* enemy) {
	colorsPerLine[enemy->getLine()][enemy->getColorId()].push_back(enemy);

	for (int i = 0; i < BOARD_SIZE; i++) {
		if (board[enemy->getLine()][i].gun != NULL && board[enemy->getLine()][i].gun->colorId == enemy->getColorId()) {
			board[enemy->getLine()][i].gun->active = true;
		}
	}
}
#include "guns.h"
#include "gun.h"
#include "service.h"
#include "board.h"

using namespace game;

Guns::Guns(float x, float y, float itemSide, float margin,
	Board* board, ResizableViewport* viewport, gfxc::SimpleScene* ctx)
	: x(x), y(y), itemSide(itemSide), margin(margin),
	board(board), ctx(ctx), viewport(viewport) {
	Service::getInstance()->mouseEvent->subscribe(this, 1);
	std::vector<unsigned int> costs = { 1, 2, 3, 3 };
	std::vector<glm::vec3> colors = ColorSingleton::getInstance()->getEntitiesColors();


	for (int i = 0; i < GUNS_NUM; i++) {
		DiamondGun* diamGun = new DiamondGun(-1, 80, 40, 30); 
		guns.push_back(new Gun(
			costs.at(i),
			diamGun->createMesh("gun", colors.at(i)),
			i,
			this,
			board,
			ctx)
		);
		delete diamGun;
	}

	Star* bullet = new Star(-1, 8, 20.0f, 10.0f);
	bulletMesh = bullet->createMesh("bullet", ColorSingleton::getInstance()->getColor("yellow"));
	delete bullet;

	float radius = Guns::itemSide / sqrtf(2.0f);

	RegPolygone* regpoly = new RegPolygone(-1, 4, radius, 45, false);
	selectBoxMesh = regpoly->createMesh("selectBox", ColorSingleton::getInstance()->getColor("tile"));
	delete regpoly;

	Star* star = new Star(-1, 5, 20.0f, 10.0f);
	starMesh = star->createMesh("star", ColorSingleton::getInstance()->getColor("red"));
	delete star;

	computePoints();

	for (int i = 0; i < GUNS_NUM; i++) {
		guns.at(i)->setPosition(selectBoxesPoints.at(i).x, selectBoxesPoints.at(i).y);
	}
}

Gun* Guns::getGun(unsigned int id) {
	return guns[id];
}

std::vector<game::Gun*> Guns::getAllGuns() {
	return guns;
}

void Guns::computePoints() {
	float step = itemSide + margin;

	for (int i = 0; i < GUNS_NUM; i++) {
		selectBoxesPoints.push_back(glm::vec2(x + i * step, y));
	}

	for (int i = 0; i < GUNS_NUM; i++) {
		float starStep = itemSide / guns[i]->cost;
		float currentX = x + i * step - itemSide / 2.0f;
		starsPoints.push_back(new std::vector<glm::vec2>);
		for (int j = 0; j < guns[i]->cost; j++) {
			float starX = currentX + starStep / 2.0f + j * starStep;
			starsPoints.at(i)->push_back(glm::vec2(starX, y - itemSide / 2.0f - 30));
		}
	}
}

void Guns::draw() {
	std::unordered_map<std::string, Shader*> shaders = Guns::ctx->getShaders();

	glm::mat3 modelMatrix;

	for (int i = 0; i < GUNS_NUM; i++) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(selectBoxesPoints.at(i).x, selectBoxesPoints.at(i).y);
		ctx->RenderMesh2D(selectBoxMesh, shaders["VertexColor"], modelMatrix);
		ctx->RenderMesh2D(selectBoxMesh, shaders["VertexColor"], modelMatrix);
		guns[i]->draw();
	}

	for (int i = 0; i < GUNS_NUM; i++) {
		for (int j = 0; j < guns[i]->cost; j++) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(starsPoints.at(i)->at(j).x, starsPoints.at(i)->at(j).y);
			ctx->RenderMesh2D(starMesh, shaders["VertexColor"], modelMatrix);
		}
	}
}

void Guns::update(int mouseX, int mouseY, int button, int type) {
	if (button == 1 && type == 0) {
		for (int i = 0; i < guns.size(); i++) {
			float distance = glm::distance(glm::vec2(guns.at(i)->x, guns.at(i)->y), glm::vec2(mouseX, mouseY));

			if (distance <= 30.0f) {
				Service::getInstance()->dragged = guns.at(i);
				break;
			}
		}
	}
}

void Guns::generateBullet(float x, float y, unsigned int line, unsigned int colorId) {
	bulletsPerLine[line][colorId].push_back(Bullet(x, y));
}

void Guns::drawBullets() {
	float deltaTime = Service::getInstance()->deltaTime;
	std::unordered_map<std::string, Shader*> shaders = ctx->getShaders();

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < ENTITIES; j++) {
			for (int k = 0; k < bulletsPerLine[i][j].size(); k++) {
				bulletsPerLine[i][j].at(k).x += 50.0f * deltaTime;
				bulletsPerLine[i][j].at(k).rotation += DEG_TO_RAD(-50.0f * deltaTime);

				glm::mat3 modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(bulletsPerLine[i][j].at(k).x, bulletsPerLine[i][j].at(k).y);
				modelMatrix *= transform2D::Rotate(bulletsPerLine[i][j].at(k).rotation);

				ctx->RenderMesh2D(bulletMesh, shaders["VertexColor"], modelMatrix);

				if (bulletsPerLine[i][j].at(k).x > viewport->originalX) {
					bulletsPerLine[i][j].erase(bulletsPerLine[i][j].begin() + k);
					k--;
				}

				if (!bulletsPerLine[i][j].size()) {
				}
			}
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < ENTITIES; j++) {
			for (int k = 0; k < bulletsPerLine[i][j].size(); k++) {
				if (board->colorsPerLine[i][j].size()) {
					glm::vec2 enemyPos = board->colorsPerLine[i][j].at(0)->getPosition();

					float distance = glm::distance(
						glm::vec2(bulletsPerLine[i][j].at(k).x, bulletsPerLine[i][j].at(k).y),
						glm::vec2(enemyPos.x, enemyPos.y)
					);

					if (distance <= 50.0f) {
						bulletsPerLine[i][j].erase(bulletsPerLine[i][j].begin() + k);
						bool deadEnemy = board->colorsPerLine[i][j].at(0)->gotDamage();
						if (deadEnemy) {
							Service::getInstance()->enemyTrash.push_back(board->colorsPerLine[i][j].at(0));
							board->colorsPerLine[i][j].erase(board->colorsPerLine[i][j].begin());
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < ENTITIES; j++) {
			if (!board->colorsPerLine[i][j].size()) {
				for (int k = 0; k < BOARD_SIZE; k++) {
					if (board->board[i][k].gun != NULL && board->board[i][k].gun->colorId == j) {
						board->board[i][k].gun->active = false;
					}
				}
			}
		}
	}
}
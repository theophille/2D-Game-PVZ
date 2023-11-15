#include "enemy.h"
#include "service.h"
#include "board.h"

using namespace game;

Enemy::Enemy(float x, float y, float lives, Mesh* inner,
	Mesh* outter, unsigned int line, unsigned int colorId,
	Board* board, ResizableViewport* viewport, gfxc::SimpleScene* ctx)
	: x(x), y(y), lives(lives), outter(outter), inner(inner), line(line), board(board), colorId(colorId), ctx(ctx) {
}

void Enemy::draw() {
	float deltaTime = Service::getInstance()->deltaTime;
	std::unordered_map<std::string, Shader*> shaders = ctx->getShaders();

	glm::mat3 modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(x, y);
	ctx->RenderMesh2D(outter, shaders["VertexColor"], modelMatrix);
	ctx->RenderMesh2D(inner, shaders["VertexColor"], modelMatrix);

	/*if (x < 100.0f) {
		Service::getInstance()->enemyTrash
		std::vector<Enemy*> vector = board->colorsPerLine[line][colorId];
		auto i = find(vector.begin(), vector.end(), this);

		if (i != vector.end()) {
			vector.erase(i);
			std::cout << "Nope" << std::endl;
		}

		delete this;
	}*/
}

bool Enemy::gotDamage() {
	lives--;
	this->arr = arr;

	if (lives == 0) {
		doRemoveAnimation = true;
		return true;
	}

	return false;
}

void Enemy::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

glm::vec2 Enemy::getPosition() {
	return glm::vec2(x, y);
}

unsigned int Enemy::getLine() {
	return line;
}

unsigned int Enemy::getColorId() {
	return colorId;
}
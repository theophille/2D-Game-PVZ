#include "gun.h"
#include "guns.h"
#include "board.h"
#include "service.h"

using namespace game;

Gun::Gun(float x, float y, unsigned int cost, unsigned int line,
	Mesh* mesh, unsigned int colorId,
	Guns* guns, Board* board, gfxc::SimpleScene* ctx)
	: x(x), y(y), cost(cost), line(line), mesh(mesh),
	colorId(colorId), guns(guns), board(board), ctx(ctx) {}

Gun::Gun(unsigned int cost, Mesh* mesh,
	unsigned int colorId, Guns* guns, Board* board, gfxc::SimpleScene* ctx)
	: x(-1), y(-1), cost(cost), line(0), mesh(mesh),
	colorId(colorId), guns(guns), board(board), ctx(ctx) {}

Gun::~Gun() {}

void Gun::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

void Gun::draw() {
	std::unordered_map<std::string, Shader*> shaders = ctx->getShaders();

	glm::mat3 modelMatrix;
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(x, y);

	if (doRemoveAnimation != NULL) {
		float deltaTime = Service::getInstance()->deltaTime;
		scale -= 3 * deltaTime;
		modelMatrix *= transform2D::Scale(scale, scale);
	}

	ctx->RenderMesh2D(mesh, shaders["VertexColor"], modelMatrix);

	if (active) {
		float deltaTime = Service::getInstance()->deltaTime;

		if (elapsedTime == 0.0f) {
			guns->generateBullet(x, y, line, colorId);
		}

		elapsedTime += deltaTime;

		if (elapsedTime >= BULLETS_TIME) {
			elapsedTime = 0.0f;
		}
	}
	
	if (scale <= 0) {
		*doRemoveAnimation = NULL;
		delete this;
	}

}
#include "service.h"

using namespace game;

Service::Service() : dragged(NULL), mouseEvent(NULL), dropped(nullptr) {}

Service* Service::instance = NULL;

Service* Service::getInstance() {
	if (instance == NULL) {
		instance = new Service();
		return instance;
	}
	else {
		return instance;
	}
}

void Service::emptyEnemyTrash() {

	for (int i = 0; i < enemyTrash.size(); i++) {
		Enemy* enemy = enemyTrash.at(i);
		std::unordered_map<std::string, Shader*> shaders = enemy->ctx->getShaders();
		glm::vec2 pos = enemy->getPosition();

		if (enemy->scale >= 0) {
			std::cout << "enemy->scale" << enemy->scale << std::endl;
			glm::mat3 modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(pos.x, pos.y);
			modelMatrix *= transform2D::Scale(enemy->scale, enemy->scale);
			modelMatrix *= transform2D::Rotate(enemy->rotation);
			enemy->ctx->RenderMesh2D(enemy->outter, shaders["VertexColor"], modelMatrix);
			enemy->ctx->RenderMesh2D(enemy->inner, shaders["VertexColor"], modelMatrix);
			enemy->scale -= 3.0f * deltaTime;
			enemy->rotation += DEG_TO_RAD(500.0f * deltaTime);
		}
		else {
			delete enemy;
			enemyTrash.erase(enemyTrash.begin() + i);
			i--;
		}
	}
}
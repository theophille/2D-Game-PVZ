#include "playerState.h"
#include "service.h"

using namespace game;

PlayerState::PlayerState(float x, float y, float margin, float livesSide, ResizableViewport* viewport, gfxc::SimpleScene* ctx)
	: lives(LIVES), hp(5), x(x), y(y), livesSide(livesSide), margin(margin), viewport(viewport), ctx(ctx) {
	float radius = livesSide * sqrtf(3.0f) / 3.0f;
	RegPolygone* triangle = new RegPolygone(-1, 3, radius, 0, true);
	triangleMesh = triangle->createMesh("lives", ColorSingleton::getInstance()->getColor("red"));
	delete triangle;

	Star* star = new Star(-1, 5, 20.0f, 10.0f);
	starMesh = star->createMesh("star", ColorSingleton::getInstance()->getColor("yellow"));
	delete star;

	Star* hp = new Star(-1, 5, 30.0f, 15.0f, 3.0f);
	hpMesh = hp->createMesh("hp", ColorSingleton::getInstance()->getColor("green"));
	delete hp;

	Plus* plus = new Plus(-1, 13.0f);
	plusMesh = plus->createMesh("plus", ColorSingleton::getInstance()->getColor("yellow"));
	delete plus;

	computePoints();

	Service::getInstance()->mouseEvent->subscribe(this, 1);
}

void PlayerState::draw() {
	std::unordered_map<std::string, Shader*> shaders = ctx->getShaders();

	glm::mat3 modelMatrix;

	for (int i = 0; i < lives; i++) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(livesPoints[i].x, livesPoints[i].y);
		ctx->RenderMesh2D(triangleMesh, shaders["VertexColor"], modelMatrix);
	}

	if (hp <= MAX_STARS_NUM) {
		for (int i = 0; i < hp; i++) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(starsPoints.at(i).x, starsPoints.at(i).y);
			ctx->RenderMesh2D(starMesh, shaders["VertexColor"], modelMatrix);
		}
	}
	else {
		for (int i = 0; i < MAX_STARS_NUM; i++) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(starsPoints.at(i).x, starsPoints.at(i).y);
			ctx->RenderMesh2D(starMesh, shaders["VertexColor"], modelMatrix);
		}

		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(starsPoints.at(MAX_STARS_NUM).x, starsPoints.at(MAX_STARS_NUM).y);
		ctx->RenderMesh2D(plusMesh, shaders["VertexColor"], modelMatrix);
	}
}

std::vector<glm::vec2> PlayerState::getStarsPoints() {
	std::vector<glm::vec2> starsPoints;

	if (hp <= MAX_STARS_NUM) {
		float starStep = 40.0f + margin;
		float lengthStars = starStep * (hp);
		float starsX = x - lengthStars / 2.0f;

		for (int i = 0; i < hp; i++) {
			starsPoints.push_back(
				glm::vec2(starsX + i * starStep + 20.0f, y - livesSide / 2.0f - 30.0f)
			);
		}
	}
	else {
		float starStep = 40.0f + margin;
		float lengthStars = starStep * (MAX_STARS_NUM + 1);
		float starsX = x - lengthStars / 2.0f;

		for (int i = 0; i < MAX_STARS_NUM + 1; i++) {
			starsPoints.push_back(
				glm::vec2(starsX + i * starStep + 20.0f, y - livesSide / 2.0f - 30.0f)
			);
		}
	}

	return starsPoints;
}

void PlayerState::resetLivesPoints() {
	float livesStep = livesSide + margin;
	float lengthLives = (livesSide + margin) * (lives - 1.0f);
	float livesX = x - lengthLives / 2.0f;

	for (int i = 0; i < lives; i++) {
		livesPoints[i] = glm::vec2(livesX + (float)i * livesStep, y);
	}
}

void PlayerState::computePoints() {
	resetLivesPoints();

	starsPoints = getStarsPoints();

	for (int i = 0; i < hp; i++) {
		std::cout << starsPoints.at(i).x << " " << starsPoints.at(i).y << std::endl;
	}
}

void PlayerState::generateHP() {
	if (elapsedTime >= HP_GEN_TIME) {
		elapsedTime = 0.0f;
	}

	if (elapsedTime == 0.0f) {
		for (int i = 0; i < HP_GEN_COUNT; i++) {
			hpPoints.push_back(HpStar(rand() % viewport->originalX, rand() % viewport->originalY));
		}
	}

	float deltaTime = Service::getInstance()->deltaTime;
	elapsedTime += deltaTime;
	std::unordered_map<std::string, Shader*> shaders = ctx->getShaders();

	int deleteThis = -1;

	for (int i = 0; i < hpPoints.size(); i++) {
		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(hpPoints.at(i).x, hpPoints.at(i).y);
		modelMatrix *= transform2D::Rotate(hpPoints.at(i).rotation);
		hpPoints.at(i).rotation -= DEG_TO_RAD(70.0f * deltaTime);

		if (hpPoints.at(i).doRemoveAnimation >= 0) {
			modelMatrix *= transform2D::Scale(hpPoints.at(i).scale, hpPoints.at(i).scale);
			hpPoints.at(i).scale -= 2.0f * deltaTime;

			if (hpPoints.at(i).scale < 0) {
				deleteThis = i;
			}
		}

		ctx->RenderMesh2D(hpMesh, shaders["VertexColor"], modelMatrix);
	}

	if (deleteThis >= 0) {
		hpPoints.erase(hpPoints.begin() + deleteThis);
	}
}

void PlayerState::update(int mouseX, int mouseY, int button, int type) {
	if (type == 1) {
		for (int i = 0; i < hpPoints.size(); i++) {
			float distance = glm::distance(glm::vec2(hpPoints.at(i).x, hpPoints.at(i).y), glm::vec2(mouseX, mouseY));

			if (distance <= 30.0f && hpPoints.at(i).doRemoveAnimation < 0) {
				hpPoints.at(i).doRemoveAnimation = i;
				hp++;

				std::cout << hp << std::endl;

				if (starsPoints.size() != MAX_STARS_NUM + 1) {
					starsPoints = getStarsPoints();
					break;
				}
			}
		}
	}
}

unsigned int PlayerState::getHP() {
	return hp;
}

void PlayerState::setHP(unsigned int hp) {
	this->hp = hp;
}

void PlayerState::setStarsPoints(std::vector<glm::vec2> sp) {
	starsPoints = sp;
}

unsigned int PlayerState::getLives() {
	return lives;
}

void PlayerState::setLives(unsigned int lives) {
	this->lives = lives;
}
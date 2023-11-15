#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstring>

#include "utils/glm_utils.h"
#include "core/gpu/mesh.h"
#include "components/simple_scene.h"
#include "regpoly.h"
#include "diamondGun.h"
#include "star.h"
#include "observer.h"
#include "colors.h"
#include "transform2d.h"
#include "constants.h"
#include "gun.h"
#include "responsiveViewport.h"

#define GUNS_NUM 4

namespace game
{
	class Guns: Observer {
	private:
		struct Bullet {
			float x;
			float y;
			float rotation;
			bool active;
			Bullet() : x(0), y(0), rotation(0.0f), active(true) {}
			Bullet(float x, float y) : x(x), y(y), rotation(0.0f), active(true) {}
		};

		float x, y, itemSide, margin;
		std::vector<game::Gun*> guns;
		gfxc::SimpleScene* ctx;
		Mesh* selectBoxMesh;
		Mesh* starMesh;
		Mesh* bulletMesh;
		std::vector<glm::vec2> selectBoxesPoints;
		std::vector<std::vector<glm::vec2>*> starsPoints;
		Board* board;
		ResizableViewport* viewport;

	public:
		std::vector<Bullet> bulletsPerLine[BOARD_SIZE][ENTITIES];
		Guns(float x, float y, float itemSide, float margin, Board* board, ResizableViewport* viewport, gfxc::SimpleScene* ctx);
		Gun* getGun(unsigned int id);
		std::vector<game::Gun*> getAllGuns();
		void computePoints();
		void draw();
		void generateBullet(float x, float y, unsigned int line, unsigned int colorId);
		void drawBullets();
		virtual void update(int mouseX, int mouseY, int button, int type) override;
	};
}
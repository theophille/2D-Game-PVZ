#pragma once

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "star.h"
#include "regpoly.h"
#include "plus.h"
#include "components/simple_scene.h"
#include "transform2d.h"
#include "colors.h"
#include "constants.h"
#include "observer.h"
#include "responsiveViewport.h"

#include <iostream>
#include <cmath>
#include <vector>

namespace game
{
	class PlayerState : Observer {
	private:
		struct HpStar {
			float x;
			float y;
			float scale;
			float rotation;
			int doRemoveAnimation;
			HpStar() : x(0), y(0), scale(1), rotation(0), doRemoveAnimation(-1) {}
			HpStar(float x, float y) : x(x), y(y), scale(1), rotation(0), doRemoveAnimation(-1) {}
		};

		float x, y, margin, livesSide;
		unsigned int lives;
		unsigned int hp;
		glm::vec2 livesPoints[LIVES];
		glm::vector<HpStar> hpPoints;
		glm::vector<glm::vec2> starsPoints;
		Mesh* triangleMesh;
		Mesh* starMesh;
		Mesh* hpMesh;
		Mesh* plusMesh;
		float elapsedTime = 0.0f;
		gfxc::SimpleScene* ctx;
		ResizableViewport* viewport;

	public:
		PlayerState(float x, float y, float margin, float livesSide, ResizableViewport* viewport, gfxc::SimpleScene* ctx);
		void computePoints();
		void draw();
		void generateHP();
		unsigned int getHP();
	    void setHP(unsigned int hp);
		unsigned int getLives();
	    void setLives(unsigned int lives);
		void resetLivesPoints();
		std::vector<glm::vec2> getStarsPoints();
		void setStarsPoints(std::vector<glm::vec2> sp);
		virtual void update(int mouseX, int mouseY, int button, int type) override;
	};
}
#pragma once

#include "components/simple_scene.h"
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "regpoly.h"
#include "transform2d.h"
#include "responsiveViewport.h"

namespace game
{
	class Board;
	class Enemy {
	private:
		float x, y;
		float lives;
		unsigned int line;
		unsigned int colorId;
		std::vector<Enemy*> arr;
		ResizableViewport* viewport;
		Board* board;

	public:
		float scale = 1.0f;
		float rotation = 0.0f;
		Mesh* outter;
		Mesh* inner;
		gfxc::SimpleScene* ctx;
		Enemy(float x, float y, float lives, Mesh *inner,
			Mesh* outter, unsigned int line, unsigned int colorId,
			Board* board, ResizableViewport* viewport, gfxc::SimpleScene* ctx);
		bool doRemoveAnimation = false;
		void draw();
		bool gotDamage();
		void setPosition(float x, float y);
		glm::vec2 getPosition();
		unsigned int getLine();
		unsigned int getColorId();
	};
}
#pragma once

#include "utils/glm_utils.h"
#include "core/gpu/mesh.h"
#include "components/simple_scene.h"
#include "transform2d.h"
#include "observer.h"
#include "constants.h"

#include <iostream>
#include <cmath>

namespace game
{
	class Guns;
	class Board;

	class Gun {
	public:
		float x, y;
		float scale = 1.0f;
		unsigned int cost;
		unsigned int line;
		unsigned int colorId;
		Mesh* mesh;
		Gun** doRemoveAnimation = NULL;
		gfxc::SimpleScene* ctx;
		bool active = false;
		Guns* guns;
		Board* board;
		float elapsedTime = 0.0f;

		Gun(float x, float y, unsigned int cost, unsigned int line,
			Mesh* mesh, unsigned int colorId, Guns* guns,
			Board* board, gfxc::SimpleScene* ctx);
		
		Gun(unsigned int cost, Mesh* mesh,
			unsigned int colorId, Guns* guns, Board* board, gfxc::SimpleScene* ctx);

		~Gun();

		void draw();
		void setPosition(float x, float y);
	};
}
#pragma once

#include "components/simple_scene.h"
#include "constants.h"
#include "core/gpu/mesh.h"
#include "enemy.h"
#include "colors.h"
#include "board.h"
#include "responsiveViewport.h"
#include "playerState.h"

#include <iostream>
#include <stdlib.h>
#include <vector>

namespace game
{
	class Enemies {
	private:
		Mesh* meshes[ENEMIES][2];
		float* linesY;
		float elapsedTime;
		Board* board;
		gfxc::SimpleScene* ctx;
		ResizableViewport* viewport;
		PlayerState* playerState;

	public:
		Enemies(Board* board, float* linesY, gfxc::SimpleScene* ctx, PlayerState* playerState, ResizableViewport* viewport);
		void generate(float deltaTime);
	};
}
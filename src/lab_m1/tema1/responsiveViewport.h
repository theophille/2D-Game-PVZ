#pragma once

#include "core/window/window_object.h"
#include "components/simple_scene.h"
#include "utils/glm_utils.h"
#include "constants.h"

#include <iostream>

namespace game
{
	class ResizableViewport {
	private:
		float aspectRatio;

	public:
		int originalX;
		int originalY;
		int width;
		int height;
		float leftX;
		float leftY;
		WindowObject* window;
		gfxc::SimpleScene* ctx;
		glm::ivec2 mouseCoords;

		ResizableViewport(WindowObject* window, gfxc::SimpleScene* ctx);
		void update();
		glm::ivec2 getMouseCoords(int mouseX, int mouseY);
	};
}
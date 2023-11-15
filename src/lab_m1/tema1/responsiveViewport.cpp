#include "responsiveViewport.h"

using namespace game;

ResizableViewport::ResizableViewport(WindowObject* window, gfxc::SimpleScene* ctx)
	: window(window), ctx(ctx) {
	glm::ivec2 resolution = window->GetResolution();
	aspectRatio = window->props.aspectRatio;
	width = originalX = resolution.x;
	height = originalY = resolution.y;
	leftX = 0.0f;
	leftY = 0.0f;
}

void ResizableViewport::update() {
	std::cout << "hei";
	glm::ivec2 res = window->GetResolution();

	if (window->props.aspectRatio <= aspectRatio) {
		width = res.x;
		height = (float)res.x / aspectRatio;
		leftX = 0.0f;
		leftY = (float)res.y / 2.0f - height / 2.0f;
	}
	else {
		width = (float)res.y * aspectRatio;
		height = res.y;
		leftX = (float)res.x / 2.0f - width / 2.0f;
		leftY = 0.0f;
	}
}

glm::ivec2 ResizableViewport::getMouseCoords(int mouseX, int mouseY) {
	glm::ivec2 res = window->GetResolution();
	int vpMouseX = ROUND((float)(mouseX - leftX) * (originalX / (float)width), 0);
	int vpMouseY = ROUND((float)((float)res.y - (float)mouseY - leftY) * (originalY / (float)height), 0);
	std::cout << vpMouseX << " " << vpMouseY << std::endl;
	return glm::ivec2(vpMouseX, vpMouseY);
}
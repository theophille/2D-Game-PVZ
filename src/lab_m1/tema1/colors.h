#pragma once

#include <string>
#include <unordered_map>

#include "utils/glm_utils.h"

#define CHANNEL_PERCENTAGE(value) ((value) / 255.0f)

namespace game
{
	class ColorSingleton {
	private:
		std::unordered_map<std::string, glm::vec3> colors;
		std::vector<glm::vec3> entitiesColors;
		static ColorSingleton* instance;
		ColorSingleton();

	public:
		ColorSingleton(const ColorSingleton& obj) = delete;
		static ColorSingleton* getInstance();
		glm::vec3 getColor(std::string color);
		std::vector<glm::vec3> getEntitiesColors();
	};
}
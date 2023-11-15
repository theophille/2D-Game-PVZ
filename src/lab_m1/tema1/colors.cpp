#include "colors.h"

using namespace game;

ColorSingleton* ColorSingleton::instance = NULL;

ColorSingleton::ColorSingleton() {
	colors["red"] = glm::vec3(
		CHANNEL_PERCENTAGE(164),
		CHANNEL_PERCENTAGE(36),
		CHANNEL_PERCENTAGE(59)
	);
	
	colors["background"] = glm::vec3(
		CHANNEL_PERCENTAGE(216),
		CHANNEL_PERCENTAGE(201),
		CHANNEL_PERCENTAGE(155)
	);
	
	colors["yellow"] = glm::vec3(
		CHANNEL_PERCENTAGE(216),
		CHANNEL_PERCENTAGE(151),
		CHANNEL_PERCENTAGE(60)
	);
	
	colors["purple"] = glm::vec3(
		CHANNEL_PERCENTAGE(146),
		CHANNEL_PERCENTAGE(44),
		CHANNEL_PERCENTAGE(92)
	);
	
	colors["darkPurple"] = glm::vec3(
		CHANNEL_PERCENTAGE(79),
		CHANNEL_PERCENTAGE(69),
		CHANNEL_PERCENTAGE(117)
	);
	
	colors["tile"] = glm::vec3(
		CHANNEL_PERCENTAGE(39),
		CHANNEL_PERCENTAGE(62),
		CHANNEL_PERCENTAGE(71)
	);

	colors["blue"] = glm::vec3(
		CHANNEL_PERCENTAGE(56),
		CHANNEL_PERCENTAGE(53),
		CHANNEL_PERCENTAGE(240)
	);

	colors["green"] = glm::vec3(
		CHANNEL_PERCENTAGE(40),
		CHANNEL_PERCENTAGE(141),
		CHANNEL_PERCENTAGE(125)
	);

	entitiesColors.push_back(colors["red"]);
	entitiesColors.push_back(colors["purple"]);
	entitiesColors.push_back(colors["darkPurple"]);
	entitiesColors.push_back(colors["yellow"]);
}

ColorSingleton* ColorSingleton::getInstance() {
	if (instance == NULL) {
		instance = new ColorSingleton();
		return instance;
	}
	else {
		return instance;
	}
}

glm::vec3 ColorSingleton::getColor(std::string color) {
	return colors.at(color);
}

std::vector<glm::vec3> ColorSingleton::getEntitiesColors() {
	return entitiesColors;
}
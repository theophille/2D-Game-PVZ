#pragma once

#include "shape.h"
#include "constants.h"
#include "core/gpu/mesh.h"

namespace game
{
	class Star : public Shape {
	private:
		unsigned int arms;
		float outterRadius;
		float innerRadius;
		float zIndex;

	public:
		Star(int id, unsigned int arms, float outterRadius, float innerRadius);
		Star(int id, unsigned int arms, float outterRadius, float innerRadius, float zIndex);
		virtual Mesh *createMesh(const std::string &name, glm::vec3 color) override;
	};
}
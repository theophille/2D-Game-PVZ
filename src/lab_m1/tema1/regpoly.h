#pragma once

#include "shape.h"
#include "core/gpu/mesh.h"

namespace game
{
	class RegPolygone : public Shape {
	private:
		unsigned int arms;
		float outterRadius;
		float angle;
		bool fill;
		float zIndex;

	public:
		RegPolygone(int id, unsigned int arms, float outterRadius);
		RegPolygone(int id, unsigned int arms, float outterRadius, float angle, bool fill);
		RegPolygone(int id, unsigned int arms, float outterRadius, float angle, bool fill, float zIndex);
		virtual Mesh* createMesh(const std::string& name, glm::vec3 color) override;
	};
}
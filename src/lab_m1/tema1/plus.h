#pragma once

#include "shape.h"
#include "core/gpu/mesh.h"

namespace game
{
	class Plus : public Shape {
	private:
		int id;
		float scale;
		float zIndex;

	public:
		Plus(int id, float scale);
		Plus(int id, float scale, float zIndex);
		virtual Mesh* createMesh(const std::string& name, glm::vec3 color) override;
	};
}
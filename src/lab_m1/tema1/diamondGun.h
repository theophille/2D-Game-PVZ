#pragma once

#include "shape.h"
#include "core/gpu/mesh.h"

namespace game
{
	class DiamondGun : public Shape {
	private:
		float D1;
		float D2;
		float L;

	public:
		DiamondGun(int id, float d1, float d2, float L);
		virtual Mesh* createMesh(const std::string& name, glm::vec3 color) override;
	};
}
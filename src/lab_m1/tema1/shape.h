#pragma once

#include <vector>
#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace game
{
	class Shape {
	private:
		int id;

	public:
		Shape(int id);
		virtual Mesh *createMesh(const std::string &name, glm::vec3 color) = 0;
		int getId();

	protected:
		std::vector<VertexFormat> vertices;
		std::vector<unsigned int> indices;
	};
}
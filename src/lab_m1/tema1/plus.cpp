#include "plus.h"

using namespace game;

Plus::Plus(int id, float scale) : Shape(id), id(id), scale(scale), zIndex(0.0f) {}
Plus::Plus(int id, float scale, float zIndex) : Shape(id), id(id), scale(scale), zIndex(zIndex) {}

Mesh* Plus::createMesh(const std::string& name, glm::vec3 color) {
	vertices = {
		VertexFormat(glm::vec3(0, 0, zIndex), color),
		VertexFormat(glm::vec3(scale / 3.0f, scale, zIndex), color),
		VertexFormat(glm::vec3(scale / 3.0f, scale / 3.0f, zIndex), color),
		VertexFormat(glm::vec3(scale, scale / 3.0f, zIndex), color),
		VertexFormat(glm::vec3(scale, -scale / 3.0f, zIndex), color),
		VertexFormat(glm::vec3(scale / 3.0f, -scale / 3.0f, zIndex), color),
		VertexFormat(glm::vec3(scale / 3.0f, -scale, zIndex), color),
		VertexFormat(glm::vec3(-scale / 3.0f, -scale, zIndex), color),
		VertexFormat(glm::vec3(-scale / 3.0f, -scale / 3.0f, zIndex), color),
		VertexFormat(glm::vec3(-scale, -scale / 3.0f, zIndex), color),
		VertexFormat(glm::vec3(-scale, scale / 3.0f, zIndex), color),
		VertexFormat(glm::vec3(-scale / 3.0f, scale / 3.0f, zIndex), color),
		VertexFormat(glm::vec3(-scale / 3.0f, scale, zIndex), color),
	};

	indices = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1
	};

	Mesh* plus = new Mesh(name);
	plus->SetDrawMode(GL_TRIANGLE_FAN);
	plus->InitFromData(vertices, indices);

	return plus;
}
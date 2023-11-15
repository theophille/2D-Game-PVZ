#include "star.h"

#include <cmath>
#include <iostream>

using namespace game;

Star::Star(int id, unsigned int arms, float outterRadius, float innerRadius)
	: Shape(id), arms(arms), outterRadius(outterRadius), innerRadius(innerRadius), zIndex(0.0f) {}

Star::Star(int id, unsigned int arms, float outterRadius, float innerRadius, float zIndex)
	: Shape(id), arms(arms), outterRadius(outterRadius), innerRadius(innerRadius), zIndex(zIndex) {}

Mesh *Star::createMesh(const std::string &name, glm::vec3 color) {
	unsigned int decimalPlaces = 2;
	unsigned int slices = 2 * arms;
	float alpha = 360.0f / (float)slices;
	this->vertices.push_back(VertexFormat(glm::vec3(0, 0, zIndex), color));

	for (int i = 0; i < slices; i++) {
		float currentAngle = i * alpha;

		if (i % 2 == 0) {
			this->vertices.push_back(
				VertexFormat(
					glm::vec3(
						outterRadius * ROUND(cos(DEG_TO_RAD(90.0f - currentAngle)), 2),
						outterRadius * ROUND(cos(DEG_TO_RAD(currentAngle)), 2),
						zIndex
					),
					color
				)
			);
		}
		else {
			this->vertices.push_back(
				VertexFormat(
					glm::vec3(
						innerRadius * ROUND(cos(DEG_TO_RAD(90.0f - currentAngle)), 2),
						innerRadius * ROUND(cos(DEG_TO_RAD(currentAngle)), 2),
						zIndex
					),
					color
				)
			);
		}
	}

	for (int i = 1; i <= slices; i++) {
		indices.push_back(0);
		indices.push_back(i);
		(i + 1) <= slices ?
			indices.push_back(i + 1) :
			indices.push_back(1);
	}

	Mesh* star = new Mesh(name);

	star->InitFromData(vertices, indices);

	return star;
}
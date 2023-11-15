#include "regpoly.h"

#include <cmath>
#include <iostream>

#include "lab_m1/tema1/transform2d.h"

#define RAD_CONST M_PI / 180.0
#define DEG_TO_RAD(degrees) ((degrees) * RAD_CONST)
#define ROUND(value, decimalPlaces) \
    (std::round((value) * std::pow(10, (decimalPlaces))) / std::pow(10, (decimalPlaces)))

using namespace game;

RegPolygone::RegPolygone(int id, unsigned int arms, float outterRadius)
	: Shape(id), arms(arms), outterRadius(outterRadius), angle(0), fill(true), zIndex(0) {}

RegPolygone::RegPolygone(int id, unsigned int arms, float outterRadius, float angle, bool fill)
	: Shape(id), arms(arms), outterRadius(outterRadius), angle(angle), fill(fill), zIndex(0) {}

RegPolygone::RegPolygone(int id, unsigned int arms, float outterRadius, float angle, bool fill, float zIndex)
	: Shape(id), arms(arms), outterRadius(outterRadius), angle(angle), fill(fill), zIndex(zIndex) {}

Mesh* RegPolygone::createMesh(const std::string& name, glm::vec3 color) {
	unsigned int decimalPlaces = 2;
	float alpha = 360.0f / (float)arms;
	this->vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color));

	for (int i = 0; i < arms; i++) {
		float currentAngle = i * alpha;

		this->vertices.push_back(
			VertexFormat(
				transform2D::Rotate(DEG_TO_RAD(angle)) * glm::vec3(
					outterRadius * ROUND(cos(DEG_TO_RAD(90.0f - currentAngle)), 2),
					outterRadius * ROUND(cos(DEG_TO_RAD(currentAngle)), 2),
					zIndex
				),
				color
			)
		);
	}

	Mesh* regpoly = new Mesh(name);

	if (!fill) {
		regpoly->SetDrawMode(GL_LINE_LOOP);

		for (int i = 1; i <= arms; i++) {
			indices.push_back(i);
		}
	}
	else {
		for (int i = 1; i <= arms; i++) {
			indices.push_back(0);
			indices.push_back(i);
			(i + 1) <= arms ?
				indices.push_back(i + 1) :
				indices.push_back(1);
		}
	}

	regpoly->InitFromData(vertices, indices);

	return regpoly;
}
#include "diamondGun.h"

#include <cmath>
#include <iostream>

#define RAD_CONST M_PI / 180.0
#define DEG_TO_RAD(degrees) ((degrees) * RAD_CONST)
#define ROUND(value, decimalPlaces) \
    (std::round((value) * std::pow(10, (decimalPlaces))) / std::pow(10, (decimalPlaces)))
#define VERTEX_COUNT 8

using namespace game;

DiamondGun::DiamondGun(int id, float D1, float D2, float L) : Shape(id) {
	this->D1 = D1;
	this->D2 = D2;
	this->L = L;
}

Mesh* DiamondGun::createMesh(const std::string& name, glm::vec3 color) {
	float l = L / 2.0f;
	float d1 = D1 / 2.0f;
	float d2 = D2 / 2.0f;
	float a = (d2 * (d1 - l)) / d1;

	std::cout << a << std::endl;

	vertices = {
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0, d1, 0), color),
		VertexFormat(glm::vec3(a, l, 0), color),
		VertexFormat(glm::vec3(2 * d2, l, 0), color),
		VertexFormat(glm::vec3(2 * d2, -l, 0), color),
		VertexFormat(glm::vec3(a, -l, 0), color),
		VertexFormat(glm::vec3(0, -d1, 0), color),
		VertexFormat(glm::vec3(-d2, 0, 0), color)
	};

	indices = {
		0, 1, 2, 3, 4, 5, 6, 7, 1
	};

	Mesh* regpoly = new Mesh(name);
	regpoly->SetDrawMode(GL_TRIANGLE_FAN);
	regpoly->InitFromData(vertices, indices);

	return regpoly;
}
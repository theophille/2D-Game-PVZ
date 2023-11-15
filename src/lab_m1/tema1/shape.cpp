#include "shape.h"

using namespace game;

Shape::Shape(int id) {
	this->id = id;
}

int Shape::getId() {
	return this->id;
}
#include "mouseEvent.h"

using namespace game;

MouseEvent::MouseEvent()
	: mouseX(-1), mouseY(-1), button(-1), type(-1) {}

void MouseEvent::setEvent(int mouseX, int mouseY, int button, int type) {
	this->mouseX = mouseX;
	this->mouseY = mouseY;
	this->button = button;
	this->type = type;

	notifyObservers(button);
}

void MouseEvent::subscribe(Observer* obs, int subscription) {
	if (subscription == 1) {
		leftClickObservers.push_back(obs);
	}
	else {
		rightClickObservers.push_back(obs);
	}
}

void MouseEvent::unsubscribe(Observer* obs, int subscription) {
	if (subscription == 1) {
		auto iter = std::find(leftClickObservers.begin(), leftClickObservers.end(), obs);

		if (iter != leftClickObservers.end()) {
			leftClickObservers.erase(iter);
		}
	}
	else {
		auto iter = std::find(rightClickObservers.begin(), rightClickObservers.end(), obs);

		if (iter != rightClickObservers.end()) {
			rightClickObservers.erase(iter);
		}
	}
}

void MouseEvent::notifyObservers(int subscription) {
	if (subscription == 1) {
		for (int i = 0; i < leftClickObservers.size(); i++) {
			leftClickObservers.at(i)->update(mouseX, mouseY, button, type);
		}
	}
	else {
		for (int i = 0; i < rightClickObservers.size(); i++) {
			rightClickObservers.at(i)->update(mouseX, mouseY, button, type);
		}
	}
}
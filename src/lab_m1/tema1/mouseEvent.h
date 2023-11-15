#pragma once

#include "subject.h"

#include <vector>

namespace game
{
	class MouseEvent : public Subject {
	private:
		std::vector<Observer*> leftClickObservers;
		std::vector<Observer*> rightClickObservers;
		static MouseEvent* instance;

	public:
		int mouseX, mouseY, button, type;

		MouseEvent();
		void setEvent(int mouseX, int mouseY, int button, int type);
		virtual void subscribe(Observer* obs, int subscription) override;
		virtual void unsubscribe(Observer* obs, int subscription) override;
		virtual void notifyObservers(int subscription) override;
	};
}
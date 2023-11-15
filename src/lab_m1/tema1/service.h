#pragma once

#include <iostream>
#include "gun.h"
#include "enemy.h"

#include "mouseEvent.h"

namespace game
{
	class Service {
	private:
		Service();
		static Service* instance;

	public:
		Gun* dragged;
		Gun* dropped;
		MouseEvent* mouseEvent;
		std::vector<Enemy*> enemyTrash;
		void emptyEnemyTrash();
		float deltaTime;
		Service(const Service& obj) = delete;
		static Service* getInstance();
	};
}
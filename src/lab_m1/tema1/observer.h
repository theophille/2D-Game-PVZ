#pragma once

class Observer {
public:
	virtual void update(int x, int y, int button, int type) = 0;
};
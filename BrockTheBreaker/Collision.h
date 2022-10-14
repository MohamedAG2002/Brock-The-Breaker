#pragma once

#include "GameObject.h"

class Collision
{
public:
	void Update();
	bool OnCollision(GameObject& go1, GameObject& go2);
};
extern Collision collision;
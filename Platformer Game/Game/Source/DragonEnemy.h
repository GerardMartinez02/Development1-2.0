#ifndef __WALKING_ENEMY_H__
#define __WALKING_ENEMY_H__

#include "ModuleEnemy.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Box2D/Box2D/Box2D.h"
#include "ModuleFadeToBlack.h"
#include "Path.h"

struct SDL_Texture;
struct Collider;
struct Path;

class DragonEnemy : public ModuleEnemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	DragonEnemy(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update(float dt) override;

	virtual void OnCollision(Collider* collider);

private:
	// A set of steps that define the position in the screen
	// And an animation for each step

	//NEED TO ADD THE ANIMATIONS
	//Animation Right;
	//Animation Left;

	Path path;

	int coolDown;
};

#endif #pragma once

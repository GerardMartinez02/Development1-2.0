#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "app.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Audio.h"
#include "ModulePhysics.h"
#include "SceneIntro.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleEnemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	ModuleEnemy(int x, int y);

	// Destructor
	virtual ~ModuleEnemy();

	// Returns the enemy's collider
	

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update(float dt);

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* collider);
	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

public:
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* Enemytexture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	int health;
	bool invincible = false;
	bool powerUp = true;
	iPoint direction = { 0, 0 };

	List<PhysBody*> dragonCounter;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENEMY_H__
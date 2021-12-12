#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Box2D/Box2D/Box2D.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"
#include "Collider.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer();

	// Destructor
	~ModulePlayer();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start() override;

	// Called each loop iteration
	bool Update(float dt) override;

	// Called before all Updates
	bool PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* bodyA, Collider* bodyB) override;

	bool loadState(pugi::xml_node&);
	bool saveState(pugi::xml_node&) const;

	// Called before quitting
	bool CleanUp();

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	PhysBody* pbody;
	b2Body* b;
	

	b2CircleShape pCircle;
	b2PolygonShape pBox;


	int speed = 1;
	bool jumpState = false;
	int jumpsCount;
	bool running = false;
	bool death;
	
	bool winCondition = false;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation lookUpAnim;
	Animation lookDownAnim;
	Animation leftAnim;
	Animation runLeftAnim;
	Animation jumpLeftAnim;
	Animation rightAnim;
	Animation runRightAnim;
	Animation jumpRightAnim;

	int currentScene;
	
	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	int horizontalMargin = 45;

	//Margin of movement

	bool debugMode;
	bool horizonalCamera;
	bool verticalCamera;

};

#endif //!__MODULE_PLAYER_H__
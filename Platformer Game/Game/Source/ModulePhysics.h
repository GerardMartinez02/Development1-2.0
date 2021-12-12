#pragma once
#include "Module.h"
#include "App.h"
#include "Box2D/Box2D/Box2D.h"
#include "Collider.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -6.0f

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)
struct Type;

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int& y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
	Type* type;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics();
	~ModulePhysics();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius, int dynamicBody);
	PhysBody* CreateStaticCircle(int x, int y, int radius);
	PhysBody* CreateRectangle(int x, int y, int width, int height, int dynamicBody);
	PhysBody* CreateBouncer(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, int dynamicBody);
	PhysBody* CreateChain(int x, int y, int* points, int size);
	PhysBody* CreateFlipper(int x, int y, int* points, int size);

	PhysBody* CreatePlayer(int x, int y, int width, int height);
	PhysBody* CreateDragon(int x, int y, int width, int height);

	void CreateFlipperJoints();
	void CreateBouncerJoint();


	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	b2World* world;

private:

	bool debug;
	
	b2Body* body_clicked;
	b2Body* ground;
	b2DistanceJoint* BouncerJoint;
}; 
#pragma once

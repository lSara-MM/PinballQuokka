#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define RAD_PER_DEG ((float)180/b2_pi)
#define DEG_PER_RAD ((float)b2_pi/180)

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

#define RAD_TO_DEG(r) ((float) RAD_PER_DEG * r)
#define DEG_TO_RAD(r) ((float) DEG_PER_RAD * r)

enum class ColliderType {
	BALL,
	GREEN_PAW,
	PURPLE_PAW,
	TURQUOISE_PAW,
	PINK_PAW,
	ORANGE_BUMPER,
	SLINGERSHOT,
	EARS,
	ROD,
	CHEEK,
	OVAL,
	PLATFORM,
	BELL,
	UNKNOWN
	// ..
};
// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody();
	~PhysBody();

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
	ColliderType ctype;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	
	// Constructors & Destructors
	ModulePhysics(Application* app, bool start_enabled = false);
	~ModulePhysics();

	// Main module steps
	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	// Create main ground
	void CreateScenarioGround();

	//BodyTypes

	enum BodyType
	{
		STATIC,
		KINEMATIK,
		DYNAMIC,
	};

	// Create basic physics objects
	PhysBody* CreateCircle(int x, int y, int radius, BodyType type, ColliderType collType);
	PhysBody* CreateBouncyCircle(int x, int y, int radius, float bounce, BodyType type, ColliderType collType);
	PhysBody* CreateRectangle(int x, int y, int width, int height, BodyType type ,ColliderType collType);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, ColliderType collType);
	PhysBody* CreateChain(int x, int y, int* points, int size, BodyType type, ColliderType collType);
	PhysBody* CreateBouncyChain(int x, int y, int* points, int size, float bounce, BodyType type, ColliderType collType);

	b2RevoluteJoint* CreateRevoluteJoint(PhysBody* A, b2Vec2 anchorA, PhysBody* B, b2Vec2 anchorB, float angle = 0.0f, bool collideConnected = false, bool enableLimit = true);
	b2PrismaticJoint* CreatePrismaticJoint(PhysBody* A, b2Vec2 anchorA, PhysBody* B, b2Vec2 anchorB, b2Vec2 axys, float minHeigth=0.0f, float maxHeight = 0.0f, bool collideConnected = true, bool enableLimit = true);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	// Box2D World
	b2World* world;

private:
	// Main ground
	b2Body* ground;

	// Mouse joint
	b2MouseJoint* mouse_joint;
	b2Body* mouse_body;

public:
	// Debug mode
	bool debug;
	float GRAVITY_Y = -7.0f;
};
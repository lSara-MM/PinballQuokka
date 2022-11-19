#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"
#include "ModuleScene.h"

// Tell the compiler to reference the compiled Box2D libraries
#ifdef _DEBUG
	#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
	#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	// Initialise all the internal class variables, at least to NULL pointer
	world = NULL;
	ground = NULL;
	mouse_joint = NULL;
	mouse_body = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
	// You should do some memory cleaning here, if required
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// Create a new World
	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));

	// Set this module as a listener for contacts
	world->SetContactListener(this);

	
	// Create a static, shapeless ground body
	// This will be used to create joints like a mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd); // Add the static ground body to the World

	return true;
}

update_status ModulePhysics::PreUpdate()
{
	// Step (update) the World
	// WARNING: WE ARE STEPPING BY CONSTANT 1/60 SECONDS!
	world->Step(1.0f / frames, 6, 2);

	// Because Box2D does not automatically broadcast collisions/contacts with sensors, 
	// we have to manually search for collisions and "call" the equivalent to the ModulePhysics::BeginContact() ourselves...
	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		// For each contact detected by Box2D, see if the first one colliding is a sensor
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			// If so, we call the OnCollision listener function (only of the sensor), passing as inputs our custom PhysBody classes
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	// Keep playing
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{
	// Activate or deactivate debug mode
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		debug = !debug;
	}

	// FPS Change

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		fps = true;
		LOG("frames %f", frames);
	}

	if (fps)
	{
		if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			frames = 0;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
			frames = 10;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
			frames = 20;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
			frames = 30;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {
			frames = 40;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
			frames = 50;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
			frames = 60;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
			frames = 70;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
			frames = 80;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
			frames = 90;
			fps = false;
		}
	}

	// Gravity Change

		//PhysBody* grav = CreateRectangle(100, 200, 30, 30, BodyType::STATIC, ColliderType::UNKNOWN);

		//b2Vec2 pos;
		//pos = grav->body->GetPosition();

		//// If mouse is over this circle, paint the circle's texture
		//if (grav->Contains(App->input->GetMouseX(), App->input->GetMouseY())) 
		//{
		//	if (App->input->GetKey(SDL_BUTTON_LEFT) == KEY_DOWN) {

		//	}
		//}

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		grav = true;
		LOG("GRAVITY %f", GRAVITY_Y);
	}

	if (grav) 
	{
		if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			GRAVITY_Y = -0;
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
			GRAVITY_Y = -1;
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
			GRAVITY_Y = -2;
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
			GRAVITY_Y = -3;
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {
			GRAVITY_Y = -4;
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
			GRAVITY_Y = -5;
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
			GRAVITY_Y = -6;
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
			GRAVITY_Y = -7;
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
			GRAVITY_Y = -8;
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
			GRAVITY_Y = -9;
			grav = false;
		}
	}

	// Bouncing coefficient

	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) {
		boing = true;
		LOG("Boing %f", App->scene->bounce);
	}

	if (fps)
	{
		if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			App->scene->bounce = 0;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
			App->scene->bounce = 1;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
			App->scene->bounce = 2;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
			App->scene->bounce = 3;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {
			App->scene->bounce = 4;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
			App->scene->bounce = 5;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
			App->scene->bounce = 6;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
			App->scene->bounce = 7;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
			App->scene->bounce = 8;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
			App->scene->bounce = 9;
			boing = false;
		}
	}

	// If we are not in debug mode, do nothing else here and Keep playing
	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 0, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}

			// TODO 1: If mouse button 1 is pressed ...
			// App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				// test if the current body contains mouse position
				b2Vec2 p = { PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()) };
				if (f->GetShape()->TestPoint(b->GetTransform(), p) == true)
				{

					// If a body was selected we will attach a mouse joint to it
					// so we can pull it around

					// TODO 2: If a body was selected, create a mouse joint
					// using mouse_joint class property

					// NOTE: you do TODO2 here or also in the original handout's location. 
					// It doesn't matter unless you are triggering several objects at once;
					// I leave it to you to add safety checks to avoid re-defining several mouse joints.

					// The variable "b2Body* mouse_body;" is defined in the header ModulePhysics.h 
					// We need to keep this body throughout several game frames; you cannot define it as a local variable here. 
					mouse_body = b;

					// Get current mouse position
					b2Vec2 mousePosition;
					mousePosition.x = p.x;
					mousePosition.y = p.y;

					// Define new mouse joint
					b2MouseJointDef def;
					def.bodyA = ground; // First body must be a static ground
					def.bodyB = mouse_body; // Second body will be the body to attach to the mouse
					def.target = mousePosition; // The second body will be pulled towards this location
					def.dampingRatio = 0.5f; // Play with this value
					def.frequencyHz = 2.0f; // Play with this value
					def.maxForce = 200.0f * mouse_body->GetMass(); // Play with this value

					// Add the new mouse joint into the World
					mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
				}
			}
		}
	}



	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	if (mouse_body != nullptr && mouse_joint != nullptr)
	{
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			// Get new mouse position and re-target mouse_joint there
			b2Vec2 mousePosition;
			mousePosition.x = PIXEL_TO_METERS(App->input->GetMouseX());
			mousePosition.y = PIXEL_TO_METERS(App->input->GetMouseY());
			mouse_joint->SetTarget(mousePosition);

			// Draw a red line between both anchor points
			App->renderer->DrawLine(METERS_TO_PIXELS(mouse_body->GetPosition().x), METERS_TO_PIXELS(mouse_body->GetPosition().y), App->input->GetMouseX(), App->input->GetMouseY(), 255, 0, 0);
		}
	}

	// TODO 4: If the player releases the mouse button, destroy the joint
	if (mouse_body != nullptr && mouse_joint != nullptr)
	{
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP)
		{
			// Tell Box2D to destroy the mouse_joint
			world->DestroyJoint(mouse_joint);

			// DO NOT FORGET THIS! We need it for the "if (mouse_body != nullptr && mouse_joint != nullptr)"
			mouse_joint = nullptr; 
			mouse_body = nullptr;
		}
	}

	// Keep playing
	return UPDATE_CONTINUE;
}

bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void ModulePhysics::CreateScenarioGround()
{
	// Get coordinates of the screen center and radius
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	// Create a static body in the middle of the screen
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	// Add this static body to the World
	b2Body* big_ball = world->CreateBody(&body);

	// Create a big circle shape
	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;

	// Create a fixture and associate the circle to it
	b2FixtureDef fixture;
	fixture.shape = &shape;
	// Add the ficture (plus shape) to the static body
	big_ball->CreateFixture(&fixture);
}

b2RevoluteJoint* ModulePhysics::CreateRevoluteJoint(PhysBody* A, b2Vec2 anchorA, PhysBody* B, b2Vec2 anchorB, float angle, bool collideConnected, bool enableLimit)
{
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = A->body;
	revoluteJointDef.bodyB = B->body;
	revoluteJointDef.collideConnected = collideConnected;
	revoluteJointDef.localAnchorA.Set(anchorA.x, anchorA.y);
	revoluteJointDef.localAnchorB.Set(anchorB.x, anchorB.y);
	revoluteJointDef.referenceAngle = 0;
	revoluteJointDef.enableLimit = enableLimit;
	revoluteJointDef.lowerAngle = -DEG_TO_RAD(angle);
	revoluteJointDef.upperAngle = DEG_TO_RAD(angle);

	return (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
}

b2PrismaticJoint* ModulePhysics::CreatePrismaticJoint(PhysBody* A, b2Vec2 anchorA, PhysBody* B, b2Vec2 anchorB, b2Vec2 axys, float minHeigth, float maxHeight, bool collideConnected, bool enableLimit)
{
	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.bodyA = A->body;
	prismaticJointDef.bodyB = B->body;
	prismaticJointDef.collideConnected = collideConnected;
	prismaticJointDef.localAxisA.Set(axys.x, axys.y);
	prismaticJointDef.localAnchorA.Set(anchorA.x, anchorA.y);
	prismaticJointDef.localAnchorB.Set(anchorB.x, anchorB.y);
	prismaticJointDef.referenceAngle = 0;
	prismaticJointDef.enableLimit = enableLimit;
	prismaticJointDef.lowerTranslation = minHeigth;
	prismaticJointDef.upperTranslation = maxHeight;

	return (b2PrismaticJoint*)world->CreateJoint(&prismaticJointDef);
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, BodyType type, ColliderType collType)
{
	// Create BODY at position x,y
	b2BodyDef body;
	if (type == BodyType::DYNAMIC) { body.type = b2_dynamicBody; }
	if (type == BodyType::KINEMATIK) { body.type = b2_kinematicBody; }
	if (type == BodyType::STATIC) { body.type = b2_staticBody; }
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	// Add BODY to the world
	b2Body* b = world->CreateBody(&body);

	// Create SHAPE
	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);

	// Create FIXTURE
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	// Add fixture to the BODY
	b->CreateFixture(&fixture);

	// Create our custom PhysBody class
	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	if (collType == ColliderType::UNKNOWN) { pbody->ctype = ColliderType::UNKNOWN; }
	if (collType == ColliderType::GREEN_PAW) { pbody->ctype = ColliderType::GREEN_PAW; }
	if (collType == ColliderType::PURPLE_PAW) { pbody->ctype = ColliderType::PURPLE_PAW; }
	if (collType == ColliderType::TURQUOISE_PAW) { pbody->ctype = ColliderType::TURQUOISE_PAW; }
	if (collType == ColliderType::PINK_PAW) { pbody->ctype = ColliderType::PINK_PAW; }
	if (collType == ColliderType::PLATFORM) { pbody->ctype = ColliderType::PLATFORM; }
	if (collType == ColliderType::ORANGE_BUMPER) { pbody->ctype = ColliderType::ORANGE_BUMPER; }
	if (collType == ColliderType::OVAL) { pbody->ctype = ColliderType::OVAL; }
	if (collType == ColliderType::BELL) { pbody->ctype = ColliderType::BELL; }
	if (collType == ColliderType::ROD) { pbody->ctype = ColliderType::ROD; }
	if (collType == ColliderType::CHEEK) { pbody->ctype = ColliderType::CHEEK; }
	if (collType == ColliderType::SLINGERSHOT) { pbody->ctype = ColliderType::SLINGERSHOT; }
	if (collType == ColliderType::EARS) { pbody->ctype = ColliderType::EARS; }

	// Return our PhysBody class
	return pbody;
}

PhysBody* ModulePhysics::CreateBouncyCircle(int x, int y, int radius, float bounce, BodyType type, ColliderType collType)
{
	// Create BODY at position x,y
	b2BodyDef body;
	if (type == BodyType::DYNAMIC) { body.type = b2_dynamicBody; }
	if (type == BodyType::KINEMATIK) { body.type = b2_kinematicBody; }
	if (type == BodyType::STATIC) { body.type = b2_staticBody; }
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	// Add BODY to the world
	b2Body* b = world->CreateBody(&body);

	// Create SHAPE
	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);

	// Create FIXTURE
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	//Bounce
	fixture.restitution = bounce;

	// Add fixture to the BODY
	b->CreateFixture(&fixture);

	// Create our custom PhysBody class
	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	if (collType == ColliderType::UNKNOWN) { pbody->ctype = ColliderType::UNKNOWN; }
	if (collType == ColliderType::GREEN_PAW) { pbody->ctype = ColliderType::GREEN_PAW; }
	if (collType == ColliderType::PURPLE_PAW) { pbody->ctype = ColliderType::PURPLE_PAW; }
	if (collType == ColliderType::TURQUOISE_PAW) { pbody->ctype = ColliderType::TURQUOISE_PAW; }
	if (collType == ColliderType::PINK_PAW) { pbody->ctype = ColliderType::PINK_PAW; }
	if (collType == ColliderType::PLATFORM) { pbody->ctype = ColliderType::PLATFORM; }
	if (collType == ColliderType::ORANGE_BUMPER) { pbody->ctype = ColliderType::ORANGE_BUMPER; }
	if (collType == ColliderType::OVAL) { pbody->ctype = ColliderType::OVAL; }
	if (collType == ColliderType::BELL) { pbody->ctype = ColliderType::BELL; }
	if (collType == ColliderType::ROD) { pbody->ctype = ColliderType::ROD; }
	if (collType == ColliderType::CHEEK) { pbody->ctype = ColliderType::CHEEK; }
	if (collType == ColliderType::SLINGERSHOT) { pbody->ctype = ColliderType::SLINGERSHOT; }
	if (collType == ColliderType::EARS) { pbody->ctype = ColliderType::EARS; }

	// Return our PhysBody class
	return pbody;
}


PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height, BodyType type, ColliderType collType)
{
	// Create BODY at position x,y
	b2BodyDef body;
	if (type == BodyType::DYNAMIC) { body.type = b2_dynamicBody; }
	if (type == BodyType::KINEMATIK) { body.type = b2_kinematicBody; }
	if (type == BodyType::STATIC) { body.type = b2_staticBody; }
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	// Add BODY to the world
	b2Body* b = world->CreateBody(&body);

	// Create SHAPE
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	// Create FIXTURE
	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	// Add fixture to the BODY
	b->CreateFixture(&fixture);

	// Create our custom PhysBody class
	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	if (collType == ColliderType::UNKNOWN) { pbody->ctype = ColliderType::UNKNOWN; }
	if (collType == ColliderType::GREEN_PAW) { pbody->ctype = ColliderType::GREEN_PAW; }
	if (collType == ColliderType::PURPLE_PAW) { pbody->ctype = ColliderType::PURPLE_PAW; }
	if (collType == ColliderType::TURQUOISE_PAW) { pbody->ctype = ColliderType::TURQUOISE_PAW; }
	if (collType == ColliderType::PINK_PAW) { pbody->ctype = ColliderType::PINK_PAW; }
	if (collType == ColliderType::PLATFORM) { pbody->ctype = ColliderType::PLATFORM; }
	if (collType == ColliderType::ORANGE_BUMPER) { pbody->ctype = ColliderType::ORANGE_BUMPER; }
	if (collType == ColliderType::OVAL) { pbody->ctype = ColliderType::OVAL; }
	if (collType == ColliderType::BELL) { pbody->ctype = ColliderType::BELL; }
	if (collType == ColliderType::ROD) { pbody->ctype = ColliderType::ROD; }
	if (collType == ColliderType::CHEEK) { pbody->ctype = ColliderType::CHEEK; }
	if (collType == ColliderType::SLINGERSHOT) { pbody->ctype = ColliderType::SLINGERSHOT; }
	if (collType == ColliderType::EARS) { pbody->ctype = ColliderType::EARS; }
	// Return our PhysBody class
	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height, ColliderType collType)
{
	// Create BODY at position x,y
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	// Add BODY to the world
	b2Body* b = world->CreateBody(&body);

	// Create SHAPE (small "box" rectangle is ok; otherwise create whatever you need)
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	// Create FIXTURE
	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true; // Set this fixture as SENSOR type

	// Add fixture to the BODY
	b->CreateFixture(&fixture);

	// Create our custom PhysBody class
	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	if (collType == ColliderType::UNKNOWN) { pbody->ctype = ColliderType::UNKNOWN; }
	if (collType == ColliderType::GREEN_PAW) { pbody->ctype = ColliderType::GREEN_PAW; }
	if (collType == ColliderType::PURPLE_PAW) { pbody->ctype = ColliderType::PURPLE_PAW; }
	if (collType == ColliderType::TURQUOISE_PAW) { pbody->ctype = ColliderType::TURQUOISE_PAW; }
	if (collType == ColliderType::PINK_PAW) { pbody->ctype = ColliderType::PINK_PAW; }
	if (collType == ColliderType::PLATFORM) { pbody->ctype = ColliderType::PLATFORM; }
	if (collType == ColliderType::ORANGE_BUMPER) { pbody->ctype = ColliderType::ORANGE_BUMPER; }
	if (collType == ColliderType::OVAL) { pbody->ctype = ColliderType::OVAL; }
	if (collType == ColliderType::BELL) { pbody->ctype = ColliderType::BELL; }
	if (collType == ColliderType::ROD) { pbody->ctype = ColliderType::ROD; }
	if (collType == ColliderType::CHEEK) { pbody->ctype = ColliderType::CHEEK; }
	if (collType == ColliderType::SLINGERSHOT) { pbody->ctype = ColliderType::SLINGERSHOT; }
	if (collType == ColliderType::EARS) { pbody->ctype = ColliderType::EARS; }
	// Return our PhysBody class
	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size, BodyType type, ColliderType collType)
{
	// Create BODY at position x,y
	b2BodyDef body;
	if (type==BodyType::DYNAMIC) {body.type = b2_dynamicBody;}
	if (type == BodyType::KINEMATIK) { body.type = b2_kinematicBody; }
	if (type == BodyType::STATIC) { body.type = b2_staticBody; }
	
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	// Add BODY to the world
	b2Body* b = world->CreateBody(&body);

	// Create SHAPE
	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];
	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}
	shape.CreateLoop(p, size / 2);

	// Create FIXTURE
	b2FixtureDef fixture;
	fixture.shape = &shape;

	// Add fixture to the BODY
	b->CreateFixture(&fixture);

	// Clean-up temp array
	delete p;

	// Create our custom PhysBody class
	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	if (collType == ColliderType::UNKNOWN) { pbody->ctype = ColliderType::UNKNOWN; }
	if (collType == ColliderType::GREEN_PAW) { pbody->ctype = ColliderType::GREEN_PAW; }
	if (collType == ColliderType::PURPLE_PAW) { pbody->ctype = ColliderType::PURPLE_PAW; }
	if (collType == ColliderType::TURQUOISE_PAW) { pbody->ctype = ColliderType::TURQUOISE_PAW; }
	if (collType == ColliderType::PINK_PAW) { pbody->ctype = ColliderType::PINK_PAW; }
	if (collType == ColliderType::PLATFORM) { pbody->ctype = ColliderType::PLATFORM; }
	if (collType == ColliderType::ORANGE_BUMPER) { pbody->ctype = ColliderType::ORANGE_BUMPER; }
	if (collType == ColliderType::OVAL) { pbody->ctype = ColliderType::OVAL; }
	if (collType == ColliderType::BELL) { pbody->ctype = ColliderType::BELL; }
	if (collType == ColliderType::ROD) { pbody->ctype = ColliderType::ROD; }
	if (collType == ColliderType::CHEEK) { pbody->ctype = ColliderType::CHEEK; }
	if (collType == ColliderType::SLINGERSHOT) { pbody->ctype = ColliderType::SLINGERSHOT; }
	if (collType == ColliderType::EARS) { pbody->ctype = ColliderType::EARS; }
	

	// Return our PhysBody class
	return pbody;
}

PhysBody* ModulePhysics::CreateBouncyChain(int x, int y, int* points, int size, float bounce, BodyType type, ColliderType collType)
{
	// Create BODY at position x,y
	b2BodyDef body;
	if (type == BodyType::DYNAMIC) { body.type = b2_dynamicBody; }
	if (type == BodyType::KINEMATIK) { body.type = b2_kinematicBody; }
	if (type == BodyType::STATIC) { body.type = b2_staticBody; }

	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	// Add BODY to the world
	b2Body* b = world->CreateBody(&body);

	// Create SHAPE
	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];
	for (uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}
	shape.CreateLoop(p, size / 2);

	// Create FIXTURE
	b2FixtureDef fixture;
	fixture.shape = &shape;

	//Bounce
	fixture.restitution = bounce;

	// Add fixture to the BODY
	b->CreateFixture(&fixture);

	// Clean-up temp array
	delete p;

	// Create our custom PhysBody class
	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	if (collType == ColliderType::UNKNOWN) { pbody->ctype = ColliderType::UNKNOWN; }
	if (collType == ColliderType::GREEN_PAW) { pbody->ctype = ColliderType::GREEN_PAW; }
	if (collType == ColliderType::PURPLE_PAW) { pbody->ctype = ColliderType::PURPLE_PAW; }
	if (collType == ColliderType::TURQUOISE_PAW) { pbody->ctype = ColliderType::TURQUOISE_PAW; }
	if (collType == ColliderType::PINK_PAW) { pbody->ctype = ColliderType::PINK_PAW; }
	if (collType == ColliderType::PLATFORM) { pbody->ctype = ColliderType::PLATFORM; }
	if (collType == ColliderType::ORANGE_BUMPER) { pbody->ctype = ColliderType::ORANGE_BUMPER; }
	if (collType == ColliderType::OVAL) { pbody->ctype = ColliderType::OVAL; }
	if (collType == ColliderType::BELL) { pbody->ctype = ColliderType::BELL; }
	if (collType == ColliderType::ROD) { pbody->ctype = ColliderType::ROD; }
	if (collType == ColliderType::CHEEK) { pbody->ctype = ColliderType::CHEEK; }
	if (collType == ColliderType::SLINGERSHOT) { pbody->ctype = ColliderType::SLINGERSHOT; }
	if (collType == ColliderType::EARS) { pbody->ctype = ColliderType::EARS; }

	// Return our PhysBody class
	return pbody;
}


// Callback function to collisions with Box2D
void ModulePhysics::BeginContact(b2Contact* contact)
{
	// Call the OnCollision listener function to bodies A and B, passing as inputs our custom PhysBody classes
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();
	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);
	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}


// PHYS BODY FUNCTIONS -------------------------------------------------------------------------------

PhysBody::PhysBody() : listener(NULL), body(NULL), ctype(ColliderType::UNKNOWN)
{
	// Initialize all internal class variables
	width = height = 0;
	body = NULL;
	listener = NULL;
	ctype = ColliderType::UNKNOWN;
}

PhysBody::~PhysBody()
{
	// Destroy the associated Box2D body
	body->GetWorld()->DestroyBody(body);
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

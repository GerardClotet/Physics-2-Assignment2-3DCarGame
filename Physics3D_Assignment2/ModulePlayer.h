#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "glmath.h"
struct PhysVehicle3D;
class vec3;
#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
#define START_POINT 0,100.5f,0
class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	vec3 PlayerCamPos();
public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	float offset_x = 0;
	int numBoosts=0;
	float camera_transitionX;
	float camera_transitionY;
	float camera_transitionZ;
	bool turn_increase;
	bool rotOrigin;
};
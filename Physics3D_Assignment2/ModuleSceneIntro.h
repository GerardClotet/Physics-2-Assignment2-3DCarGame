#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "glmath.h"
#define MAX_SNAKE 2
#define STANDARD_SIZE vec3(5,2,5)
class Cube;
class DebugDrawer;
struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void Speedway();
	void LoadSpeedWay();
	void CreateCube(vec3 dimension = { 1.0f,1.0f,1.0f }, vec3 position = { 0.0f, 0.0f, 0.0f }, Color color = White, float angle = 0.0f, vec3 u = (0.0f, 0.0f, 0.0f), float mass = 0.0f);
	void CreateStraigthPath(float dim_x , float dim_y, float dim_z,float length, float width, bool direction);
public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	DebugDrawer* timedraw;
	

	p2List <Cube> cubes;
	vec3 vec3_zero = { 0.0f,0.0f,0.0f };
	vec3 axis_x = { 1.0f,0.0f,0.0f }, axis_y = { 0.0f,1.0f,0.0f }, axis_z = { 0.0f,0.0f,1.0f }, axis_xy = {1,1,0}, axis_xz = { 1,0,1 }, axis_yz = { 0,1,1 };
	vec3 vec3jeje = { 20.0f,900.0f, 0.0f };

	/*Cube c(10, 4, 10);
	c.SetPos(0, 100, 0);
	c.color = White;

	float mass = 0.0f;*/
	Cube start_plat;//
	bool plat_done = true;
	
	//= (10.0f, 4.0f, 10.0f);
};

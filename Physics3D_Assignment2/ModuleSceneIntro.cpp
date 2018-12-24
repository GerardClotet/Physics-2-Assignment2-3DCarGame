#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "ModuleRenderer3D.h"
ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
//	App->physics->draw3d
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	//App->camera->LookAt(vec3(0, 0, 0));
	btVector3 hola(1, 2, 1);
	const char* addeu ="hola";
	//timedraw->draw3dText(hola, addeu);
	//App->renderer3D(timedraw);
	/*Cube start_plat(10, 4, 10);
	start_plat.SetPos(0,100,0);
	start_plat.color = White;
	float mass = 0.0f;
	App->physics->AddBody(start_plat,mass);*/
	LoadSpeedWay();
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	Speedway();
	
	return UPDATE_CONTINUE;
	
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}


void ModuleSceneIntro::Speedway()
{
	p2List_item<Cube>* cubes_item = cubes.getFirst();
	plat_done = false;
	while (cubes_item != nullptr)
	{
		cubes_item->data.Render();
		cubes_item = cubes_item->next;
	}
	
}


void ModuleSceneIntro::LoadSpeedWay()
{
#define ROAD_TRY vec3(10,0.5,20)
#define PLATFORM vec3(10,0.5f,10)
	CreateCube(STANDARD_SIZE, vec3(vec3_zero.x, vec3_zero.y, vec3_zero.x), White);
	CreateCube(STANDARD_SIZE, vec3(vec3_zero.x, vec3_zero.y, vec3_zero.x + STANDARD_SIZE.z), White);
	CreateCube(STANDARD_SIZE, vec3(vec3_zero.x, vec3_zero.y, vec3_zero.x + STANDARD_SIZE.z * 2), White);

	//PROVA
	CreateCube(vec3(3, 0.5, 15), vec3(5, 100, -15), Orange, -10, axis_xy);
	CreateCube(vec3(3, 0.5, 15), vec3(0, 100, -17), LightBlue, 40, axis_yz);
	CreateCube(vec3(3, 0.5, 15), vec3(-5, 100, -20), Yellow, 5, axis_yz);

	//START_PLATFORM
	CreateCube(PLATFORM, vec3(0, 102.2, 0.3), Red);

	//START_RAMP
	CreateCube(ROAD_TRY, vec3(vec3_zero.x, vec3_zero.y + +98.8f, 14.4f), White, 20.0f, axis_x);
	CreateCube(vec3(10,0.5,7), vec3(vec3_zero.x, vec3_zero.y + +93, 30), White, 20.0f, axis_x);

	//2nd PLAT
	CreateCube(PLATFORM, vec3(0, 91.8, 38.3), Red);

	//2n RAMP
	CreateCube(vec3(40, 0.5, 15), vec3(-25, 95, 38.3), White, -10, axis_z);

	//3 PLAT
	CreateCube(PLATFORM, vec3(-48, 98.5f, 38.3), Red);

	//JUMP
	CreateCube(vec3(3, 0.5, 15), vec3(-54, 98, 38.3), Green, 45, axis_z);
	CreateCube(vec3(3, 0.5, 15), vec3(-56, 96, 38.3), Pink, 43, axis_z);
	CreateCube(vec3(3, 0.5, 15), vec3(-58, 94, 38.3), LightBlue, 41, axis_z);
	CreateCube(vec3(3, 0.5, 15), vec3(-60, 92.3, 38.3), Yellow, 38, axis_z);
	CreateCube(vec3(4, 0.5, 15), vec3(-62.5, 90.3, 38.3), Orange, 36, axis_z);
	CreateCube(vec3(4, 0.5, 15), vec3(-65.8, 88, 38.3), Red, 33, axis_z);
	CreateCube(vec3(4, 0.5, 15), vec3(-69, 85.9, 38.3), Green, 30, axis_z);
	CreateCube(vec3(4, 0.5, 15), vec3(-72.5, 84, 38.3), Pink, 27, axis_z);
	CreateCube(vec3(4, 0.5, 15), vec3(-76, 82.3, 38.3), LightBlue, 24, axis_z);
	CreateCube(vec3(4, 0.5, 15), vec3(-80.3, 80.3, 38.3), Yellow, 21, axis_z);
	CreateCube(vec3(4, 0.5, 15), vec3(-85.2, 78.7, 38.3), Orange, 18, axis_z);
	CreateCube(vec3(4, 0.5, 15), vec3(-89.2, 77.5, 38.3), Red, 15, axis_z);
	CreateCube(vec3(4, 0.5, 15), vec3(-93.2, 76.5, 38.3), Green, 12, axis_z);
	CreateCube(vec3(4, 0.5, 15), vec3(-97.1, 75.8, 38.3), Pink, 9, axis_z); 
	CreateCube(vec3(4, 0.5, 15), vec3(-101.1, 75.3, 38.3), LightBlue, 6, axis_z);
	CreateCube(vec3(4, 0.5, 15), vec3(-104.7, 75, 38.3), Yellow, 3, axis_z);

	//Plat
	CreateCube(vec3(80, 0.5, 15), vec3(-120, 75, 38.3), Yellow);
	
	CreateCube(vec3(15, 0.5, 100), vec3(-120, 49.4, 88), White, 30, axis_x);
	
	CreateCube(vec3(15, 0.5, 60), vec3(-120, 16.5, 155), Pink, 20, axis_x);
	
}

//void ModuleSceneIntro::CreateCube(vec3 dimension, vec3 pos, float angle, vec3 rotDir, float mass, Color color)
//{
//	Cube cube(dimension.x, dimension.y, dimension.z);
//	cube.SetPos(pos.x, pos.y, pos.z);
//	
//	if (angle != 0)
//	{
//		cube.SetRotation(angle, vec3(rotDir.x, rotDir.y, rotDir.z));
//	}
//
//	cube.color = color;
//
//	App->physics->AddBody(cube, mass);
//	cubes.add(cube);
//}

void ModuleSceneIntro::CreateCube(vec3 dim, vec3 pos, Color color, float angle, vec3 u, float mass)
{
	Cube cube(dim.x, dim.y, dim.z);
	cube.SetPos(pos.x, pos.y, pos.z);
	cube.color = color;

	if (angle != 0)
		cube.SetRotation(angle, vec3(u.x, u.y, u.z));


	App->physics->AddBody(cube, mass);

	cubes.add(cube);

	//return c;
}

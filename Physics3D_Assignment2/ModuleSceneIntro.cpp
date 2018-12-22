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
	CreateCube(STANDARD_SIZE, vec3(vec3_zero.x, vec3_zero.y, vec3_zero.x), White);
	CreateCube(STANDARD_SIZE, vec3(vec3_zero.x, vec3_zero.y, vec3_zero.x + STANDARD_SIZE.z), White);
	CreateCube(STANDARD_SIZE, vec3(vec3_zero.x, vec3_zero.y, vec3_zero.x + STANDARD_SIZE.z * 2), White);
	CreateCube(ROAD_TRY, vec3(vec3_zero.x+4, vec3_zero.y + +50, vec3_zero.x + STANDARD_SIZE.z * 3 - 0.25f), White, -20.0f, axis_x);
	//CreateCube(ROAD_DIM, vec3(vec3jeje.x+700*100000, vec3jeje.y+300, vec3jeje.z + ROAD_DIM.z * 2), White);
	CreateCube(vec3(10, 4, 10), vec3(0, 100, 0), White);
//	LOG("vec3zro: %f", vec3_zero.y + 100);
	/*CreateCube(vec3(5, .1, 12), vec3(0, 0, 0), 0,vec3(0,0,0),200, Green);
	CreateCube(vec3(5, .5, 12), vec3(0, 1, 20), -20, vec3(1, 0, 0), -200, Green);*/
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
	Cube c(dim.x, dim.y, dim.z);
	c.SetPos(pos.x, pos.y, pos.z);
	c.color = color;

	if (angle != 0)
		c.SetRotation(angle, vec3(u.x, u.y, u.z));


	App->physics->AddBody(c, mass);

	cubes.add(c);

	//return c;
}

#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "ModuleRenderer3D.h"
#include "ModulePlayer.h"
#include"PhysVehicle3D.h"
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
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	
	
	
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
	Pendulums();

	

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

	trap2.Render();
	trap2_2.Render();

	mat4x4 transform;
	trap_02->GetTransform(transform.M);
	trap2.transform = transform;
	trap_02_2->GetTransform(transform.M);
	trap2_2.transform = transform;
}


void ModuleSceneIntro::LoadSpeedWay()
{
#define ROAD_TRY vec3(10,0.5,20)
#define PLATFORM vec3(10,0.5f,10)
	


	//safe

	////START_PLATFORM
	//CreateCube(PLATFORM, vec3(0, 102.2, 0.3), Red , Platform);

	////START_RAMP
	//CreateCube(ROAD_TRY, vec3(vec3_zero.x, 98.8f, 14.4f), White, 20.0f, axis_x, Platform);
	//CreateCube(vec3(10,0.5,7), vec3(vec3_zero.x, vec3_zero.y + +93, 30), White, 20.0f, axis_x, Platform);

	////safe 
	//CreateCube(PLATFORM, vec3(0, 91.8, 38.3), Red, 90,axis_z, Platform);

	////START_PLATFORM
	//CreateCube(PLATFORM, vec3(0, 96, 38.3), Red, Platform);

	//2n RAMP
	CreateCube(vec3(380, 0.5, 15), vec3(135, 35, 38.3), White, -20, axis_z, Platform);

	//safe
	CreateCube(PLATFORM, vec3(-43, 112, 38.3), Red, 90, axis_z, Platform);
	//START_PLATFORM
CreateCube(PLATFORM, vec3(-48, 100, 38.3), Red, Platform);

	//JUMP
	CreateCube(vec3(3, 0.5, 15), vec3(-54, 98, 38.3), Green, 45, axis_z, Platform);
	CreateCube(vec3(3, 0.5, 15), vec3(-56, 96, 38.3), Pink, 43, axis_z, Platform);
	CreateCube(vec3(3, 0.5, 15), vec3(-58, 94, 38.3), LightBlue, 41, axis_z, Platform);
	CreateCube(vec3(3, 0.5, 15), vec3(-60, 92.3, 38.3), Yellow, 38, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-62.5, 90.3, 38.3), Orange, 36, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-65.8, 88, 38.3), Red, 33, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-69, 85.9, 38.3), Green, 30, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-72.5, 84, 38.3), Pink, 27, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-76, 82.3, 38.3), LightBlue, 24, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-80.3, 80.3, 38.3), Yellow, 21, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-85, 78.7, 38.3), Orange, 18, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-89.2, 77.5, 38.3), Red, 15, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-93.2, 76.5, 38.3), Green, 12, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-97.1, 75.8, 38.3), Pink, 9, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-101.1, 75.3, 38.3), LightBlue, 6, axis_z, Platform);
	CreateCube(vec3(4, 0.5, 15), vec3(-104.7, 75, 38.3), Yellow, 3, axis_z, Platform);

	//Plat
	CreateCube(vec3(80, 0.5, 15), vec3(-120, 75, 38.3), Yellow, Platform);
	CreateStraigthPath(-160, 77, 32.5, 11, 0, true);
	CreateStraigthPath(-160, 77, 32.5, 2,0, false);
	//Big fall
	CreateCube(vec3(80, 0.5, 100), vec3(-120, 50, 88), White, 30, axis_x, Platform);
	
	CreateCube(vec3(15, 2, 60), vec3(-120, 16.5, 155), Pink, 20, axis_x, Platform);
	
	CreateStraigthPath(-100, 1.5, 247, 40, 25,true);

	CreateStraigthPath(-134, 1.5, 259.8, 6, 0, true);
	CreateStraigthPath(-133, 1.5, 240, 3, 0, false);
	CreateStraigthPath(-120.5, 1.5, 195, 8, 25, false);
	
	//Devil Square
	CreateCube(vec3(30, 0.5, 25), vec3(108, 4, 247), White, 20, axis_z, Platform);
	CreateCube(vec3(30, 0.5, 25), vec3(234, 4, 247), White, -20, axis_z, Platform);

	CreateStraigthPath(250, 1.5, 247, 5, 25, true);
	CreateStraigthPath(280, 1.5, 259.5, 4, 0, true);
	CreateStraigthPath(303, 1.5, 230, 5, 0, false);

	CreateStraigthPath(290, 1.5, 53, 35, 25, false);
	//Rotation Boxes
	trap.SetPos(114, 12, 247);
	trap.color = Red;
	trap_01 = App->physics->AddBody(trap, 0);


	trap2.SetPos(114, 19, 260);
	trap2.color = Red;
	trap_02 = App->physics->AddBody(trap2, 50);

	btHingeConstraint* hinge = App->physics->AddConstraintHinge(*trap_01, *trap_02, vec3(0, 0, 0), vec3(0, 0, -20), vec3(0, 1, 0), vec3(0, 1, 0), true);
	hinge->enableAngularMotor(true, 2.0f, INFINITE);
	trap_2.SetPos(0, 25, 0);
	trap_2.color = Red;
	trap_01_2 = App->physics->AddBody(trap_2, 0);


	trap2_2.SetPos(1000, 72, 1000);
	trap2_2.color = Red;
	trap_02_2 = App->physics->AddBody(trap2_2, 50);

	btHingeConstraint* hinge_2 = App->physics->AddConstraintHinge(*trap_01_2, *trap_02_2, vec3(0, 0, 0), vec3(0, 0, -425), vec3(0, 1, 0), vec3(0, 1, 0), false);
	hinge_2->enableAngularMotor(true, -2.0f, INFINITE);


	//PENDULUM
	createPendulum(-120, 84 , 110); //1st
	createPendulum(290, 48, 190);
	createPendulum(290, 48, 170);
	createPendulum(290, 48, 150);
	createPendulum(290, 48, 130);
	createPendulum(290, 48, 110);
	createPendulum(290, 48, 90);


}






void ModuleSceneIntro::CreateCube(vec3 dim, vec3 pos, Color color, float angle, vec3 u, float mass, Type type)
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



void ModuleSceneIntro::CreateStraigthPath(float pos_x, float pos_y, float pos_z, float length, float width,bool direction)
{
	
	int current_pos = 0;
	for (int i = 0; i < length; i++)
	{
		current_pos += 5;

		if (width != 0)
		{
			switch (direction)
			{
			case true:
				if (i == 0)
				{
					CreateCube(vec3(3, 4, 3), vec3(pos_x, pos_y, pos_z + 0.5f*width), Orange);
					CreateCube(vec3(3, 4, 3), vec3(pos_x, pos_y, pos_z - 0.5f*width), Orange);

				}


				CreateCube(vec3(3, 4, 3), vec3(pos_x + current_pos, pos_y, pos_z + 0.5f*width), White);
				CreateCube(vec3(3, 4, 3), vec3(pos_x + current_pos, pos_y, pos_z - 0.5*width), Green);

				break;
			case false:

				if (i == 0)
				{
					CreateCube(vec3(3, 4, 3), vec3(pos_x + 0.5f*width, pos_y, pos_z), Orange);
					CreateCube(vec3(3, 4, 3), vec3(pos_x - 0.5f*width, pos_y, pos_z), Orange);
				}
				CreateCube(vec3(3, 4, 3), vec3(pos_x + 0.5f*width, pos_y, pos_z + current_pos), LightBlue);
				CreateCube(vec3(3, 4, 3), vec3(pos_x - 0.5f*width, pos_y, pos_z + current_pos), LightBlue);
			}
		}
		else if(width ==0)
		{ 
			switch (direction)
			{
			case true:
				if (i == 0)
				{
					CreateCube(vec3(3, 4, 3), vec3(pos_x, pos_y, pos_z), Orange);
				}
				CreateCube(vec3(3, 4, 3), vec3(pos_x + current_pos, pos_y, pos_z ), White);
				break;

			case false:
				if (i == 0)
				{
					CreateCube(vec3(3, 4, 3), vec3(pos_x, pos_y, pos_z), Orange);

				}

				CreateCube(vec3(3, 4, 3), vec3(pos_x , pos_y, pos_z+ current_pos), White);

			}
		}
		
		
	}
}

void ModuleSceneIntro::createPendulum(float x, float y, float z)
{
	Sphere sp(0.1f);
	sp.SetPos(x, y, z);
	PhysBody3D* spB = App->physics->AddBody(sp, 0);

	Cylinder c;
	c.radius = 0.3f*2;
	c.height = 15 * 2;
	c.SetPos(x + 9 * 2, y, z);
	c.color = Gray;
	PhysBody3D* cB = App->physics->AddBody(c, 1000);

	btHingeConstraint* hinge_pendul = App->physics->AddConstraintHinge(*spB, *cB, { 0, 0, 0 }, { 9 * 2, 0, 0 }, { 0, 0, 1 }, { 0, 0, 1 }, true);

	Sphere s;
	s.radius = 3 * 2;
	s.SetPos(x + 10.5f*2, y, z);
	s.color = Gray;
	PhysBody3D* sB = App->physics->AddBody(s, 2000);

	App->physics->AddConstraintP2P(*cB, *sB, { -9 * 2, 0, 0 }, { 1.5f*2, 0, 0 });

	Pendulum p(s, c, sB, cB);
	p.hinge_pendul = hinge_pendul;
	pendulums.add(p);
}

void Pendulum::Render()
{
	//Bar
	btQuaternion q = cB->GetRotation();
	q = q.normalized();
	float angle = 2 * acos(q.w()) * 180 / 3.14;
	c.SetRotation(angle, { 0,0,1 });
	c.SetPos(cB->GetPos().x, cB->GetPos().y, cB->GetPos().z);
	c.Render();

	//Weight
	s.SetPos(sB->GetPos().x, sB->GetPos().y, sB->GetPos().z);
	s.Render();
}

void ModuleSceneIntro::Pendulums()
{
	for (p2List_item<Pendulum>* item = pendulums.getFirst(); item; item = item->next)
	{
		item->data.Render();
		if ((item->data.sB->GetPos().y) > 35 && item->data.rising)
		{
			item->data.rising = false;
			int speed;
			if (item->data.positive)
			{
				speed = 700;
				item->data.positive = false;
			}
			else
			{
				speed = -700;
				item->data.positive = true;
			}

			if (item->data.hinge_pendul != nullptr)
				item->data.hinge_pendul->enableAngularMotor(true, 10, speed);
		}
		else if (item->data.sB->GetPos().y < 30 && !item->data.rising)
		{
			item->data.rising = true;
		}
	}

}
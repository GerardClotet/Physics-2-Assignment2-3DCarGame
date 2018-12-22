#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	numBoosts = 3;
	// Camera Var
	camera_transitionX = 10;
	camera_transitionY = 5;
	camera_transitionZ = 0;
	VehicleInfo car;
	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1, 4);
	car.chassis_offset.Set(0, 1, 0);
	car.cabin_size.Set(1.98, 1.25, 2);
	car.cabin_offset.Set(-0.001,2,-0.03);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 101, 0);
	App->camera->Position.x = vehicle->GetPos().x;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		vehicle->SetPos(START_POINT);
	}
	//App->camera->Position = front_vec + vehicle->GetPos();
	
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
		
	}
	

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (turn < TURN_DEGREES)
		{
			turn += TURN_DEGREES;
			turn_increase = true;
			rotOrigin = false;
		}
		
		
	}
	else rotOrigin = true;
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (turn > -TURN_DEGREES) 
		{
			turn -= TURN_DEGREES;
			turn_increase = false;
			rotOrigin = false;
		}
		//else rotOrigin = true;
	}
	else rotOrigin = true;
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && numBoosts >0)
	{
		 
		int impulse = 50000;
		acceleration = acceleration + impulse;
		//numBoosts--;
		if (numBoosts < 0)
		{
			numBoosts = 0;
		}

	}
	if (App->camera->debugMove == false)
	{
		PlayerCamPos();
		vec3 third_person_cam = { vehicle->GetPos().x, vehicle->GetPos().y, vehicle->GetPos().z };

		App->camera->LookAt(third_person_cam);
	}

	
	
	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}


vec3 ModulePlayer::PlayerCamPos()
{
	vec3 front_vec = vehicle->GetForwardVec();
	front_vec = -front_vec;
	
	//front_vec.z += 0.2;
	if (acceleration == MAX_ACCELERATION)
	{
		if (camera_transitionX < 15) {
			camera_transitionX+=0.05F;
		}
		else
		{
			camera_transitionX = 15;
		}
		if (camera_transitionY < 7)
		{
			camera_transitionY+=0.05F;
		}
		else
		{
			camera_transitionY = 7;
		}
		front_vec = front_vec * camera_transitionX;
		front_vec.y = front_vec.y + camera_transitionY; //ACCELERATED 
		//front_vec.z = front_vec.z*camera_transitionX/10;
		//front_vec.x = front_vec.x + camera_transitionX;

	}
	else if (acceleration != MAX_ACCELERATION)
	{
		if (camera_transitionX<= 15 && camera_transitionX> 10)
		{
			camera_transitionX-=0.05F;
		}
		else
		{
			camera_transitionX = 10;
		}
		if (camera_transitionY <= 7 && camera_transitionY > 5)
		{
			camera_transitionY-=0.05F;
		}
		else
		{
			camera_transitionY = 5;
		}
		front_vec = front_vec * camera_transitionX ;  //NO ACCELERATION
		front_vec.y = front_vec.y + camera_transitionY;
		//front_vec.x = front_vec.x + camera_transitionX;
	}

	//if (turn > -TURN_DEGREES && turn_increase == false) // turn > -TURN_DEGREES && turn_increase == false
	//{
	//	
	//	
	//	if (camera_transitionZ <= 15 && camera_transitionZ >=0)
	//	{
	//		camera_transitionZ += 0.2;
	//	}
	//	else if (rotOrigin == true &&  camera_transitionZ >=0)
	//	{
	//		camera_transitionZ -= 0.2;
	//	}
	//	else
	//	{
	//		camera_transitionZ = 0;
	//	}
	//	front_vec.x = front_vec.x + camera_transitionZ;

	//}
	//else if (turn < TURN_DEGREES && turn_increase == true) //turn < TURN_DEGREES && turn_increase == true
	//{
	//	if(camera_transitionZ >= -15 && camera_transitionZ <= 0)
	//	{
	//		camera_transitionZ -= 0.2;
	//	}
	//	else if (rotOrigin == true && camera_transitionZ <= 0)
	//	{
	//		camera_transitionZ += 0.2;
	//	}
	//	else
	//	{
	//		camera_transitionZ = 0;
	//	}
	//	front_vec.x = -front_vec.x + camera_transitionZ;
	//}

	App->camera->Position = front_vec + vehicle->GetPos();
	
	/*LOG("front vec.z: %f", front_vec.x);
	LOG("cam TransZ: %f", camera_transitionZ);*/
	return App->camera->Position;
}

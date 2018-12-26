#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	// CAR'S CABIN

	Cube cabin(info.cabin_size.x, info.cabin_size.y, info.cabin_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&cabin.transform);

	btVector3 offset_cabin(info.cabin_offset.x, info.cabin_offset.y, info.cabin_offset.z);
	offset_cabin = offset_cabin.rotate(q.getAxis(), q.getAngle());

	cabin.transform.M[12] += offset_cabin.getX();
	cabin.transform.M[13] += offset_cabin.getY();
	cabin.transform.M[14] += offset_cabin.getZ();

	cabin.color = Red;


	// FRONT FENDER

	Cube front_fender(info.front_fender_size.x, info.front_fender_size.y, info.front_fender_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&front_fender.transform);

	btVector3 offset_front_fender(info.front_fender_offset.x, info.front_fender_offset.y, info.front_fender_offset.z);
	offset_front_fender = offset_front_fender.rotate(q.getAxis(), q.getAngle());

	front_fender.transform.M[12] += offset_front_fender.getX();
	front_fender.transform.M[13] += offset_front_fender.getY();
	front_fender.transform.M[14] += offset_front_fender.getZ();

	front_fender.color = Blue;

	//SPOILER
	Cube spoiler(info.spoiler_size.x, info.spoiler_size.y, info.spoiler_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&spoiler.transform);

	btVector3 offset_spoiler(info.spoiler_offset.x, info.spoiler_offset.y, info.spoiler_offset.z);
	offset_spoiler = offset_spoiler.rotate(q.getAxis(), q.getAngle());

	spoiler.transform.M[12] += offset_spoiler.getX();
	spoiler.transform.M[13] += offset_spoiler.getY();
	spoiler.transform.M[14] += offset_spoiler.getZ();

	spoiler.color = Green;

	//SPOILER ARMS

	Cube spoiler_left_arm(info.spoiler_left_arm_size.x, info.spoiler_left_arm_size.y, info.spoiler_left_arm_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&spoiler_left_arm.transform);

	btVector3 offset_spoiler_left_arm(info.spoiler_left_arm_offset.x, info.spoiler_left_arm_offset.y, info.spoiler_left_arm_offset.z);
	offset_spoiler_left_arm = offset_spoiler_left_arm.rotate(q.getAxis(), q.getAngle());

	spoiler_left_arm.transform.M[12] += offset_spoiler_left_arm.getX();
	spoiler_left_arm.transform.M[13] += offset_spoiler_left_arm.getY();
	spoiler_left_arm.transform.M[14] += offset_spoiler_left_arm.getZ();

	spoiler_left_arm.color = Green;

	Cube spoiler_right_arm(info.spoiler_right_arm_size.x, info.spoiler_right_arm_size.y, info.spoiler_right_arm_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&spoiler_right_arm.transform);

	btVector3 offset_spoiler_right_arm(info.spoiler_right_arm_offset.x, info.spoiler_right_arm_offset.y, info.spoiler_right_arm_offset.z);
	offset_spoiler_right_arm = offset_spoiler_right_arm.rotate(q.getAxis(), q.getAngle());

	spoiler_right_arm.transform.M[12] += offset_spoiler_right_arm.getX();
	spoiler_right_arm.transform.M[13] += offset_spoiler_right_arm.getY();
	spoiler_right_arm.transform.M[14] += offset_spoiler_right_arm.getZ();

	spoiler_right_arm.color = Green;



	//Renderer
	chassis.Render();
	cabin.Render();
	front_fender.Render();
	spoiler.Render();
	spoiler_left_arm.Render();
	spoiler_right_arm.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}

vec3 PhysVehicle3D::GetForwardVec()
{
	btVector3 btFront = vehicle->getForwardVector();
	vec3 front_vec;
	front_vec.Set(btFront.getX(), btFront.getY(), btFront.getZ());
	return front_vec;
}
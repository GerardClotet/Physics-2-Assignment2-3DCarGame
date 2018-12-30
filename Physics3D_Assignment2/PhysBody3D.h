#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "ModuleSceneIntro.h"

class btRigidBody;
class Module;
class vec3;
struct btQuaternion;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetAsSensor(bool is_sensor);
	vec3 GetPos();
//	btVector3 Get_bt_Pos() ;
	btQuaternion GetRotation() const;
	void SetRotation(btQuaternion newQ);
private:
	btRigidBody* body = nullptr;
	bool is_sensor = false;
public:
	p2List<Module*> collision_listeners;
	
};

#endif // __PhysBody3D_H__
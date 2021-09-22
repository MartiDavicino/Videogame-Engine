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

	wheel.color = White;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	//Main Car Body
	CreateCube(vec3(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z), { info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z }, Red).Render();
	
	float facePos = 1.0f;
	CreateCube(vec3(1.8f, 0.6, 1.5f), { 0, 1.25f + facePos,2.1f }, Red).Render();
	CreateCube(vec3(0.25f, 0.4f, 0.4f), { 0.5f, 1.25f + facePos, 2.7f }, White).Render();
	CreateCube(vec3(0.25f, 0.4f, 0.4f), { -0.5f, 1.25f + facePos, 2.7f }, White).Render();
	CreateCube(vec3(0.1f, 0.1f, 0.1f), { 0.6f, 1.3f + facePos, 2.9f }, Black).Render();
	CreateCube(vec3(0.1f, 0.1f, 0.1f), { -0.6f, 1.2f + facePos, 2.9f }, Black).Render();
	CreateCube(vec3(0.1f, 0.1f, 0.1f), { 0.0f, 1.2f + facePos, 2.9f }, Black).Render();


	CreateCube(vec3(0.1, 0.3, .3), { .6, 2.2, -1.5 }, White).Render();
	CreateCube(vec3(0.1, 0.3, .3), { -.6, 2.2, -1.5 }, White).Render();
	CreateCube(vec3(2, 0.07, .5), { 0, 2.35, -1.5 }, White).Render();
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

Cube PhysVehicle3D::CreateCube(vec3 size, vec3 position, Color color)
{
	Cube cube(size.x, size.y, size.z);

	vehicle->getChassisWorldTransform().getOpenGLMatrix(&cube.transform);

	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(position.x, position.y, position.z);

	offset = offset.rotate(q.getAxis(), q.getAngle());

	cube.transform.M[12] += offset.getX();
	cube.transform.M[13] += offset.getY();
	cube.transform.M[14] += offset.getZ();

	cube.color = color;

	cube.Render();

	return cube;
}
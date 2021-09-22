#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PhysBody3D.h"

#define MAX_SNAKE 2
#define MAX_CHECKPOINTS 3

struct PhysBody3D;
struct PhysMotor3D;
struct PhysSensor3D;

struct CheckPoint {
	vec3 pos;
	bool isEnabled;
};

enum SensorType;
class btHingeConstraint;

class ModuleMap : public Module
{
public:
	ModuleMap(Application* app, bool start_enabled = true);
	~ModuleMap();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	PhysBody3D* CreateRectangle(vec3, vec4, vec3, Color, float mass = 0.f);
	PhysBody3D* CreateCylinder(vec3, vec4, float, float, Color, float mass = 0.f);
	PhysSensor3D* CreateSensor(vec3 position, vec4 rotation, vec3 size, PhysSensor3D::Type type, float mass = 0.0f);

	void FirstPhaseObjects();
	void SecondPhaseObjects();
	void ThirdPhaseObjects();
	void LastPhaseObjects();
	void CreateSensors();
	void CreateConstrains();

	p2DynArray<Primitive*> obs_primitives;
	p2DynArray<PhysBody3D*> obs_bodys;
	btHingeConstraint* rotatingWheel;

	int checkpointCounter;

public:

	

	p2List<Primitive*> map_objects;
	p2List<PhysSensor3D*> map_sensors;
	PhysSensor3D* checkPoints[3];

	CheckPoint checkPointsSpawn[5];
};

#include "Globals.h"
#include "Application.h"
#include "ModuleMap.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"

ModuleMap::ModuleMap(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	checkpointCounter = 0;
}

ModuleMap::~ModuleMap()
{}

// Load assets
bool ModuleMap::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//Camera init
	

	//Audio Load
	
	//Create map
	/*FirstPhaseObjects();
	SecondPhaseObjects();
	ThirdPhaseObjects();
	LastPhaseObjects();
	CreateSensors();
	CreateConstrains();*/

	//Checkpoints info
	checkPointsSpawn[0].isEnabled = false;
	checkPointsSpawn[0].pos = { 110.0f , 110.0f , 0.0f};

	checkPointsSpawn[1].isEnabled = false;
	checkPointsSpawn[1].pos = { 0.0f , 0.0f , 0.0f };

	checkPointsSpawn[2].isEnabled = false;
	checkPointsSpawn[2].pos = { 1110.0f , 1110.0f , 0.0f };

	CreateSensors();

	return ret;
}

// Load assets
bool ModuleMap::CleanUp()
{
	LOG("Unloading Intro scene");
	map_objects.clear();
	map_sensors.clear();
	obs_bodys.Clear();
	obs_primitives.Clear();
	return true;
}

// Update
update_status ModuleMap::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	

	return UPDATE_CONTINUE;
}

void ModuleMap::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

PhysBody3D* ModuleMap::CreateRectangle(vec3 position, vec4 rotation, vec3 size, Color s_color, float mass)
{

	Cube* object = new Cube();

	object->SetPos(position.x, position.y, position.z);
	object->size = size;
	object->color = s_color;
	object->SetRotation(rotation.x, { rotation.y, rotation.z, rotation.w });

	map_objects.add(object);
	return App->physics->AddBody(*object, mass);
}

PhysBody3D* ModuleMap::CreateCylinder(vec3 position, vec4 rotation, float radius, float height, Color s_color, float mass)
{
	Cylinder* object = new Cylinder();

	object->SetPos(position.x, position.y, position.z);
	object->color = s_color;
	object->SetRotation(rotation.x, { rotation.y, rotation.z, rotation.w });

	object->height = height;
	object->radius = radius;

	map_objects.add(object);
	return App->physics->AddBody(*object, mass);
}

PhysSensor3D* ModuleMap::CreateSensor(vec3 position, vec4 rotation, vec3 size, PhysSensor3D::Type type, float mass)
{
	Cube* object = new Cube();

	object->SetPos(position.x, position.y, position.z);
	object->size = size;
	object->SetRotation(rotation.x, { rotation.y, rotation.z, rotation.w });
	//map_objects.add(object);
	return App->physics->AddSensor(*object, type);
}

void ModuleMap::FirstPhaseObjects()
{
	//------------------------ROAD LIMITS---------------------------------------
	//Left side ------------------------------------------------
	
	
}

void ModuleMap::SecondPhaseObjects()
{
	
}

void ModuleMap::ThirdPhaseObjects()
{
	
}

void ModuleMap::LastPhaseObjects()
{
	
}

void ModuleMap::CreateSensors()
{
	//Here we add all sensors:
	//FINISH
	CreateSensor({ 0,0,-8 }, { 0,1, 0, 0 }, { 14,110,2.f }, PhysSensor3D::Type::FINISH);
	//LAP
	CreateSensor({ -14,0,-8 }, { 0,1, 0, 0 }, { 14,110,2.f }, PhysSensor3D::Type::LAP);
	//-------------------------------------------------------------------------------------
	//WALL LEFT CURVE
	CreateSensor({ 0,0,70 }, { 0,0,0,1 }, {14,1.f,60 }, PhysSensor3D::Type::DEAD);
	CreateSensor({ -14,0,0 }, { 0,0,0,1 }, {14,1.f,60 }, PhysSensor3D::Type::DEAD);
	//WALL FRONT 
	CreateSensor({ 10,1,128 }, { 0,0,0,1 }, { 2,5.f,50 }, PhysSensor3D::Type::DEAD);
	//WALL RIGHT CURVE
	CreateSensor({ -25,1,128 }, { 0,0,0,1 }, { 2,5.f,50 }, PhysSensor3D::Type::DEAD);
	//MEGA-WALL-MAP
	CreateSensor({ -24,1,85 - 15 }, { 0,0,0,1 }, { 10,70.f,80 }, PhysSensor3D::Type::DEAD);
	//---------------------------------------------------------------------------------
	CreateSensor({ -14,1,25 }, { 0,0,0,1 }, { 14,24,2 }, PhysSensor3D::Type::BOOSTER);
	CreateSensor({ 0,0,0 }, { 0,0,0,1 }, { 14,24,2 }, PhysSensor3D::Type::BOOSTER);
	//MEGA-WALL-MAP
	CreateSensor({ -27,1,-5 }, { 0,0,0,1 }, { 10,70.f,80 }, PhysSensor3D::Type::DEAD);
	CreateSensor({ 0,1,150 }, { 0,0,0,1 }, { 50,5.f,2 }, PhysSensor3D::Type::DEAD);
	//CreateSensor({ 0,0,70 }, { 0,0,0,1 }, { 14,1.f,60 }, PhysSensor3D::Type::DEAD);
	//CreateSensor({ 0,0,70 }, { 0,0,0,1 }, { 14,1.f,60 }, PhysSensor3D::Type::DEAD);

	CreateSensor({ 300,1,10 }, { 0,0,0,1 }, { 5,5.f,5 }, PhysSensor3D::Type::REESTART);

	
}

void ModuleMap::CreateConstrains()
{
	
}

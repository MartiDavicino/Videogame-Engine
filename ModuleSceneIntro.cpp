#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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

	//CreateSensors();

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	//App->camera->LookAt(vec3(0, 0, 0));

	FirstPhaseObjects();

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

	p2List_item<Primitive*>* item = map_objects.getFirst();
	while (item)
	{
		item->data->Render();
		item = item->next;
	}

	if (App->player->lapsCounter == 0 && App->player->one == false)
	{
		CreateRectangle({ 10.0f,16,180 }, { 0,0,0,1 }, { 1,8.0f,1 }, Green);
		CreateRectangle({ 10.8f + 0.8f,18,180 }, { 30,0,0,1 }, { 1,3.0f,1 }, Green);
		App->player->one = true;
	}
	else if (App->player->lapsCounter == 1 && App->player->two == false)
	{
		CreateRectangle({ 12 - 8, 16 + 3,180 }, { 0,0,0,1 }, { 5,1,1 }, Green);
		CreateRectangle({ 14 - 8, 12 + 3,180 }, { 90,0,0,1 }, { 3,1,1 }, Green);
		CreateRectangle({ 12 - 8, 13 + 3,180 }, { 0,0,0,1 }, { 5,1,1 }, Green);
		CreateRectangle({ 10 - 8, 15 + 3,180 }, { 90,0,0,1 }, { 3,1,1 }, Green);
		CreateRectangle({ 12 - 8, 10 + 3,180 }, { 0,0,0,1 }, { 5,1,1 }, Green);
		App->player->two = true;
		App->player->one = false;
	}
	else if (App->player->lapsCounter == 2 && App->player->three == false)
	{
		CreateRectangle({ 12 - 16,18 + 1,180 }, { 0,0,0,1 }, { 5,1,1 }, Green);
		CreateRectangle({ 10 - 16,17 + 1,180 }, { 90,0,0,1 }, { 3,1,1 }, Green);
		CreateRectangle({ 12 - 16,15 + 1,180 }, { 0,0,0,1 }, { 5,1,1 }, Green);
		CreateRectangle({ 10 - 16,14 + 1,180 }, { 90,0,0,1 }, { 3,1,1 }, Green);
		CreateRectangle({ 12 - 16,12 + 1,180 }, { 0,0,0,1 }, { 5,1,1 }, Green);
		App->player->three = true;
		App->player->two = false;
	}
	else if (App->player->lapsCounter == 3 && App->player->gg == false)
	{
		float xregulator = 5.0f;
		CreateRectangle({ 0 + xregulator,16 + 13,180 }, { 0,0,0,1 }, { 5,1,1 }, Red);
		CreateRectangle({ 2 + xregulator, 15 + 13,180 }, { 90,0,0,1 }, { 3,1,1 }, Red);
		CreateRectangle({ -1.6f + xregulator,13 + 13,180 }, { 0,0,0,1 }, { 1,1,1 }, Red);
		CreateRectangle({ 2 + xregulator, 12 + 13,180 }, { 90,0,0,1 }, { 3,1,1 }, Red);
		CreateRectangle({ -2 + xregulator, 12 + 13,180 }, { 90,0,0,1 }, { 3,1,1 }, Red);
		CreateRectangle({ 0 + xregulator, 10 + 13,180 }, { 0,0,0,1 }, { 5,1,1 }, Red);

		CreateRectangle({ -6 + xregulator,16 + 13,180 }, { 0,0,0,1 }, { 5,1,1 }, Red);
		CreateRectangle({ -4 + xregulator, 15 + 13,180 }, { 90,0,0,1 }, { 3,1,1 }, Red);
		CreateRectangle({ -7.6f + xregulator,13 + 13,180 }, { 0,0,0,1 }, { 1,1,1 }, Red);
		CreateRectangle({ -4 + xregulator, 12 + 13,180 }, { 90,0,0,1 }, { 3,1,1 }, Red);
		CreateRectangle({ -8 + xregulator, 12 + 13,180 }, { 90,0,0,1 }, { 3,1,1 }, Red);
		CreateRectangle({ -6 + xregulator, 10 + 13,180 }, { 0,0,0,1 }, { 5,1,1 }, Red);
		App->player->gg = true;
		App->player->three = false;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

PhysBody3D* ModuleSceneIntro::CreateRectangle(vec3 position, vec4 rotation, vec3 size, Color s_color, float mass)
{

	Cube* object = new Cube();

	object->SetPos(position.x, position.y, position.z);
	object->size = size;
	object->color = s_color;
	object->SetRotation(rotation.x, { rotation.y, rotation.z, rotation.w });

	map_objects.add(object);
	return App->physics->AddBody(*object, mass);
}

void ModuleSceneIntro::FirstPhaseObjects()
{

	//WALL BACK---------------------------------------------------
	CreateRectangle({ 7,1,-6 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ 3,1,-6 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -1,1,-6 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -5,1,-6 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	//WALL LEFT----------------------------------------------------
	CreateRectangle({ 7,1,37 }, { 0,0,0,1 }, { 1,3.f,140 }, Black);
	//WALL RIGHT-----------------------------------------------------
	CreateRectangle({ -7,1,37 }, { 0,0,0,1 }, { 1,3.f,140 }, Black);
	//--------------------------------------------------------------
	//WALL HIGH LEFT----------------------------------------------------
	CreateRectangle({ 7,5,0 }, { 0,0,0,1 }, { 1,5.f,140 }, Black);
	//WALL HIGH RIGHT----------------------------------------------------
	CreateRectangle({ -7,6,0 }, { 0,0,0,1 }, { 1,7.f,140 }, Black);
	//---------------------------------------------------------------------
	CreateRectangle({ 6,1,108 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ 6,1,114 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ 8,1,120 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ 10,1,126 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ 10,1,132 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ 9,1,137 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ 7,1,141 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ 5,1,145 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ 4,1,147 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ 1,1,149 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -1,1,149 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -3,1,149 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -7,1,149 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -11,1,149 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -15,1,149 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -18,1,147 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -20,1,143 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -22,1,139 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -24,1,135 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -25,1,129 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -24,1,123 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -22,1,117 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -20,1,111 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -18,1,105 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	//OBSTACLES ON THE RECT

	CreateRectangle({ -16,1,99 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -10,1,99 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	//MIDDLE OBSTACLE
	CreateRectangle({ -13,1,80 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	//SIDES OBSTACLES 
	CreateRectangle({ -16,1,60 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -10,1,60 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	//MIDDLE OBSTACLE
	CreateRectangle({ -13,1,40 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);

	//RAMPAS 2nd----------------------------------------------------------------
	CreateRectangle({ -15, 1, 32 }, { -70, 1, 0, 0 }, { 5, 15, 0.3f }, Red);
	CreateRectangle({ -10, 1, 32 }, { -70, 1, 0, 0 }, { 5, 15, 0.3f }, Red);
	//----------------------------------------------------------------------

	//1nd PLATFORM
	CreateRectangle({ -15, 6.5, -15 }, { 90, 1, 0, 0 }, { 16, 20, 0.3f }, Red);
	//2rd PLATFORM
	CreateRectangle({ -15, 4.5, -35 }, { 90, 1, 0, 0 }, { 16, 20, 0.3f }, Red);
	//3th PLATFORM
	CreateRectangle({ -15, 2.5, -65 }, { 90, 1, 0, 0 }, { 16, 40, 0.3f }, Red);
	//4th PLATFORM
	CreateRectangle({ 2, 2.5, -65 }, { 90, 1, 0, 0 }, { 18, 40, 0.3f }, Red);
	//5th PLATFORM
	CreateRectangle({ 2, 2.5, -25 }, { 90, 1, 0, 0 }, { 18, 40, 0.3f }, Red);
	//CreateRectangle({ -18,1,95 }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	//--------------CURVA COMMENTED------------------------------
	/*
	CreateRectangle({ -22,1,95 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -25,1,97 }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -25,1,102 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -23,1,108 }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -26,1,128 }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -28,1,132 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -30,1,136 }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -32,1,140 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -34,1,144 }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -38,1,144 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -42,1,144 }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -47,1,144 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -53,1,144 }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -59,1,144 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);
	CreateRectangle({ -65,1,144 }, { 0,0,0,1 }, { 1,3.f,1 }, Red);
	CreateRectangle({ -71,1,144 }, { 0,0,0,1 }, { 1,3.f,1 }, Black);*/
	//
	CreateRectangle({ -6,1,114 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -5,1,120 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -3,1,126 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -3,1,132 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -6,1,136 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	//
	CreateRectangle({ -10,1,136 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -18,1,70 }, { 0,0,0,1 }, { 1,3.f,70 }, Blue);
	//SECOND LAP
	//---------------------------------------------------------------
	CreateRectangle({ -22,7,-85 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-80 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-75 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-70 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-65 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-60 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-55 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-50 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-45 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-40 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-35 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-30 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-25 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-20 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-15 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-10 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,-5 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,0 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,5 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,10 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,15 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,20 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,25 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ -22,7,30 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	//-----------------------------------------------------------------
	CreateRectangle({ -19,7,-85 }, { 0,0,0,1 }, { 4,15.f,1 }, Black);
	CreateRectangle({ -14,7,-85 }, { 0,0,0,1 }, { 4,15.f,1 }, Black);
	CreateRectangle({ -9,7,-85 }, { 0,0,0,1 }, { 4,15.f,1 }, Black);
	CreateRectangle({ -4,7,-85 }, { 0,0,0,1 }, { 4,15.f,1 }, Black);
	CreateRectangle({ 1,7,-85 }, { 0,0,0,1 }, { 4,15.f,1 }, Black);
	CreateRectangle({ 6,7,-85 }, { 0,0,0,1 }, { 4,15.f,1 }, Black);
	//-----------------------------------------------------------------
	CreateRectangle({ 7,7,-85 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-80 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-75 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-70 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-65 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-60 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-55 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-50 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-45 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-40 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-35 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-30 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-25 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-20 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-15 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-10 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,-5 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,0 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,5 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,10 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,15 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,20 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,25 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	CreateRectangle({ 7,7,30 }, { 0,0,0,1 }, { 1,15.f,3 }, Black);
	//-------------------------------------------------------------
	CreateRectangle({ -11,1,126 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	CreateRectangle({ -9,1,120 }, { 0,0,0,1 }, { 1,3.f,1 }, Blue);
	//
	//RAMPAS 1st----------------------------------------------------------------
	CreateRectangle({ 5, 1, 30 }, { 70, 1, 0, 0 }, { 5, 15, 0.3f }, Red);
	CreateRectangle({ 0, 1, 30 }, { 70, 1, 0, 0 }, { 5, 15, 0.3f }, Red);
	CreateRectangle({ -5, 1, 30 }, { 70, 1, 0, 0 }, { 5, 15, 0.3f }, Red);
	//--------------------------------------------------------------------------
	CreateRectangle({ 0, 1, 49 }, { 0, 1, 0, 0 }, { 5, 5, 8.f }, Black);
	CreateRectangle({ 0, 4, 60 }, { 80, 1, 0, 0 }, { 5, 15, 0.2f }, Black);
	CreateRectangle({ 0, 2, 82 }, { -85, 1, 0, 0 }, { 5, 42, 0.2f }, Black);
	//--------------------------------------------------------------------------
	CreateRectangle({ 320, 2, 0 }, { 0, 1, 0, 0 }, { 5, 42, 50.0f }, Red);
	CreateRectangle({ 280, 2, 0 }, { 0, 1, 0, 0 }, { 5, 42, 50.0f }, Red);
	CreateRectangle({ 300, 2, 20 }, { 0, 1, 0, 0 }, { 40, 42, 5.0f }, Red);
	CreateRectangle({ 300, 2, -20 }, { 0, 1, 0, 0 }, { 40, 42, 5.0f }, Red);
	//--------------------------------------------------------------------------
	CreateRectangle({ 300, 1, 10 }, { 0, 1, 0, 0 }, { 4, 42, 4.0f }, White);

	//----------Finish Line--------------------------
	//c_finish.Size(30, 10, 1);
	//finish_line = App->physics->AddBody(c_finish, 0);
	//finish_line->SetPos(0, 0, 20);
	//finish_line->GetTransform(&c_finish.transform);
	//finish_line->SetAsSensor(true);
	////finish_line->isChecked = false;
	////finish_line->isDeath = false;
	//finish_line->collision_listeners.add(this);

	//---------------GG-----------------------------------------------

	

}




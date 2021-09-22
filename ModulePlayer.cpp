#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
	laps = false;
	lapsCounter = 0;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;
	boostCounter = 1;
	boostAceleration = 0;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 10.0f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 1.0f;
	car.maxSuspensionTravelCm = 500.0f;
	car.frictionSlip = 10.0f;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.1f;
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

	car.spawnPosition = { 0, 2,10 };

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(car.spawnPosition.x, car.spawnPosition.y, car.spawnPosition.z);

	VehicleInfo carriCoche;
	carriCoche.chassis_size.Set(2, 1, 2);
	carriCoche.chassis_offset.Set(0, 1.5, 0);
	carriCoche.mass = 200.0f;
	carriCoche.suspensionStiffness = 15.88f;
	carriCoche.suspensionCompression = 0.83f;
	carriCoche.suspensionDamping = 0.88f;
	carriCoche.maxSuspensionTravelCm = 1000.0f;
	carriCoche.frictionSlip = 50.5;
	carriCoche.maxSuspensionForce = 6000.0f;

	connection_height = 1.8f;

	half_width = carriCoche.chassis_size.x * 0.5f;
	half_length = carriCoche.chassis_size.z * 0.5f;

	carriCoche.num_wheels = 2;
	carriCoche.wheels = new Wheel[2];

	carriCoche.carriSpawnPosition = { 0, 2, 5};

	carriCoche.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, 0.0f);
	carriCoche.wheels[0].direction = direction;
	carriCoche.wheels[0].axis = axis;
	carriCoche.wheels[0].suspensionRestLength = suspensionRestLength;
	carriCoche.wheels[0].radius = wheel_radius;
	carriCoche.wheels[0].width = wheel_width;
	carriCoche.wheels[0].front = true;
	carriCoche.wheels[0].drive = true;
	carriCoche.wheels[0].brake = false;
	carriCoche.wheels[0].steering = true;

	carriCoche.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, 0.0f);
	carriCoche.wheels[1].direction = direction;
	carriCoche.wheels[1].axis = axis;
	carriCoche.wheels[1].suspensionRestLength = suspensionRestLength;
	carriCoche.wheels[1].radius = wheel_radius;
	carriCoche.wheels[1].width = wheel_width;
	carriCoche.wheels[1].front = true;
	carriCoche.wheels[1].drive = true;
	carriCoche.wheels[1].brake = false;
	carriCoche.wheels[1].steering = true;
	
	trolley = App->physics->AddVehicle(carriCoche);
	trolley->SetPos(carriCoche.carriSpawnPosition.x, carriCoche.carriSpawnPosition.y, carriCoche.carriSpawnPosition.z);

	App->physics->AddConstraintP2P(*vehicle, *trolley, vec3(0, -0.6f, -1.6f), vec3(0, 0, 2));

	App->camera->vehicleToLook = vehicle;

	isBoosted = false;

	//Checkpoints information
	

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
	if (isBoosted)
	{
		boostCounter++;

		boostAceleration = MAX_ACCELERATION * 3;

		if (boostCounter > 200)
		{
			isBoosted = false;
			boostAceleration = 0;
		}
	}
	
	else
		turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (vehicle->GetKmh() > 30)
		{
			App->audio->PlayFx(App->audio->brakeSoundFx);
		}
		

		if (roundf(vehicle->GetKmh()) <= 0)
		{
			acceleration = -MAX_ACCELERATION;
		}
		else
		{
			brake = BRAKE_POWER;
		}
	}

	if (vehicle->GetKmh() > 83.0) acceleration = -MAX_ACCELERATION;
	if (vehicle->GetKmh() < -83.0) acceleration = MAX_ACCELERATION;

	vehicle->ApplyEngineForce(acceleration);


	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();
	trolley->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	acceleration = boostAceleration;

	return UPDATE_CONTINUE;
}

void ModulePlayer::FinishGame()
{
	if (!gameHasFinished)
	{
		App->audio->StopMusic(0.f);
		App->audio->PlayFx(App->audio->winSoundFx);	
		gameHasFinished = true;
	}

	if (gameHasFinished)
	{
		

		//restart_timer -= dt;
		btVector3 cameraLerp = { App->camera->Position.x, App->camera->Position.y, App->camera->Position.z };

		vec3 a = { App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getX(),
			App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getY(),
			App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getZ() };

		cameraLerp = lerp(cameraLerp, { 100, 100, 0 }, 0.01f);
		App->camera->LookAt(a);
		App->camera->Position = { cameraLerp.getX(), cameraLerp.getY(), cameraLerp.getZ() };

		/*if (restart_timer <= 0.f)
		{
			RespawnCar();
			App->audio->PlayMusic("music/DejaVu.ogg");
			App->camera->followCar = true;
			restart_timer = 5.f;
			game_finished = false;
		}*/
	}
}

void ModulePlayer::RespawnCar()
{
	App->audio->PlayFx(App->audio->respawnSoundFx);

	App->physics->SetGravity({ GRAVITY.getX(), GRAVITY.getY(), GRAVITY.getZ() });
	mat4x4 carMatrix;
	mat4x4 carriCoche;
	vehicle->GetTransform(&carMatrix);
	trolley->GetTransform(&carriCoche);

	//Correct position and rotation
	carMatrix.rotate(0, { 0, 1, 0 });
	carriCoche.rotate(0, { 0, 1, 0 });
	if (App->map->checkPointsSpawn[0].isEnabled == false)
	{
		LOG("Respawning vehicle");
		carMatrix.translate(vehicle->info.spawnPosition.x, vehicle->info.spawnPosition.y, vehicle->info.spawnPosition.z);
		carriCoche.translate(trolley->info.carriSpawnPosition.x, trolley->info.carriSpawnPosition.y, trolley->info.carriSpawnPosition.z);
	}
	else
	{
		for (int i = 0; App->map->checkPointsSpawn[i].isEnabled == true; i++)
		{
			if(App->map->checkPointsSpawn[i+1].isEnabled !=true )
			{

				if (App->map->checkPointsSpawn[i].isEnabled == true)
				{
					LOG("Respawning vehicle from ckeckpoint %d", i + 1);
					carMatrix.translate(App->map->checkPointsSpawn[i].pos.x, App->map->checkPointsSpawn[i].pos.y, App->map->checkPointsSpawn[i].pos.z);

					break;
				}
			}
		}

	}
	

	//Set corrected transform
	vehicle->SetTransform(&carMatrix.M[0]);
	trolley->SetTransform(&carriCoche.M[0]);
	//Correct velocity (set to 0)
	vehicle->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	trolley->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	vehicle->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });
	trolley->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });

	vehicle->rotating = false;
	trolley->rotating = false;
	vehicle->currentAngle = 0;
	trolley->currentAngle = 0;

	App->player->one = false;
	App->player->two = false;
	App->player->three = false;
	App->player->gg = false;

	p2List_item<PhysSensor3D*>* item = App->map->map_sensors.getFirst();
	while (item)
	{
		item->data->isEnabled = true;
		item = item->next;
	}
}

void ModulePlayer::DeadCar()
{
	App->physics->SetGravity({ GRAVITY.getX(), GRAVITY.getY(), GRAVITY.getZ() });
	mat4x4 carMatrix;
	mat4x4 carriCoche;
	vehicle->GetTransform(&carMatrix);
	trolley->GetTransform(&carriCoche);

	//Correct position and rotation
	carMatrix.rotate(0, { 0, 1, 0 });
	carriCoche.rotate(0, { 0, 1, 0 });
	if (App->map->checkPointsSpawn[0].isEnabled == false)
	{
		LOG("Respawning vehicle");
		carMatrix.translate(300, 1, 0);
		carriCoche.translate(300, 1, -5);
	}
	else
	{
		for (int i = 0; App->map->checkPointsSpawn[i].isEnabled == true; i++)
		{
			if (App->map->checkPointsSpawn[i + 1].isEnabled != true)
			{

				if (App->map->checkPointsSpawn[i].isEnabled == true)
				{
					LOG("Respawning vehicle from ckeckpoint %d", i + 1);
					carMatrix.translate(App->map->checkPointsSpawn[i].pos.x, App->map->checkPointsSpawn[i].pos.y, App->map->checkPointsSpawn[i].pos.z);

					break;
				}
			}
		}

	}


	//Set corrected transform
	vehicle->SetTransform(&carMatrix.M[0]);
	trolley->SetTransform(&carriCoche.M[0]);
	//Correct velocity (set to 0)
	vehicle->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	trolley->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	vehicle->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });
	trolley->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });

	vehicle->rotating = false;
	trolley->rotating = false;
	vehicle->currentAngle = 0;
	trolley->currentAngle = 0;

	App->player->one = false;
	App->player->two = false;
	App->player->three = false;
	App->player->gg = false;

	p2List_item<PhysSensor3D*>* item = App->map->map_sensors.getFirst();
	while (item)
	{
		item->data->isEnabled = true;
		item = item->next;
	}
}

void ModulePlayer::PickBooster()
{
	isBoosted = true;
}


#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1500.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 250.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void FinishGame();
	void RespawnCar();
	void DeadCar();
	void PickBooster();

public:

	PhysVehicle3D* vehicle;
	PhysVehicle3D* trolley;

	float turn;
	float acceleration;
	float boostedAcceleration = 100;
	float brake;
	bool laps;
	int lapsCounter;

	bool isBoosted;

	bool gameHasFinished = false;

	bool one = false;
	bool two = false;
	bool three = false;
	bool gg = false;
private:
	int boostCounter;
	float boostAceleration;
};
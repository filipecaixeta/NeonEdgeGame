// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_GALLAHAD_H_
#define INCLUDE_GALLAHAD_H_

#include "Drone.h"
#include "Player.h"
#include "Timer.h"
#include "TileMap.h"
#include "GallahadInputComponent.h"
#include "GallahadGraphicsComponent.h"
#include "Drone.h"

#define HIDE_TIME 500
#define DIE_TIME 800
#define INITIAL_CUTSCENE_INDEX 7
#define INITIAL_PROJECT_X_AXIS 0.8f
#define INITIAL_PROJECT_Y_AXIS 0
#define INITIAL_LIFE_TIME_PROJECT 1200
#define INITIAL_POWER_PROJECT 1
#define LIMIT_TIME_HIDE_0 2000
#define LIMIT_TIME_HIDE_1 1500
#define LIMIT_TIME_HIDE_2 1000
#define LIMIT_TIME_HIDE_OTHERS 500
#define ENERGY_USED 1
#define CLAMP_L 0
#define CLAMP_U 5
#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f


class Gallahad : public Player {
private:
    void UpdateTimers(float deltaTime);
    GameObject *drone = nullptr;
    Timer isHiding;
    bool isShooting = false;
    bool active = false;
    bool done = false;

public:
    Gallahad(ItemsManager* itemManager, int x, int y, GameObject *setDrone);
    ~Gallahad();
    void Attack();
    void StartHiding();
    void StartShooting();
    void StopShooting();
    bool IsHiding();
    bool IsShooting();
    void Activate(bool on);
    bool Active();
    Drone * GetDrone();
    void Update(TileMap *map, float deltaTime);
};

#endif // INCLUDE_GALLAHAD_

/**
    Copyright 2017 Neon Edge Game
    File Name: Player.cpp
    Header File Name: Player.h
    Class Name: Player
    Objective: Manages the behavior of some aspects of the player.
*/

#include "Player.h"
#include "Projectile.h"

/**
    Objective: Constructor of the class Player.
    @param ItensManager* itemManager
    @param int x - Coordinate of the player.
    @param int y - Coordinate of the player.
    @return Instance to the class Player.
*/
Player::Player(ItensManager* itemManager, int x, int y):
    Character(x,y),
    inputComponent(nullptr),
    itemManager(itemManager),
    skills( {
            false,
                false,
                true,true,
                true,
                false,
                false
     }
                 ),
    skillPoints(0),
    energy(5),
    regenCD(500),
    crouching(false),
    crouchingEdge(true) {
    name = "Player"; //Sets the Player's name.
    hitpoints = MAX_HITPOINTS; //Sets the hitpoints of the player to 10.
}

/**
    Objective: Destructor of the class Player.
    @param None.
    @return None.
*/
Player::~Player() {

}

/**
    Objective: Checks if is a player.
    @param None.
    @return bool - Returns TRUE.
*/
bool Player::IsPlayer() {
    return true;
}

/**
    Objective: Gets the energy of player.
    @param None.
    @return int energy - Returns the amount of energy of the player.
*/
int Player::GetEnergy() {
    return energy;
}

/**
    Objective: Performs the action of crouch.
    @param: None.
    @return: None.
*/
void Player::Crouch() {
    if (crouchingEdge) {
        crouchingEdge = false;
        soundComponent->Crouching();
    }
    crouching = true;
}

/**
    Objective: Performs the action of stand.
    @param None.
    @return None.
*/
void Player::Stand() {
    crouching = false;
    crouchingEdge = true;
}

/**
    Objective: Checks if the player is crouching or not.
    @param None.
    @return bool crouching - Return true if the player is crouching.
*/
bool Player::Crouching() {
    return crouching;
}

/**
    Objective: Performs an action due to an item used by the player.
    @param string itemName - The name of the item.
    @return None.
*/
void Player::EvalItem(std::string itemName) {
    if (itemName == "Healing Potion 25") {
        hitpoints += MAX_HITPOINTS*0.5;
        clamp(hitpoints, 0, MAX_HITPOINTS);
    }
    if (itemName == "Healing Potion 50") {
        hitpoints += MAX_HITPOINTS*0.5;
        clamp(hitpoints, 0, MAX_HITPOINTS);
    }
    if (itemName == "Energy Potion 25") {
        energy += 2;
        clamp(energy, 0, 5);
    }
    if (itemName == "Energy Potion 50") {
        energy += 5;
        clamp(energy, 0, 5);
    }
    if (itemName == "Skill Coin") {
        skillPoints++;
    }
}

/**
    Objective: Manages the reactions of other objects in collision with the player.
    @param GameObject* other - The object that is in collision with the player.
    @return None.
*/
void Player::NotifyObjectCollision(GameObject* other) {
    Character::NotifyObjectCollision(other);
    if (other->IsCharacter() && !other->IsPlayer()) {
        Character* c = (Character*) other;
        if (c->Attacking())
            Damage(c->Power());
    }
    if (other->Is("Projectile")) {
        Projectile* p = (Projectile*) other;
        if (!(p->GetOwner() == "Gallahad"))
            Damage(p->Power());
    }
    if (other->Is("Energy")) {
        if (crouching && !regenCD.IsRunning()) {
            regenCD.Start();
            energy += 1;
            clamp(energy, 0, 5);
        }
    }
    if (other->Is("Life")) {
        if (crouching && !regenCD.IsRunning()) {
            regenCD.Start();
            hitpoints += 1;
            clamp(hitpoints, 0, 10);
        }
    }
}

/**
    Objective: Updates the time of the cool down regeneration.
    @param float dt - the amount of time to cool down the regeneration.
    @return None.
*/
void Player::UpdateTimers(float dt) {
    Character::UpdateTimers(dt);
    regenCD.Update(dt);
}

void Player::Update(TileMap* map, float dt) {
    UpdateTimers(dt);
    inputComponent->Update(this, dt);
    physicsComponent.Update(this, map, dt);
    if (OutOfBounds(map)) {
        SetPosition(Vec2(startingX, startingY));
    }
    graphicsComponent->Update(this, dt);
}

/**
    Copyright (c) 2017 Neon Edge Game
    File Name: Player.cpp
    Header File Name: Player.h
    Class Name: Player
    Objective: manages the behavior of some aspects of the player.
*/

#include "Player.h"
#include "Projectile.h"

/**
    Objective: constructor of the class Player.
    @param ItensManager* itemManager
    @param int x - coordinate of the player.
    @param int y - coordinate of the player.
    @return Player - instance of the class Player.
*/
Player::Player(ItensManager* itemManager, int x, int y):
    Character(x,y),  // Player's positions in the screen.
    inputComponent(nullptr),
    itemManager(itemManager),
    skills( {
            false,
                false,
                true,true,
                true,
                false,
                false
    } ),  // Sets the default enabled skills.
    skillPoints(0),
    energy(5),  // Sets the energy of the player to 5.
    regenCD(500),  // The time of the cool down regeneration in miliseconds.
    crouching(false),  // Default state: standing.
    crouchingEdge(true) {
    name = "Player";  // Sets the Player's name.
    characterHealthPoints = MAX_CHARACTERHEALTHPOINTS;  // Sets the hitpoints of the player to 10.
}

/**
    Objective: destructor of the class Player.
    @param none.
    @return none.
*/
Player::~Player() {

}

/**
    Objective: checks if is a player.
    @param none.
    @return bool - returns TRUE.
*/
bool Player::IsPlayer() {
    return true;
}

/**
    Objective: gets the energy of player.
    @param none.
    @return int energy - returns the amount of energy of the player.
*/
int Player::GetEnergy() {
    return energy;
}

/**
    Objective: performs the action of crouch.
    @param: none.
    @return: none.
*/
void Player::Crouch() {
    if (crouchingEdge) {
        crouchingEdge = false;
        soundComponent->Crouching();  // Performs the crouching sound in case that the player is
                                      // standing.
    }
    crouching = true;
}

/**
    Objective: performs the action of stand.
    @param none.
    @return none.
*/
void Player::Stand() {
    crouching = false;
    crouchingEdge = true;
}

/**
    Objective: checks if the player is crouching or not.
    @param none.
    @return bool crouching - return true if the player is crouching.
*/
bool Player::Crouching() {
    return crouching;
}

/**
    Objective: performs an action due to an item used by the player.
    @param string itemName - the name of the item.
    @return none.
*/
void Player::EvalItem(std::string itemName) {
    // Heals the hitpoints of the player by 25% of the total.
    if (itemName == "Healing Potion 25") {
        characterHealthPoints += MAX_CHARACTERHEALTHPOINTS * 0.25;
        clamp(characterHealthPoints, 0, MAX_CHARACTERHEALTHPOINTS);
    }
    // Heals the hitpoints of the player by 50% of the total.
    if (itemName == "Healing Potion 50") {
        characterHealthPoints += MAX_CHARACTERHEALTHPOINTS * 0.5;
        clamp(characterHealthPoints, 0, MAX_CHARACTERHEALTHPOINTS);
    }
    // Adds 2 energy points.
    if (itemName == "Energy Potion 25") {
        energy += 2;
        clamp(energy, 0, 5);
    }
    // Adds 5 energy points.
    if (itemName == "Energy Potion 50") {
        energy += 5;
        clamp(energy, 0, 5);
    }
    // Adds 1 point to the skills.
    if (itemName == "Skill Coin") {
        skillPoints++;
    }
}

/**
    Objective: manages the reactions of other objects in collision with the player.
    @param GameObject* other - the object that is in collision with the player.
    @return none.
*/
void Player::NotifyObjectCollision(GameObject* other) {
    Character::NotifyObjectCollision(other);
    // The player gets damaged if the object is attacking.
    if (other->IsCharacter() && !other->IsPlayer()) {
        Character* c = (Character*) other;
        if (c->Attacking()) {
            Damage(c->CharacterPower());
        }
    }
    if (other->Is("Projectile")) {
        Projectile* p = (Projectile*) other;
        if (!(p->GetOwner() == "Gallahad"))
            Damage(p->CharacterPower());
    }
    // Restores some energy of the player.
    if (other->Is("Energy")) {
        if (crouching && !regenCD.IsRunning()) {
            regenCD.Start();
            energy += 1;
            clamp(energy, 0, 5);
        }
    }
    // Restores some hitpoints of the player.
    if (other->Is("Life")) {
        if (crouching && !regenCD.IsRunning()) {
            regenCD.Start();
            characterHealthPoints += 1;
            clamp(characterHealthPoints, 0, 10);
        }
    }
}

/**
    Objective: updates the time of the cool down regeneration.
    @param float dt - the amount of time to cool down the regeneration.
    @return none.
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

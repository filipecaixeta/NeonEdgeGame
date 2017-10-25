/**
 * Copyright (c) 2017 Neon Edge Game
 * File Name: Player.cpp
 * Header File Name: Player.h
 * Class Name: Player
 * Objective: manages the behavior of some aspects of the player.
 */

#include "Player.h"
#include "Projectile.h"
#include <assert.h>

/**
    Objective: constructor of the class Player.
    @param ItensManager* itemManager
    @param int x - coordinate of the player.
    @param int y - coordinate of the player.
    @return Player - instance of the class Player.
*/
Player::Player(ItemsManager* itemManager, int x, int y): Character(x,y){
    inputComponent = nullptr;
    this->itemManager = itemManager ;

	// Sets the default enabled skills.
    skills[0] = false;
    skills[1] = false;
    skills[2] = true;
    skills[3] = true;
    skills[4] = true;
    skills[5] = false;
    skills[6] = false;
	skillPoints = 0;
	energy = 5;  // Sets the energy of the player to 5.
	regenCD = 500;  // The time of the cool down regeneration in miliseconds.
	isCrouching = false;  // Default state: standing.
	isStading = true;
    name = "Player";  // Sets the Player's name.
    hitpoints = MAX_HITPOINTS;  // Sets the hitpoints of the player to 10.

}

/**
 * Objective: destructor of the class Player.
 *
 * @param none.
 * @return none.
 */
Player::~Player() {

}

/**
 * Objective: checks if is a player.
 *
 * @param none.
 * @return bool - returns TRUE.
 */
bool Player::IsPlayer() {
    return true;
}

/**
 * Objective: gets the energy of player.
 *
 * @param none.
 * @return int energy - returns the amount of energy of the player.
 */
int Player::GetEnergy() {
    return energy;
}

/**
 * Objective: performs the action of crouch.
 *
 * @param: none.
 * @return: none.
 */
void Player::Crouch() {
    if (isStading) {
        isStading = false;
        assert(soundComponent != nullptr);
        soundComponent->SoundCrouching();   // Performs the crouching sound in case that the player is
                                            // standing.
    } else {
        // It does nothing.
    }
    isCrouching = true;
}

/**
 * Objective: performs the action of stand.
 *
 * @param none.
 * @return none.
 */
void Player::Stand() {
    isCrouching = false;
    isStading = true;
}

/**
 * Objective: checks if the player is crouching or not.
 *
 * @param none.
 * @return bool crouching - return true if the player is crouching.
*/
bool Player::IsCrouching() {
    return isCrouching;
}

/**
 * Objective: performs an action due to an item used by the player.
 *
 * @param string itemName - the name of the item.
 * @return none.
 */
void Player::EvalItem(std::string itemName) {
    assert(itemName != "");

    // Heals the hitpoints of the player by 25% of the total.
    if (itemName == "Healing Potion 25") {
        hitpoints += MAX_HITPOINTS*0.25;
        clamp(hitpoints, 0, MAX_HITPOINTS);
    } else
    // Heals the hitpoints of the player by 50% of the total.
    if (itemName == "Healing Potion 50") {
        hitpoints += MAX_HITPOINTS*0.5;
        clamp(hitpoints, 0, MAX_HITPOINTS);
    } else
    // Adds 2 energy points.
    if (itemName == "Energy Potion 25") {
        energy += 2;
        clamp(energy, 0, 5);
    } else
    // Adds 5 energy points.
    if (itemName == "Energy Potion 50") {
        energy += 5;
        clamp(energy, 0, 5);
    } else
    // Adds 1 point to the skills.
    if (itemName == "Skill Coin") {
        skillPoints++;
    } else {
        // It does nothing.
    }
}

/**
 * Objective: manages the reactions of other objects in collision with the player.
 *
 * @param GameObject* other - the object that is in collision with the player.
 * @return none.
 */
void Player::NotifyObjectCollision(GameObject* other) {
    assert(other != nullptr);

    Character::NotifyObjectCollision(other);
    // The player gets damaged if the object is attacking.
    if (other->IsCharacter() && !other->IsPlayer()) {
        Character* c = (Character*) other;
        if (c->Attacking()) {
            Damage(c->Power());
        } else {
            // It does nothing.
        }
    } else
        // It does nothing.
    if (other->Is("Projectile")) {
        Projectile* p = (Projectile*) other;
        if (!(p->GetOwner() == "Gallahad")) {
            Damage(p->Power());
        } else {
            // It does nothing.
        }
    } else
    // Restores some energy of the player.
    if (other->Is("Energy")) {
        if (isCrouching && !regenCD.IsRunning()) {
            regenCD.Start();
            energy += 1;
            clamp(energy, 0, 5);
        } else {
            // It does nothing.
        }
    } else
    // Restores some hitpoints of the player.
    if (other->Is("Life")) {
        if (isCrouching && !regenCD.IsRunning()) {
            regenCD.Start();
            hitpoints += 1;
            clamp(hitpoints, 0, 10);
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
}

/**
 * Objective: updates the time of the cool down regeneration.
 *
 * @param float dt - the amount of time to cool down the regeneration.
 * @return none.
 */
void Player::UpdateTimers(float dt) {
    assert(dt >= FLOAT_MIN_SIZE && dt <= FLOAT_MAX_SIZE);

    Character::UpdateTimers(dt);
    regenCD.Update(dt);
}

void Player::Update(TileMap* map, float dt) {
    assert(dt >= FLOAT_MIN_SIZE && dt <= FLOAT_MAX_SIZE);
    assert(map != nullptr);

    UpdateTimers(dt);
    inputComponent->Update(this, dt);
    physicsComponent.Update(this, map, dt);
    if (OutOfBounds(map)) {
        SetPosition(Vec2(startingX, startingY));
    } else {
        // It does nothing.
    }
    graphicsComponent->Update(this, dt);
}

/**
 * Copyright (c) 2017 Neon Edge
 * File Name: SoundComponent.cpp
 * Header File Name: SoundComponent.h
 * Class Name: SoundComponent
 * Objective: Class responsible for the sound effects of the game.
 */

#include <assert.h>

#include "SoundComponent.h"

/**
 * Objective: Construction method that loads the sound effects.
 *
 * @param string playerName - Refers to the first part of the audio file name.
 * @return - none.
 */
SoundComponent::SoundComponent(std::string playerName) {

    // Finds the audio files and defines their names.
    sounds.emplace("Crouching", Sound("Agachamento.ogg"));
    sounds.emplace("Jump", Sound("Pulo.ogg"));
    sounds.emplace("Flying", Sound("DroneVoando.wav"));
    sounds.emplace("Attack", Sound(playerName + "Ataque.ogg"));
    sounds.emplace("Damage", Sound(playerName + "Dano.wav"));
    sounds.emplace("Die", Sound(playerName + "Morte.wav"));
    sounds.emplace("Item", Sound("Item.ogg"));
}

/**
 * Objective: Function responsible for controlling the states of the sound effects (pause, play, repeat ...).
 *
 * @param String soundName - Receives a string referring to the name of the effect.
 * @param int action - Integer referring to the occurrence of an action of the character.
 * @return - none.
 */
void SoundComponent::SoundPlay(std::string soundName, int action) {

    // Checks if the sound effects are null or are playing.
    if (!sounds.count(soundName) || sounds[soundName].IsPlaying()) {
        return;
    } else {
        // It does nothing.
    }

    // Checks if there is action of the character and stop the sound effect.
    assert(action >= INT_SIZE_MIN && action <= INT_SIZE_MAX);
    if (action&SOUND_STOP) {
        sounds[soundName].SoundStop();
    } else {
        // It does nothing.
    }

    // Checks if there is an action of the character and initiates the sound effect.
    assert(action >= INT_SIZE_MIN && action <= INT_SIZE_MAX);
    if ((action&SOUND_PLAY) || (action&SOUND_PLAY_ONCE)) {
        sounds[soundName].SoundPlay(0);
    } else {
        // It does nothing.
    }

    // Checks if there is a repeat of the character's last action and repeat the sound effect.
    assert(action >= INT_SIZE_MIN && action <= INT_SIZE_MAX);
    if ((action&SOUND_REPEAT)) {
        sounds[soundName].SoundPlay(-1);
    } else {
        // It does nothing.
    }
}

/**
 * Objective: Determines the sound reproduction of the pump.
 *
 * @param int action - Receives an integer (action) that reports the occurrence of a character action.
 * @return - none.
 */
void SoundComponent::SoundBomb(int action) {
    assert(action >= INT_SIZE_MIN && action <= INT_SIZE_MAX);
    SoundPlay("Bomb", action);
}

/**
 * Objective: Informs the method responsible for reproducing the effects that the sound of item collection should be reproduced.
 * @param - Receives an integer (action) that reports the occurrence of a character action.
 * @return - none.
 */
void SoundComponent::SoundItem(int action) {
    assert(action >= INT_SIZE_MIN && action <= INT_SIZE_MAX);
    SoundPlay("Item", action);
}

/**
 * Objective: Informs the method responsible for reproducing the effects that the squat sound of the character must be reproduced.
 * @param - Receives an integer (action) that reports the occurrence of a character action.
 * @return - none.
 */
void SoundComponent::SoundCrouching(int action) {
    assert(action >= INT_SIZE_MIN && action <= INT_SIZE_MAX);
    SoundPlay("Crouching", action);
}

/**
 * Objective: Informs the method responsible for reproducing the effects that the "jump" sound of the character must be reproduced.
 *
 * @param - Receives an integer (action) that reports the occurrence of a character action.
 * @return - none.
 */
void SoundComponent::SoundJump(int action) {
    assert(action >= INT_SIZE_MIN && action <= INT_SIZE_MAX);
    SoundPlay("Jump", action);
}

/**
 * Objective: Informs the method responsible for reproducing the effects that the attack sound of the character must be reproduced.
 *
 * @param - Receives an integer (action) that reports the occurrence of a character action.
 * @return - none.
 */
void SoundComponent::SoundAttack(int action) {

    SoundPlay("Attack", action);
}

/**
 * Objective: Informs the method responsible for reproducing the effects that the death sound of the character must be reproduced.
 *
 * @param - Receives an integer (action) that reports the occurrence of a character action.
 * @return - none.
 */
void SoundComponent::SoundDie(int action) {

    SoundPlay("Die", action);
}

/**
 * Objective: Informs the method responsible for reproducing the effects that the damage sound of the character must be reproduced.
 *
 * @param - Receives an integer (action) that reports the occurrence of a character action.
 * @return - none.
 */
void SoundComponent::SoundDamage(int action) {

    SoundPlay("Damage", action);
}

/**
 * Objective: It informs the method responsible for reproducing the effects that the sound of the flying character must be reproduced.
 *
 * @param - Receives an integer (action) that reports the occurrence of a character action.
 * @return - none.
 */
void SoundComponent::SoundFlying(int action) {
    assert(action >= INT_SIZE_MIN && action <= INT_SIZE_MAX);
    SoundPlay("Flying", action);
}

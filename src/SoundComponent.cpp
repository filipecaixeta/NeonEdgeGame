/**
    Copyright (c) 2017 Neon Edge
    File Name: SoundComponent.cpp
    Header File Name: SoundComponent.h
    Class Name: SoundComponent
    Objective: Class responsible for the sound effects of the game.

*/

#include "SoundComponent.h"

/**
    Objective: Construction method that loads the sound effects.
    @param string playerName - Refers to the first part of the audio file name.
    @return - none.

*/
SoundComponent::SoundComponent(std::string playerName) {

    // Finds the audio files and defines their names.
    sounds.emplace("Crouching",Sound("Agachamento.ogg"));
    sounds.emplace("Jump",Sound("Pulo.ogg"));
    sounds.emplace("Flying",Sound("DroneVoando.wav"));
    sounds.emplace("Attack",Sound(playerName+"Ataque.ogg"));
    sounds.emplace("Damage",Sound(playerName+"Dano.wav"));
    sounds.emplace("Die",Sound(playerName+"Morte.wav"));
    sounds.emplace("Item",Sound("Item.ogg"));
}

/**
    Objective: Function responsible for controlling the states of the sound effects (pause, play, repeat ...).
    @param String soundName - Receives a string referring to the name of the effect.
    @param int options - Integer referring to the occurrence of an action of the character.
    @return - none.

*/
void SoundComponent::Play(std::string soundName, int options) {

    // Checks if the sound effects are null or are playing.
    if (!sounds.count(soundName) || sounds[soundName].IsPlaying()) {
        return;
    }

    // Checks if there is action of the character and stop the sound effect.
    if (options&SOUND_STOP) {
        sounds[soundName].Stop();
    }

    // Checks if there is an action of the character and initiates the sound effect.
    if ((options&SOUND_PLAY) || (options&SOUND_PLAY_ONCE)) {
        sounds[soundName].Play(0);
    }

    // Checks if there is a repeat of the character's last action and repeat the sound effect.
    if ((options&SOUND_REPEAT)) {
        sounds[soundName].Play(-1);
    }
}

/**
    Objective: Determines the sound reproduction of the pump.
    @param int options - Receives an integer (options) that reports the occurrence of a character action.
    @return - none.

*/
void SoundComponent::Bomb(int options) {
    Play("Bomb", options);
}

/**
    Objective: Informs the method responsible for reproducing the effects that the sound of item collection should be reproduced.
    @param - Receives an integer (options) that reports the occurrence of a character action.
    @return - none.

*/
void SoundComponent::Item(int options) {
    Play("Item", options);
}

/**
    Objective: Informs the method responsible for reproducing the effects that the squat sound of the character must be reproduced.
    @param - Receives an integer (options) that reports the occurrence of a character action.
    @return - none.

*/
void SoundComponent::Crouching(int options) {
    Play("Crouching", options);
}

/**
    Objective: Informs the method responsible for reproducing the effects that the "jump" sound of the character must be reproduced.
    @param - Receives an integer (options) that reports the occurrence of a character action.
    @return - none.

*/
void SoundComponent::Jump(int options) {
    Play("Jump", options);
}

/**
    Objective: Informs the method responsible for reproducing the effects that the attack sound of the character must be reproduced.
    @param - Receives an integer (options) that reports the occurrence of a character action.
    @return - none.

*/
void SoundComponent::Attack(int options) {
    Play("Attack", options);
}

/**
    Objective: Informs the method responsible for reproducing the effects that the death sound of the character must be reproduced.
    @param - Receives an integer (options) that reports the occurrence of a character action.
    @return - none.

*/
void SoundComponent::Die(int options) {
    Play("Die", options);
}

/**
    Objective: Informs the method responsible for reproducing the effects that the damage sound of the character must be reproduced.
    @param - Receives an integer (options) that reports the occurrence of a character action.
    @return - none.

*/
void SoundComponent::Damage(int options) {
    Play("Damage", options);
}

/**
    Objective: It informs the method responsible for reproducing the effects that the sound of the flying character must be reproduced.
    @param - Receives an integer (options) that reports the occurrence of a character action.
    @return - none.

*/
void SoundComponent::Flying(int options) {
    Play("Flying", options);
}

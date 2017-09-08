/*
  Copyright 2017 Neon Edge Game
  File Name: SoundComponent.cpp
  Header File Name: SoundComponent.h
  Class Name: SoundComponent
  Objective: Class responsible for the sound effects of the game.
*/

#include "SoundComponent.h"

/*
  Function Objective: Construction method that loads the sound effects.
  param: string playerName refers to the first part of the audio file name.
  return: No return.
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

/*
  Function Objective: Function responsible for controlling the states of the sound effects (pause, play, repeat ...).
  param:  Receives a string referring to the name of the effect and an integer referring to the occurrence of an action of the character.
  return: No return.
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

/*
  Function Objective: Determines the sound reproduction of the pump.
  param: Receives an integer (options) that reports the occurrence of a character action.
  return: No return.
*/
void SoundComponent::Bomb(int options) {
    Play("Bomb", options);
}
/*
  Function Objective: Informs the method responsible for reproducing the effects that the sound of item collection should be reproduced.
  param: Receives an integer (options) that reports the occurrence of a character action.
  return:  No return.
*/
void SoundComponent::Item(int options) {
    Play("Item", options);
}

/*
  Function Objective: Informs the method responsible for reproducing the effects that the squat sound of the character must be reproduced.
  param: Receives an integer (options) that reports the occurrence of a character action.
  return:  No return.
*/
void SoundComponent::Crouching(int options) {
    Play("Crouching", options);
}

/*
  Function Objective: Informs the method responsible for reproducing the effects that the "jump" sound of the character must be reproduced.
  param: Receives an integer (options) that reports the occurrence of a character action.
  return: No return.
*/
void SoundComponent::Jump(int options) {
    Play("Jump", options);
}

/*
  Function Objective: Informs the method responsible for reproducing the effects that the attack sound of the character must be reproduced.
  param: Receives an integer (options) that reports the occurrence of a character action.
  return: No return.
*/
void SoundComponent::Attack(int options) {
    Play("Attack", options);
}

/*
  Function Objective: Informs the method responsible for reproducing the effects that the death sound of the character must be reproduced.
  param: Receives an integer (options) that reports the occurrence of a character action.
  return: No return.
*/
void SoundComponent::Die(int options) {
    Play("Die", options);
}

/*
  Function Objective: Informs the method responsible for reproducing the effects that the damage sound of the character must be reproduced.
  param: Receives an integer (options) that reports the occurrence of a character action.
  return: No return.
*/
void SoundComponent::Damage(int options) {
    Play("Damage", options);
}

/*
  Function Objective: It informs the method responsible for reproducing the effects that the sound of the flying character must be reproduced.
  param: Receives an integer (options) that reports the occurrence of a character action.
  return: No return.
*/
void SoundComponent::Flying(int options) {
    Play("Flying", options);
}

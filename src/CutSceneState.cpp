#include "CutSceneState.h"
#include "Sprite.h"
#include "Vec2.h"

CutSceneState::CutSceneState(int scene){
    this->scene = scene;

    switch(scene){
        case(1):
        bg.open("background.png");
    }
}

CutSceneState::~CutSceneState(){
    delete bg;
}

CutSceneState::AddWindow(Window *ptr){

}

CutSceneState::Update(float dt){
bg.Update(dt);
}

CutSceneState::Render(){
    bg.Render(Vec2(0,0));
    switch(scene){
        case(1):


    }
}


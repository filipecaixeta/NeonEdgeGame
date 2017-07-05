#ifndef CUTSCENESTATE_H
#define CUTSCENESTATE_H

#include "Sprite.h"
#include "Window.h"

class CutSceneState : public State{
public:
    CutSceneState(int scene,Sprite* lista);
    ~CutSceneState();
    void AddWindow(Window* ptr);
    void RemoveWindow(Window* ptr);
    void LoadAssets();
    void Update(float dt);
    void Render();



private:
    Sprite bg;
    void HandleInput();
    int scene;
    Window janela;

};

#endif // CUTSCENESTATE_H


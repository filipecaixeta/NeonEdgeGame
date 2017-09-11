#ifndef INGAMEPAUSE_H
#define INGAMEPAUSE_H
#include "menu/MenuState.h"
#include "StageState.h"

class InGamePause : public MenuState
{
public:
    InGamePause(StageState *stageState_);
    void LoadAssets();
    void Update();
    void Render();
    StageState *stageState;
};

#endif // INGAMEPAUSE_H

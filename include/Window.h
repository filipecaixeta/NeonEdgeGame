#ifndef WINDOW_H_
#define WINDOW_H_

#include "Rect.h"

/*
*	Classe da qual toda janela dentro do jogo deverão herdar
*	as características.
*/
class Window{
public:
	virtual ~Window() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(int cameraX = 0, int cameraY = 0) = 0;

	Rect box;
};

#endif
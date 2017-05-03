#ifndef WINDOW_H_
#define WINDOW_H_

#include "Rect.h"
#include "Sprite.h"

#define WINDOWPIECE 32

/*
*	Classe da qual toda janela dentro do jogo deverão herdar
*	as características.
*/
class Window{
public:
	virtual ~Window() = 0;
	virtual void Update(float dt) = 0;
	void Render(int cameraX = 0, int cameraY = 0);

	Rect box;
	Sprite sp;
private:
	void RenderPiece(int posx, int posy, int x, int y, int w, int h);
};

#endif
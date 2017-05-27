#ifndef WINDOW_H_
#define WINDOW_H_

#include "Rect.h"
#include "Sprite.h"

/*
*	A constante WINDOWPIECE define o tamanho de cada pedaço
*	a ser renderizado da janela. Nota-se que por enquanto, o
*	codigo de render das janelas requer que seja 32x32, mas é
*	possível mudar.
*/

#define WINDOWPIECE 32

/*
*	Classe da qual toda janela dentro do jogo deverão herdar
*	as características.
*/
class Window{
public:
	virtual ~Window() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(int cameraX = 0, int cameraY = 0);
	void RenderPiece(int posx, int posy, int x, int y, int w, int h);
	
	Rect box;
	Sprite sp;
};

#endif
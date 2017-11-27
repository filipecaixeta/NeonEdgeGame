#ifndef DIALOGWINDOW_H_
#define DIALOGWINDOW_H_

#include <string>
#include <vector>

#include "Window.h"
#include "Sprite.h"
#include "Text.h"

#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f
#define INT_SIZE_MAX 2147483647
#define INT_SIZE_MIN -2147483648

class DialogWindow: public Window {
public:
	DialogWindow(int positionX, int positionY, std::string text, std::string charName, std::string spritePortrait);
	void Update(float deltaTime);
	void Render(int cameraX = 0, int cameraY = 0);

private:
    std::vector<SDL_Texture*> textArray;
    SDL_Texture* nameTexture;
    Sprite* characterName;
    std::vector<Sprite*> dialog;
    SDL_Color fontColor = {255, 255, 255, 255};
    int fontSize = 40;
    std::string fontName;
    Sprite* face;

};

#endif

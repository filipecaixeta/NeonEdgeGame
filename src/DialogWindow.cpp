#include "DialogWindow.h"
#include "Game.h"
#include <iostream>
#include <assert.h>

DialogWindow::DialogWindow(int positionX, int positionY, std::string text,std::string charName, std::string spritePortrait) {
    fontName = "Sabo-Filled.ttf";
    sp = Sprite("window.png");
    if (!spritePortrait.empty()) {
        face = new Sprite(spritePortrait.c_str(), 8, 80, false, false);
		} else {
		    face = nullptr;
		}

    assert(positionX >= INT_SIZE_MIN && positionX <= INT_SIZE_MAX);
    assert(positionY >= INT_SIZE_MIN && positionY <= INT_SIZE_MAX);
    box.x = positionX;
    box.y = positionY;
    box.w = face->GetWidth() + sp.GetWidth();
    box.h = face->GetHeight();

    assert(fontSize >= INT_SIZE_MIN && fontSize <= INT_SIZE_MAX);
    textArray.emplace_back(Text::GetText(fontName, fontSize, fontColor, text, sp.GetWidth() - 30));
    dialog.emplace_back(new Sprite(textArray.at(0), 1, 0, true));
    nameTexture = Text::GetText(fontName, fontSize, fontColor, charName, sp.GetWidth());
    characterName = new Sprite(nameTexture, 1, 0, true);
}

void DialogWindow::Update(float deltaTime) {
    assert(deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE);
    face->Update(deltaTime);
}

void DialogWindow::Render(int cameraPositionX, int cameraPositionY) {
    if (face != nullptr) {
        face->Render(box.x, box.y);
		}

    sp.Render(box.x + face->GetWidth(), box.y + 23);

    for (unsigned int i = 0; i < dialog.size(); i++) {
        dialog.at(i)->Render(362, 567);
		}

    if (face != nullptr) {
        characterName->Render(357, 542);
		}
}

// Copyright (c) 2017 Neon Edge Game.

#include "GraphicsComponent.h"
#include "Rect.h"
#include "StageState.h"
#include "Character.h"
#include "Logger.h"

GraphicsComponent::GraphicsComponent(std::string baseNameParam): sprite(new Sprite()),
                                                                 baseName(baseNameParam) {
}

GraphicsComponent::~GraphicsComponent() {
    sprite = nullptr;
    for (auto &i : sprites) {
        delete i.second;
    }
    sprites.clear();

    surface = nullptr;
    for (auto &i : surfaces) {
        delete i.second;
    }
    surfaces.clear();
}

void GraphicsComponent::Render(Vec2 position, float angle) {
    if (angle >= FLOAT_MIN_SIZE && angle <= FLOAT_MAX_SIZE){
        sprite->Render(position, angle);
    } else {
        Log::instance.error("Tested value is higher or lower than allowed!");
    }
}

Vec2 GraphicsComponent::GetSize() {
    return sprite->GetSize();
}

SDL_Surface *GraphicsComponent::GetSurface() {
    return surface;
}

SDL_Rect GraphicsComponent::GetClip() {
    return sprite->GetClip();
}

bool GraphicsComponent::GetCharacterLeftDirection() {
    return characterLeftDirection;
}

void GraphicsComponent::UpdateSprite(GameObject *gameObject, std::string spriteParam) {
    if (sprite != sprites[spriteParam]) {
        int w = sprite->GetWidth();
        int h = sprite->GetHeight();
        sprite = sprites[spriteParam];
        surface = surfaces[spriteParam];
        if (gameObject->footing == GameObject::LEFT_WALLED) {
            gameObject->box.x += 0;
        } else if (gameObject->footing == GameObject::RIGHT_WALLED) {
            gameObject->box.x += w - sprite->GetWidth();
        } else {
            gameObject->box.x += (w - sprite->GetWidth()) / 2;
        }

        gameObject->box.y += h - sprite->GetHeight();
        gameObject->box.SetWH(GetSize());
        if (!sprite->Loops()) {
            sprite->SetFrame(1);
        } else {
            // It does nothing.
        }

        if (gameObject->IsCharacter()) {
            Character *character = (Character *) gameObject;
            character->physicsComponent.TileFix(character, StageState::GetCurrentRoom()->GetMap(),
                                                GameObject::LEFT);
            character->physicsComponent.TileFix(character, StageState::GetCurrentRoom()->GetMap(),
                                                GameObject::RIGHT);
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
}

void GraphicsComponent::AddSprite(std::string baseName, std::string name, int frameCount,
                                  int frameTime, bool loops) {
    surfaces.emplace(name, Resources::GetSurface(baseName + name + ".png"));
    if ((frameCount >= INT_MIN_SIZE && frameCount <= INT_MAX_SIZE) &&
        (frameTime >= INT_MIN_SIZE && frameTime <= INT_MAX_SIZE)) {
        sprites.emplace(name, new Sprite(baseName + name + ".png", frameCount, frameTime, true, loops));
    } else {
        Log::instance.error("Tested value of frameCount or frameTime is higher or lower than allowed!");
    }

}

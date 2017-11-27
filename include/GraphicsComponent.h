// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_GRAPHICSCOMPONENT_H_
#define INCLUDE_GRAPHICSCOMPONENT_H_

#include <string>
#include <vector>

#include "Vec2.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Character.h"

#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f

class Character;

class GraphicsComponent {
 public:
    GraphicsComponent(std::string baseNameParam);
    virtual ~GraphicsComponent();
    virtual void Update(GameObject *gameObject, float deltaTime) = 0;
    virtual void UpdateSprite(GameObject *gameObject, std::string sprite);
    virtual void Render(Vec2 position, float angle = 0);
    virtual Vec2 GetSize();
    virtual SDL_Surface*GetSurface();
    virtual SDL_Rect GetClip();
    virtual bool GetCharacterLeftDirection();
    virtual void AddSprite(std::string baseName, std::string name, int frameCount, int frameTime,
                           bool loops = false);

 protected:
    std::unordered_map<std::string, Sprite *> sprites;
    std::unordered_map<std::string, SDL_Surface *> surfaces;
    Sprite *sprite;
    SDL_Surface *surface;
    bool characterLeftDirection;
    std::string baseName;
};

#endif  // INCLUDE_GRAPHICSCOMPONENT_H_

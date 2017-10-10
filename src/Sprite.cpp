/**
 * Copyright 2017 Neon Edge Game
 * File Name: Sprite.cpp
 * Header File Name: Sprite.h
 * Class Name: Sprite
 * Objective: manages the sprites.
 */

#include <math.h>
#include <cstdio>
#include <cstdlib>

#include "Sprite.h"
#include "Game.h"
#ifndef clamp
    #define clamp(N, L, U) N=std::max((float)L, std::min(N, (float)U))
#endif

/**
 * Objective: Constructor of the Sprite.
 * @param none.
 * @return: Return a instance of Sprite.

*/
Sprite::Sprite():
    destroyTexture(false) {
    texture = nullptr;
}

/**
 * Objective: Constructor of the Sprite.

 * @param string file.
 * @param int frameCount.
 * @param float frameTime.
 * @param bool enableAlpha.
 * @param bool loops.
 * @return: Return a instance of Sprite.
*/
Sprite::Sprite(std::string file, int frameCount, float frameTime, bool enableAlpha, bool loops):
    destroyTexture(false) {
    texture = nullptr;
    if (frameCount >= INT_MIN_SIZE && frameCount <= INT_MAX_SIZE) {
        Sprite::frameCount = frameCount;
    }

    if (frameTime >= INT_MIN_SIZE && frameTime <= INT_MAX_SIZE) {
        Sprite::frameTime = frameTime;
    }

    Sprite::loops = loops;
    Open(file, enableAlpha);
}

/**
 * Objective: Constructor of the Sprite.
 *
 * @param SDL_Texture* tex.
 * @param int frameCount.
 * @param float frameTime.
 * @param bool enableAlpha.
 * @param bool loops.
 * @return: Return a instance of Sprite.

*/
Sprite::Sprite(SDL_Texture *tex, int frameCount, float frameTime, bool enableAlpha, bool loops):
    destroyTexture(true) {
    texture = tex;
    if (frameCount >= INT_MIN_SIZE && frameCount <= INT_MAX_SIZE) {
        Sprite::frameCount = frameCount;
    }

    if (frameTime >= INT_MIN_SIZE && frameTime <= INT_MAX_SIZE) {
        Sprite::frameTime = frameTime;
    }

    Sprite::loops = loops;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
    if (enableAlpha) {
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }
}

/**
 * Objective: Destroct the class Sprite, delocalizing some memory used in the class and shutdown dependent libraries.
 *
 * @param none.
 * @return: void.

*/
Sprite::~Sprite() {
    if (destroyTexture) { // destroyTexture is boolean
        SDL_DestroyTexture(texture);
    }
    texture = nullptr;
}

/**
 * Objective: load sprite from file.
 *
 * @param: string file.
 * @param: bool enableAlpha.
 * @return: void.

 */
void Sprite::Open(std::string file, bool enableAlpha) {
    texture = Resources::GetImage(file, enableAlpha);
    if (!IsOpen()) { // Check if image loading sucessful
        printf("IMG_LoadTexture failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
    if (enableAlpha) {
        SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
    }
}

/*
 * Objective: update sprite frames.
 *
 * @param: float dt.
 * @return: void.

 */
void Sprite::Update(float dt) {
    if (dt >= FLOAT_MIN_SIZE && dt <= FLOAT_MAX_SIZE) {
        timeElapsed += dt;
        if (timeElapsed > frameTime && frameTime > 0) {
            if (currentFrame < frameCount) {
                currentFrame++;
            } else if (!loops) {
                currentFrame = 1;
            }
            SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
            timeElapsed = 0;
        }

    }

}

/*
 * Objective: render sprite texture.
 *
 * @param: int x.
 * @param: int y.
 * @param: float angle.
 * @return: void.
 */
void Sprite::Render(int x, int y, float angle) {
    if ((x >= INT_MIN_SIZE && y <= INT_MAX_SIZE) && (y >= INT_MIN_SIZE && y <= INT_MAX_SIZE)) {
        dstRect.w = clipRect.w*scaleX;
        dstRect.h = clipRect.h*scaleY;
        dstRect.x = x - ((dstRect.w-clipRect.w)/2);
        dstRect.y = y - ((dstRect.h-clipRect.h)/2);
    }
    if ((texture!=nullptr) && (angle >= FLOAT_MIN_SIZE && angle <= FLOAT_MAX_SIZE)) {
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture,
                            &clipRect, &dstRect, angle, nullptr, flipHorizontal);
    }
}

/*
 * Objective: render sprite screen position.
 *
 * @param: Vec2 pos.
 * @param: float angle:
 * @return: void.

 */
void Sprite::Render(Vec2 pos, float angle) {
    if (angle >= FLOAT_MIN_SIZE && angle <= FLOAT_MAX_SIZE) {
        Render(pos.x, pos.y, angle);
    }
}

/*
 * Objective: set clip position in sprite.
 *
 * @param: int x.
 * @param: int y.
 * @param: int w.
 * @param: int h.
 * @return: void.

 */
void Sprite::SetClip(int x, int y, int w, int h) {
    if ((x >= INT_MIN_SIZE && x <= INT_MAX_SIZE) && (y >= INT_MIN_SIZE && y <= INT_MAX_SIZE)) {
        clipRect.x = x;
        clipRect.y = y;
    }
    if ((w >= INT_MIN_SIZE && w <= INT_MAX_SIZE) && (h >= INT_MIN_SIZE && h <= INT_MAX_SIZE)) {
        clipRect.w = w;
        clipRect.h = h;
    }
}

/*
 * Objective: get clip from sprite.
 *
 * @param: none.
 * @return: SDL_Rect clipRect.
 */
SDL_Rect Sprite::GetClip() {
    return clipRect;
}

/*
 * Objective: set scale in sprite.
 *
 * @param: float scale.
 * @return: void.

 */
void Sprite::SetScaleX(float scale) {
    if (scale >= FLOAT_MIN_SIZE && scale <= FLOAT_MAX_SIZE) {
        scaleX = scale;
    }
}

/*
 * Objective: set scale y in sprite
 *
 * @param: float scale.
 * @return: void.
 */
void Sprite::SetScaleY(float scale) {
    if (scale >= FLOAT_MIN_SIZE && scale <= FLOAT_MAX_SIZE) {
        scaleY = scale;
    }
}

/*
 * Objective: set transparency in sprite.
 *
 * @param: float a.
 * @return: void.
 */
void Sprite::SetTransparency(float a) {
    //a = (0.0, 1.0)
    if(a >= FLOAT_MIN_SIZE && a <= FLOAT_MAX_SIZE) {
        clamp(a, 0.0f, 1.0f);
        SDL_SetTextureAlphaMod(texture, (unsigned short int)(255*a));
    }
}

/**
 * Objective: set frame in sprite.
 *
 * @param: int frame.
 * @return: void.
 */
void Sprite::SetFrame(int frame) {
    if (frame >= INT_MIN_SIZE && frame <= INT_MAX_SIZE) {
        currentFrame = frame;
        SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
    }
}

/*
 * Objective: set frame normalized in sprite.
 *
 * @param: float f.
 * @return: void.
 */
void Sprite::SetFrameNormalized(float f) {
    //f = (0.0, 1.0)
    if (f >= FLOAT_MIN_SIZE && f <= FLOAT_MAX_SIZE) {
        SetFrame(round(f*(frameCount-1)+1));
    }
}

/*
 * Objective: set frame count in sprite.
 *
 * @param: int frameCount.
 * @return: void.
 */
void Sprite::SetFrameCount(int frameCount) {
    if (frameCount >= INT_MIN_SIZE && frameCount <= INT_MAX_SIZE) {
        Sprite::frameCount = frameCount;
    }
}

/*
 * Objective: set frame time in sprite.
 *
 * @param: float frameTime.
 * @return: void.
 */
void Sprite::SetFrameTime(float frameTime) {
    if (frameTime >= FLOAT_MIN_SIZE && frameTime <= FLOAT_MAX_SIZE) {
        Sprite::frameTime = frameTime;
    }
}

/*
 * Objective: set bleeding texture.
 * @param: bool b.
 * @return: void.
 */
void Sprite::SetBlending(bool b) {
    SDL_SetTextureBlendMode(texture, b ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
}

/*
 * Objective: set texture with current frame.
 *
 * @param: SDL_Texture* tex.
 * @param: bool destroyTexture_.
 * @return: void.
 */
void Sprite::SetTexture(SDL_Texture* tex, bool destroyTexture_) {
    if (destroyTexture) {
        SDL_DestroyTexture(texture);
    }
    destroyTexture = destroyTexture_;
    texture = tex;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
}

/*
 * Objective: flip sprite.
 *
 * @param: bool m.
 * @return: void.
 */
void Sprite::Mirror(bool m) {
    flipHorizontal = m ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

/*
 * Objective: get width redimensioned.
 *
 * @param: none.
 * @return: int width.
 */
int Sprite::GetWidth() {
    return width/frameCount*((scaleX-1)*0.5+1);
}

/*
 * Objective: get height redimensioned.
 * @param: none.
 * @return: int height.
 */
int Sprite::GetHeight() {
    return height*((scaleY-1)*0.5+1);
}

/*
 * Objective: get size, width and height.
 * @param: none.
 * @return: Vec2.
 */
Vec2 Sprite::GetSize() {
    return Vec2(GetWidth(), GetHeight());
}

/*
 * Objective: get frame count.
 * @param: none.
 * @return: int frameCount.
 */
int Sprite::GetFrameCount() {
    return frameCount;
}
/*
 * Objective: check loop with boolean.
 *
 * @param: none.
 * @return: bool !loops.
 */
bool Sprite::Loops() {
    return !loops;
}

/*
 * Objective: flip horizontal sprite.
 *
 * @param: none.
 * @return: bool flipHorizontal.
 */
bool Sprite::GetMirror() {
    return flipHorizontal==SDL_FLIP_HORIZONTAL;
}

/*
 * Objective: check if texture is open.
 * @param: none.
 * @return: bool.
 */
bool Sprite::IsOpen() {
    return (!texture) ? false : true;
}

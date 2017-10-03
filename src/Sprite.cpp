/*
    Copyright 2017 Neon Edge Game
    File Name: Sprite.cpp
    Header File Name: Sprite.h
    Class Name: Sprite
    Objective: manages the sprites.
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
    Objective: Constructor of the Sprite.
    @param None.
    @return: Return a instance of Sprite.

*/
Sprite::Sprite():
    destroyTexture(false) {
    texture = nullptr;
}

/**
    Objective: Constructor of the Sprite.
    @param string file.
    @param int frameCount.
    @param float frameTime.
    @param bool enableAlpha.
    @param bool loops.
    @return: Return a instance of Sprite.

*/
Sprite::Sprite(std::string file, int frameCount, float frameTime, bool enableAlpha, bool loops):
    destroyTexture(false) {
    texture = nullptr;
    Sprite::frameCount = frameCount;
    Sprite::frameTime = frameTime;
    Sprite::loops = loops;
    OpenFile(file, enableAlpha);
}

/**
    Objective: Constructor of the Sprite.
    @param SDL_Texture* tex.
    @param int frameCount.
    @param float frameTime.
    @param bool enableAlpha.
    @param bool loops.
    @return: Return a instance of Sprite.

*/
Sprite::Sprite(SDL_Texture *tex, int frameCount, float frameTime, bool enableAlpha, bool loops):
    destroyTexture(true) {
    texture = tex;
    Sprite::frameCount = frameCount;
    Sprite::frameTime = frameTime;
    Sprite::loops = loops;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClipPosition((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
    if (enableAlpha) {
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }
}

/**
    Objective: Destroct the class Sprite, delocalizing some memory used in the class and shutdown dependent libraries.
    @param None.
    @return: void.
    
*/
Sprite::~Sprite() {
    if (destroyTexture) { // destroyTexture is boolean
        SDL_DestroyTexture(texture);
    }
    texture = nullptr;
}

/*
    Objective: load sprite from file.
    @param: string file.
    @param: bool enableAlpha.
    @return: void.

 */
void Sprite::OpenFile(std::string file, bool enableAlpha) {
    texture = Resources::GetImage(file, enableAlpha);
    if (IsOpen()) { // Check if image loading sucessful
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        SetClipPosition((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
        if (enableAlpha) {
            SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
        }
    }
    else {
        printf("IMG_LoadTexture failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/*
    Objective: update sprite frames.
    @param: float delayTime.
    @return: void.

 */
void Sprite::Update(float delayTime) {
    timeElapsed += delayTime;
    if (timeElapsed > frameTime && frameTime > 0) {
        if (currentFrame < frameCount) {
            currentFrame++;
        } else if (!loops) {
            currentFrame = 1;
        }
        SetClipPosition((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
        timeElapsed = 0;
    }
}

/*
    Objective: render sprite texture.
    @param: int x.
    @param: int y.
    @param: float angle.
  @return: void.

 */
void Sprite::RenderTexture(int x, int y, float angle) {
    dstRect.w = clipRect.w*scaleX;
    dstRect.h = clipRect.h*scaleY;
    dstRect.x = x - ((dstRect.w-clipRect.w)/2);
    dstRect.y = y - ((dstRect.h-clipRect.h)/2);
    if (texture!=nullptr) {
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture,
                            &clipRect, &dstRect, angle, nullptr, flipHorizontal);
    }
}

/*
    Objective: render sprite screen position.
    @param: Vec2 pos.
    @param: float angle:
    @return: void.

 */
void Sprite::RenderScreenPosition(Vec2 pos, float angle) {
    RenderTexture(pos.x, pos.y, angle);
}

/*
    Objective: set clip position in sprite.
    @param: int x.
    @param: int y.
    @param: int w.
    @param: int h.
    @return: void.

 */
void Sprite::SetClipPosition(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

/*
    Objective: get clip from sprite.
    @param: none.
    @return: SDL_Rect clipRect.

 */
SDL_Rect Sprite::GetClip() {
    return clipRect;
}

/*
    Objective: set scale in sprite.
    @param: float scale.
    @return: void.

 */
void Sprite::SetScaleX(float scale) {
    scaleX = scale;
}

/*
    Objective: set scale y in sprite
    @param: float scale.
    @return: void.

 */
void Sprite::SetScaleY(float scale) {
    scaleY = scale;
}

/*
    Objective: set transparency in sprite.
    @param: float a.
    @return: void.

 */
void Sprite::SetTransparency(float a) {
    //a = (0.0, 1.0)
    clamp(a, 0.0f, 1.0f);
    SDL_SetTextureAlphaMod(texture, (unsigned short int)(255*a));
}

/*
    Objective: set frame in sprite.
    @param: int frame.
    @return: void.

 */
void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    SetClipPosition((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
}

/*
    Objective: set frame normalized in sprite.
    @param: float f.
    @return: void.

 */
void Sprite::SetFrameNormalized(float f) {
    //f = (0.0, 1.0)
    SetFrame(round(f*(frameCount-1)+1));
}

/*
    Objective: set frame count in sprite.
    @param: int frameCount.
    @return: void.

 */
void Sprite::SetFrameCount(int frameCount) {
    Sprite::frameCount = frameCount;
}

/*
    Objective: set frame time in sprite.
    @param: float frameTime.
    @return: void.

 */
void Sprite::SetFrameTime(float frameTime) {
    Sprite::frameTime = frameTime;
}

/*
    Objective: set bleeding texture.
    @param: bool b.
    @return: void.

 */
void Sprite::SetBlending(bool b) {
    SDL_SetTextureBlendMode(texture, b ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
}

/*
    Objective: set texture with current frame.
    @param: SDL_Texture* tex.
    @param: bool destroyTexture_.
    @return: void.

 */
void Sprite::SetTexture(SDL_Texture* tex, bool destroyTexture_) {
    if (destroyTexture) {
        SDL_DestroyTexture(texture);
    }
    destroyTexture = destroyTexture_;
    texture = tex;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClipPosition((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
}

/*
    Objective: flip sprite.
    @param: bool m.
    @return: void.

 */
void Sprite::Mirror(bool m) {
    flipHorizontal = m ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

/*
    Objective: get width redimensioned.
    @param: none.
    @return: int width.

 */
int Sprite::GetWidth() {
    return width/frameCount*((scaleX-1)*0.5+1);
}

/*
    Objective: get height redimensioned.
    @param: none.
    @return: int height.

 */
int Sprite::GetHeight() {
    return height*((scaleY-1)*0.5+1);
}

/*
    Objective: get size, width and height.
    @param: none.
    @return: Vec2.

 */
Vec2 Sprite::GetSize() {
    return Vec2(GetWidth(), GetHeight());
}

/*
    Objective: get frame count.
    @param: none.
    @return: int frameCount.

 */
int Sprite::GetFrameCount() {
    return frameCount;
}
/*
    Objective: check loop with boolean.
    @param: none.
    @return: bool !loops.

 */
bool Sprite::Loops() {
    return !loops;
}

/*
    Objective: flip horizontal sprite.
    @param: none.
    @return: bool flipHorizontal.

 */
bool Sprite::GetMirror() {
    return flipHorizontal==SDL_FLIP_HORIZONTAL;
}

/*
    Objective: check if texture is open.
    @param: none.
    @return: bool.

 */
bool Sprite::IsOpen() {
    return (!texture) ? false : true;
}

#include <math.h>
#include <cstdio>
#include <cstdlib>

#include "Sprite.h"
#include "Game.h"
#ifndef clamp
	#define clamp(N,L,U) N=std::max((float)L,std::min(N,(float)U))
#endif

Sprite::Sprite():
	destroyTexture(false)
{
	texture = nullptr;
}

Sprite::Sprite(std::string file, int frameCount, float frameTime, bool enableAlpha, bool loops):
	destroyTexture(false)
{
	texture = nullptr;
	Sprite::frameCount = frameCount;
	Sprite::frameTime = frameTime;
	Sprite::loops = loops;
	Open(file,enableAlpha);
}

Sprite::Sprite(SDL_Texture *tex, int frameCount, float frameTime, bool enableAlpha, bool loops):
	destroyTexture(true)
{
	texture = tex;
	Sprite::frameCount = frameCount;
	Sprite::frameTime = frameTime;
	Sprite::loops = loops;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
	if(enableAlpha)
		SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
}

Sprite::~Sprite() {
	if (destroyTexture)
		SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Sprite::Open(std::string file, bool enableAlpha)
{
	texture = Resources::GetImage(file,enableAlpha);
	if(!IsOpen())
	{
		printf("IMG_LoadTexture failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
	if(enableAlpha)
		SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
}

void Sprite::Update(float dt)
{
	timeElapsed += dt;
	if(timeElapsed > frameTime && frameTime > 0)
	{
		if(currentFrame < frameCount)
			currentFrame++;
		else if(!loops)
			currentFrame = 1;
		SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
		timeElapsed = 0;
	}
}

void Sprite::Render(int x, int y, float angle)
{
	dstRect.w = clipRect.w*scaleX;
	dstRect.h = clipRect.h*scaleY;
	dstRect.x = x - ((dstRect.w-clipRect.w)/2);
	dstRect.y = y - ((dstRect.h-clipRect.h)/2);
	if (texture!=nullptr)
		SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, angle, nullptr, flipHorizontal);
}

void Sprite::Render(Vec2 pos, float angle)
{
	Render(pos.x,pos.y,angle);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

SDL_Rect Sprite::GetClip()
{
	return clipRect;
}

void Sprite::SetScaleX(float scale)
{
	scaleX = scale;
}

void Sprite::SetScaleY(float scale)
{
	scaleY = scale;
}

void Sprite::SetTransparency(float a)
{
	//a = (0.0,1.0)
	clamp(a,0.0f,1.0f);
	SDL_SetTextureAlphaMod(texture,(unsigned short int)(255*a));
}

void Sprite::SetFrame(int frame)
{
	currentFrame = frame;
	SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
}

void Sprite::SetFrameNormalized(float f)
{
	//f = (0.0,1.0)
	SetFrame(round(f*(frameCount-1)+1));
}

void Sprite::SetFrameCount(int frameCount)
{
	Sprite::frameCount = frameCount;
}

void Sprite::SetFrameTime(float frameTime)
{
	Sprite::frameTime = frameTime;
}

void Sprite::SetBlending(bool b)
{
	SDL_SetTextureBlendMode(texture, b ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
}

void Sprite::SetTexture(SDL_Texture* tex, bool destroyTexture_)
{
	if (destroyTexture)
		SDL_DestroyTexture(texture);
	destroyTexture = destroyTexture_;
	texture = tex;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
}

void Sprite::Mirror(bool m)
{
	flipHorizontal = m ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

int Sprite::GetWidth()
{
	return width/frameCount*((scaleX-1)*0.5+1);
}

int Sprite::GetHeight()
{
	return height*((scaleY-1)*0.5+1);
}

Vec2 Sprite::GetSize()
{
	return Vec2(GetWidth(), GetHeight());
}

int Sprite::GetFrameCount()
{
	return frameCount;
}

bool Sprite::GetMirror()
{
	return flipHorizontal==SDL_FLIP_HORIZONTAL;
}

bool Sprite::IsOpen()
{
	return (!texture) ? false : true;
}

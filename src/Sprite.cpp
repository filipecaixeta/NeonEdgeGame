#include "Sprite.h"
#include "Game.h"
#include <math.h>
#define clamp(N,L,U) N=std::max((float)L,std::min(N,(float)U))

Sprite::Sprite() {
	file = "";
	texture = nullptr;
}

Sprite::Sprite(std::string file, int frameCount, float frameTime, bool enableAlpha){
    Sprite::file = file;
	texture = nullptr;
	Sprite::frameCount = frameCount;
	Sprite::frameTime = frameTime;
    Open(file,enableAlpha);
}

Sprite::~Sprite() {
	texture = nullptr;
}

void Sprite::Open(std::string file, bool enableAlpha) {
    texture = Resources::GetImage(file,enableAlpha);
	if(!IsOpen()) {
		printf("IMG_LoadTexture failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
    if (enableAlpha)
        SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);

}

void Sprite::Update(float dt) {
	timeElapsed += dt;
	if(timeElapsed > frameTime && frameTime > 0) {
		if(currentFrame < frameCount)
			currentFrame++;
		else
			currentFrame = 1;
		SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
		timeElapsed = 0;
	}
}

void Sprite::Render(int x, int y, float angle) {
	dstRect.w = clipRect.w*scaleX;
	dstRect.h = clipRect.h*scaleY;
	dstRect.x = x - ((dstRect.w-clipRect.w)/2);
	dstRect.y = y - ((dstRect.h-clipRect.h)/2);
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, angle, nullptr, flipHorizontal);
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::SetScaleX(float scale) {
	scaleX = scale;
}

void Sprite::SetScaleY(float scale) {
	scaleY = scale;
}

void Sprite::SetFrame(int frame) {
	currentFrame = frame;
    SetClip((width/frameCount)*(currentFrame-1), 0, width/frameCount, height);
}

void Sprite::SetFrameNormalized(float f)
{
    // f = (0.0,1.0)
    SetFrame(round(f*(frameCount-1)+1));
}

void Sprite::SetFrameCount(int frameCount) {
	Sprite::frameCount = frameCount;
}

void Sprite::SetFrameTime(float frameTime) {
	Sprite::frameTime = frameTime;
}

void Sprite::SetFile(std::string file, int frameCount, float frameTime) {
	lastWidth = width;
	lastHeight = height;
	Sprite::file = file;
	texture = nullptr;
	Sprite::frameCount = frameCount;
	Sprite::frameTime = frameTime;
	Open(file);
}

std::string Sprite::GetFile() {
	return file;
}

int Sprite::GetWidth() {
	return width/frameCount*scaleX;
}

int Sprite::GetHeight() {
	return height*scaleY;
}

int Sprite::GetLastWidth() {
	return lastWidth/frameCount*scaleX;
}

int Sprite::GetLastHeight() {
    return lastHeight*scaleY;
}

int Sprite::GetFrameCount()
{
    return frameCount;
}

void Sprite::SetAlpha(float a)
{
    // a = (0.0,1.0)
    clamp(a,0.0f,1.0f);
    SDL_SetTextureAlphaMod(texture,(unsigned short int)(255*a));
}

void Sprite::Mirror(bool m)
{
    flipHorizontal = m?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE;
}

bool Sprite::IsOpen() {
	return (!texture) ? false : true;
}

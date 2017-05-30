#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>

#include "Resources.h"
#include "Vec2.h"

class Sprite {
private:
	SDL_Texture* texture;
	SDL_Rect clipRect;
	SDL_Rect dstRect;
	float scaleX = 1;
	float scaleY = 1;
	int frameCount = 1;
	float frameTime = 0;
	bool loops = true;
	int currentFrame = 1;
	float timeElapsed = 0;
	int width = 0;
	int height = 0;
	int destroyTexture;
	SDL_RendererFlip flipHorizontal = SDL_FLIP_NONE;

public:
	Sprite();
	Sprite(std::string file, int frameCount = 1, float frameTime = 0, bool enableAlpha = false, bool loops = true);
	Sprite(SDL_Texture *tex, int frameCount = 1, float frameTime = 0, bool enableAlpha = false, bool loops = true);
	~Sprite();
	void Open(std::string file, bool enableAlpha=false);
	void Update(float dt);
	void Render(int x, int y, float angle = 0);
	void Render(Vec2 pos, float angle = 0);
	void SetClip(int x, int y, int w, int h);
	SDL_Rect getClip();
	void SetScaleX(float scale);
	void SetScaleY(float scale);
	void SetTransparency(float a);
	void SetFrame(int frame);
	void SetFrameNormalized(float f);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	void SetBlending(bool b);
	void SetTexture(SDL_Texture *tex, bool destroyTexture_=true);
	void Mirror(bool m);
	int GetWidth();
	int GetHeight();
	Vec2 GetSize();
	int GetFrameCount();
	bool GetMirror();
	bool IsOpen();
};

#endif /* SPRITE_H_ */

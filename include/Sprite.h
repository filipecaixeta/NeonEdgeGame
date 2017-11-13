#ifndef SPRITE_H_
#define SPRITE_H_
#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f
#define INT_MIN_SIZE -32768
#define INT_MAX_SIZE 32767
#define INT_MAX_SIZE 32767


#include <string>

#include "Resources.h"
#include "Vec2.h"

class Sprite {
private:
	SDL_Texture* texture = NULL;
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
	int destroyTexture = 0;
	SDL_RendererFlip flipHorizontal = SDL_FLIP_NONE;
	int GetFrameCount();
	bool GetMirror();
	void SetFrameCount(int frameCount = 0);
	void SetFrameTime(float frameTime = 0);


public:
	Sprite();
	Sprite(std::string file, int frameCount = 1, float frameTime = 0, bool enableAlpha = false, bool loops = true);
	Sprite(SDL_Texture *tex, int frameCount = 1, float frameTime = 0, bool enableAlpha = false, bool loops = true);
	~Sprite();
	void OpenFile(std::string file, bool enableAlpha=false);
	void Update(float dt = 0);
	void RenderTexture(int x, int y, float angle = 0);
	void RenderScreenPosition(Vec2 pos, float angle = 0);
	int GetWidth();
	int GetHeight();
	Vec2 GetSize();
	void Mirror(bool m = 0);
	void SetTransparency(float a);
	void SetFrame(int frame = 0);
	bool Loops();
	SDL_Rect GetClip();
	void SetClipPosition(int x, int y, int w, int h);
	bool IsOpen();
	void SetScaleX(float scale);
	void SetScaleY(float scale);
	void SetFrameNormalized(float f);
	void SetBlending(bool b = false);
	void SetTexture(SDL_Texture *tex, bool destroyTexture_=true);

};

#endif /* SPRITE_H_ */

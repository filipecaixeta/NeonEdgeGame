#ifndef SPRITE_H_
#define SPRITE_H_

#include "Resources.h"

class Sprite {
private:
	std::string file;
	SDL_Texture* texture;
	SDL_Rect clipRect;
	SDL_Rect dstRect;
	float scaleX = 1;
	float scaleY = 1;
	int frameCount = 1;
	int currentFrame = 1;
	float frameTime = 0;
	float timeElapsed = 0;
	int width = 0;
	int height = 0;
	int lastWidth = 0;
	int lastHeight = 0;

public:
	Sprite();
	Sprite(std::string file, int frameCount = 1, float frameTime = 0);
	~Sprite();
	void Open(std::string file);
	void Update(float dt);
	void Render(int x, int y, float angle = 0);
	void SetClip(int x, int y, int w, int h);
	void SetScaleX(float scale);
	void SetScaleY(float scale);
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	void SetFile(std::string file, int frameCount = 1, float frameTime = 0);
	std::string GetFile();
	int GetWidth();
	int GetHeight();
	int GetLastWidth();
	int GetLastHeight();
	bool IsOpen();
};

#endif /* SPRITE_H_ */

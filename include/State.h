#ifndef STATE_H_
#define STATE_H_

#include "Music.h"
#include "TileMap.h"

class State {
public:
	Sprite bg;
	Music music;
	bool quitRequested;
	State();
	virtual ~State();
	virtual void LoadAssets() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool Is(std::string type) = 0;
	virtual State* get();
	virtual bool QuitRequested();

	Vec2 CenterVertical(Sprite *sp);
	Vec2 CenterVertical(int size);
	Vec2 CenterVertical(Vec2 size);
	Vec2 CenterHorizontal(Sprite* sp);
	Vec2 CenterHorizontal(int size);
	Vec2 CenterHorizontal(Vec2 size);
};

#endif /* STATE_H_ */

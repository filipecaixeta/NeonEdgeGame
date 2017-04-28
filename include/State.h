#ifndef STATE_H_
#define STATE_H_

#include "Music.h"
#include "TileMap.h"

class State {
public:
	Sprite bg = Sprite();
	Music music = Music();
	bool quitRequested = false;

	virtual ~State() = 0;
	virtual void LoadAssets() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool QuitRequested() = 0;
	virtual bool Is(std::string type) = 0;
	virtual State* get() = 0;
};

#endif /* STATE_H_ */

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
};

#endif /* STATE_H_ */

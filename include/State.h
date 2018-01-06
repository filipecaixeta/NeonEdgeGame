#ifndef STATE_H_
#define STATE_H_
#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f
#define INT_MIN_SIZE -32768
#define INT_MAX_SIZE 32767

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

 private:

	
};

#endif /* STATE_H_ */

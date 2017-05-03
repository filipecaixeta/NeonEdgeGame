#ifndef STAGESTATE_H_
#define STAGESTATE_H_

#include "State.h"
#include "Godofredo.h"
#include "Notfredo.h"
#include "Window.h"

class StageState : public State {
private:
	TileSet* tileSet;
	bool paused = false;

	static TileMap* tileMap;
	static std::vector<std::unique_ptr<GameObject>> objectArray;
	static std::vector<std::unique_ptr<Window>> windowArray;

public:
	StageState();
	~StageState();

	static void AddObject(GameObject* ptr);
	static void AddObjectAsFirst(GameObject* ptr);
	static void RemoveObject(GameObject* ptr);
	static bool IsColliding(Rect a, Rect b);
	static TileMap* GetTileMap();
	static void AddWindow(Window* ptr);

	void Pause();
	void Resume();
	void LoadAssets();
	void Update();
	void Render();
	bool QuitRequested();
	bool Is(std::string type);
	StageState* get();
};

#endif /* STAGESTATE_H_ */

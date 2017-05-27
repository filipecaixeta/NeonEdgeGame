#ifndef STAGESTATE_H_
#define STAGESTATE_H_

#include "State.h"
#include "Lancelot.h"
#include "Gallahad.h"
#include "Notfredo.h"
#include "Window.h"
#include <LoadingBar.h>

class StageState : public State
{
private:
	std::string mode;
	TileSet* tileSet;
	bool paused = false;

	static TileMap* tileMap;
	static GameObject* player;
	static std::vector<GameObject*> objectArray;
	static std::vector<std::unique_ptr<Window>> windowArray;
	static std::unordered_map<int, TileMap*> roomTable;
	LoadingBar healthBar;

public:
	StageState(std::string mode);
	~StageState();

	static TileMap* GetTileMap();
	static GameObject* GetPlayer();
	static void AddObject(GameObject* ptr);
	static void AddObjectAsFirst(GameObject* ptr);
	static void RemoveObject(GameObject* ptr);
	static void AddWindow(Window* ptr);
	static void RemoveWindow(Window* ptr);
	static bool IsColliding(Rect a, Rect b);

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

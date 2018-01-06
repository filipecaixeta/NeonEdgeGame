#include "BoxSpawner.h"
#include "StageState.h"
#include <assert.h>

BoxSpawner::BoxSpawner(int positionX, int positionY) {
    name = "BoxSpawner";
		assert(positionX >= INT_SIZE_MIN && positionX <= INT_SIZE_MAX);
		assert(positionY >= INT_SIZE_MIN && positionY <= INT_SIZE_MAX);
    box.SetXY(Vec2(positionX, positionY));
    spawn = nullptr;
}

BoxSpawner::~BoxSpawner() {
}

void BoxSpawner::Update(TileMap* map, float deltaTime) {
    assert(deltaTime >= INT_SIZE_MIN && deltaTime <= INT_SIZE_MAX);
    if (!spawn) {
        spawn = new Box(box.x, box.y);
        StageState::AddObject(BoxSpawner::spawn);
    }

    if (spawn->GetHealth() == 1) {
        spawn->Kill();
        spawn = new Box(box.x, box.y);
        StageState::AddObject(BoxSpawner::spawn);
    }
}

void BoxSpawner::Render() {
}

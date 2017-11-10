#include "PressurePlateOneTime.h"
#include "Camera.h"

#include <assert.h>

PressurePlateOneTime::PressurePlateOneTime(int x, int y, Interactive* d):
	Interactive(x,y,"PressurePlateOneTime")
{
    assert(x >= INTEGER_SIZE_MIN && x <= INTEGER_SIZE_MAX);
    assert(y >= INTEGER_SIZE_MIN && y <= INTEGER_SIZE_MAX);
	name = "PressurePlateOneTime";
    assert(d != NULL);
    door = d;
}

PressurePlateOneTime::~PressurePlateOneTime()
{

}

void PressurePlateOneTime::Trigger() {
	if(Active()) {
		door->On();
	}
}

void PressurePlateOneTime::NotifyObjectCollision(GameObject* other) {
	if(other->IsPlayer()) {
        assert(other != NULL);
		On();
    }
}

void PressurePlateOneTime::Update(TileMap* map, float dt) {
    assert(map != NULL);
    assert(dt >= FLOAT_SIZE_MIN && dt <= FLOAT_SIZE_MAX);
	Interactive::Update(map,dt);
    assert(map != NULL);
	Trigger();
}

#ifndef PIXELPERFECTCOLISION_H
#define PIXELPERFECTCOLISION_H
#include <SDL.h>
#include <SDL_image.h>

#include "Vec2.h"
#include "GameObject.h"
#include "TileMap.h"

namespace ColisionFunctions
{
	inline void GetSurfaceData(SDL_Surface* surface,int& x,int& y,
							   int& rowSize,Uint32** pixels,SDL_PixelFormat** format);

	void ConvertSurfaceColors(SDL_Surface* surface);

	int PixelPerfectColision(SDL_Surface* surface1, SDL_Rect clipRect1, Vec2 pos1, bool mirror1,
					  SDL_Surface* surface2, SDL_Rect clipRect2, Vec2 pos2, bool mirror2);

	int PixelPerfectColision(GameObject* object1,GameObject* object2);

	bool RayCastColision(TileMap* map, Vec2 pos1, Vec2 pos2);
}

#endif // PIXELPERFECTCOLISION_H

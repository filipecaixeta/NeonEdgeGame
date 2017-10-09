/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: ColisionFunctions.cpp
 * Header File Name: ColisionFunctions.h
 * Class Name: ColisionFunctions
 * Objective: the objective of this class is to check a colision between two objects.
 */
#include <cmath>
#include <assert.h>
#include "ColisionFunctions.h"
#ifndef clamp
#define clamp(N, L, U) N = std::max(L, std::min(N, U))
#endif

/**
  * Objective: Update the data about some aspects important to check the colision of two objcts,
  *              as the pixels dispositions and theposition of the object.
  *
  * @param  SDL_Surface surface - a struct of the sdl library that contains a collection of pixels.
  * @param int x - the position of the object in the x axis
  * @param int y - the position of the object in the y axis
  * @param int rowSize - the length of a row of pixels in bytes.
  * @param Uint32 pixels - a pointer to the actual pointer data. 
  * @param SDL_PixelFormat format - A structure of the sdl library that contains pixel format information. 
  * @return x - x param updated
  * @return y - y param updated
  * @return pixel - pixel param updated
  * @return format - format param updated
  * @return rowSize - rowSize param updated
  */
void ColisionFunctions::GetSurfaceData(SDL_Surface *surface, int &x, int &y, int &rowSize,
                                              Uint32 **pixels, SDL_PixelFormat **format) {
	if(surface != NULL & x !=NULL & y!= NULL & rowSize != NULL & pixels != NULL & format != NULL){
		SDL_LockSurface(surface);
		x = surface->w;
		y = surface->h;
		*pixels = (Uint32 *)surface->pixels;
		*format = surface->format;
		rowSize = surface->pitch/sizeof(unsigned int);
		assert(0==1);
	}
	else{
		//Do nothing		
		//TODO: put ERROR log
	}
}

/**
 * Objective: Convert pixels color of a SDL_Surface  
 *
 * @param  SDL_Surface surface - a struct of the sdl library that contains a collection of pixels.
 * @return SDL_Surface surface - change the surface pixels color.  
 */
void ColisionFunctions::ConvertSurfaceColors(SDL_Surface *surface) {
	if(surface!=NULL){
		int x = INITIAL_VALUE;
		int y = INITIAL_VALUE;
		int rowSize = INITIAL_VALUE;
		Uint32* pixels;
		SDL_PixelFormat *format;

		ColisionFunctions::GetSurfaceData(surface, x, y, rowSize, &pixels, &format);

		Uint32 colorW = SDL_MapRGBA(format, FULL_COLOR, NO_COLOR, NO_COLOR, FULL_COLOR);
		Uint32 colorB = SDL_MapRGBA(format, NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR);

		for (int j = 0; j < y; j++) {
			for (int i = 0; i < x; i++) {
				Uint8 red;
				Uint8 green;
				Uint8 blue;
				Uint8 alpha;
				int pixelPosition = j * rowSize + i;
				int const VISIBILITY = 100; // constant the set a alpha to be visible.
				SDL_GetRGBA(pixels[pixelPosition], format, &red, &green, &blue, &alpha);

				if (alpha > VISIBILITY) {
					pixels[pixelPosition] = colorW;
				} else {
					pixels[pixelPosition] = colorB;
				}
			}
		}

		SDL_UnlockSurface(surface);
	}
	else{
		//do nothing
	}
}

/**
 * Objective: Check if two surfaces collided. 
 *
 * @param 
 * @param  SDL_Surface surface - a struct of the sdl library that contains a collection of pixels.
 * @return int colision - 1 if colide, 0 if not. 
 */
int ColisionFunctions::PixelPerfectColision(SDL_Surface *surface1, SDL_Rect clipRect1, Vec2 pos1,
											bool mirror1, SDL_Surface *surface2, SDL_Rect clipRect2,
											Vec2 pos2, bool mirror2) {
	if(surface1 != NULL & surface2 != NULL){
		int colision = INITIAL_VALUE;
		int xSize1 = INITIAL_VALUE;
		int ySize1 = INITIAL_VALUE;
		int rowSize1 = INITIAL_VALUE;
		Uint32* pixels1;
		SDL_PixelFormat *format1;
		ColisionFunctions::GetSurfaceData(surface1, xSize1, ySize1, rowSize1, &pixels1, &format1);

		int xSize2 = INITIAL_VALUE;
		int ySize2 = INITIAL_VALUE;
		int rowSize2 = INITIAL_VALUE;
		Uint32* pixels2;
		SDL_PixelFormat *format2;
		ColisionFunctions::GetSurfaceData(surface2, xSize2, ySize2, rowSize2, &pixels2, &format2);

		int WA = clipRect1.w;
		int X0A = std::round(pos1.x);
		int X1A = X0A + WA;
		int HA = clipRect1.h;
		int Y0A = std::round(pos1.y);
		int Y1A = Y0A + HA;
		int WB = clipRect2.w;
		int X0B = std::round(pos2.x);
		int X1B = X0B + WB;
		int HB = clipRect2.h;
		int Y0B = std::round(pos2.y);
		int Y1B = Y0B + HB;
		int i1Min = 0;
		int i2Min = 0;
		int i1Max = 0;
		int i2Max = 0;
		int j1Min = 0;
		int j2Min = 0;
		int j1Max = 0;
		int j2Max = 0;

		if (X0A < X0B) {
			i1Min = X0B - X0A + clipRect1.x;
			i2Min = clipRect2.x;
		} else {
			i1Min = clipRect1.x;
			i2Min = X0A - X0B + clipRect2.x;
		}

		if (X1A < X1B) {
			i1Max = WA - 1 + clipRect1.x;
			i2Max = X1A - X0B - 1 + clipRect2.x;
		} else {
			i1Max = X1B - X0A - 1 + clipRect1.x;
			i2Max = WB - 1 + clipRect2.x;
		}

		if (Y0A < Y0B) {
			j1Min = (Y0B - Y0A + clipRect1.y) * rowSize1;
			j2Min = clipRect2.y * rowSize2;
		} else {
			j1Min = clipRect1.y * rowSize1;
			j2Min = (Y0A - Y0B + clipRect2.y) * rowSize2;
		}

		if (Y1A < Y1B) {
			j1Max = (HA - 1 + clipRect1.y) * rowSize1;
			j2Max = (Y1A - Y0B - 1 + clipRect2.y) * rowSize2;
		} else {
			j1Max = (Y1B - Y0A - 1 + clipRect1.y) * rowSize1;;
			j2Max = (HB - 1 + clipRect2.y) * rowSize2;
		}

		if (i1Min > i1Max || i2Min > i2Max) {
			return 0;
		} else{
			// Do nothing
		}

		if (j1Min > j1Max || j2Min > j2Max) {
			return 0;
		} else {
			// Do nothing
		}

		int w1Size = i1Max + i1Min;
		int w2Size = i2Max + i2Min;

		for (int j1 = j1Min, j2 = j2Min; j1 <= j1Max ; j1 += rowSize1, j2 += rowSize2) {
			for (int i1 = i1Min, i2 = i2Min; i1 <= i1Max; i1++, i2++) {
				Uint8 r1;
				Uint8 g1;
				Uint8 b1;
				Uint8 a1;
				int pixelPosition1 = INITIAL_VALUE;
				if (mirror1) {
					pixelPosition1 = j1 + w1Size - i1;
				} else {
					pixelPosition1 = j1 + i1;
				}
				SDL_GetRGBA(pixels1[pixelPosition1], format1, &r1, &g1, &b1, &a1);

				Uint8 r2;
				Uint8 g2;
				Uint8 b2;
				Uint8 a2;
				int pixelPosition2 = INITIAL_VALUE;
				if (mirror2) {
					pixelPosition2 = j2 + w2Size - i2;
				} else {
					pixelPosition2 = j2 + i2;
				}
				SDL_GetRGBA(pixels2[pixelPosition2], format2, &r2, &g2, &b2, &a2);

				int const TOlERANT_ALPHA = 200;
				if (a1 > TOlERANT_ALPHA && a2 > TOlERANT_ALPHA) {
					colision++;
				} else {
					// Do nothing
				}
			}
		}

		SDL_UnlockSurface(surface1);
		SDL_UnlockSurface(surface2);

		return colision;
	} else{
		//do nothing
	}
}


/**
 * Objective: Check if two GameObjects have collided. 
 *
 * @param GameObject object1 - An object of the game. 
 * @param GameObject object2 - An object of the game. 
 * @return int colision - 1 if colided, 0 if not. 
 */
int ColisionFunctions::PixelPerfectColision(GameObject *object1, GameObject *object2) {
	if(object1 != NULL && object2 != NULL){
    SDL_Surface *surface1;
    SDL_Rect clipRect1;
    Vec2 pos1;
    bool mirror1 = false;

    if (object1->GetColisionData(&surface1, clipRect1, pos1, mirror1) == false) {
        return 0;
    } else {
		// Do nothing
	}

    SDL_Surface *surface2;
    SDL_Rect clipRect2;
    Vec2 pos2;
    bool mirror2 = false;

    if (object2->GetColisionData(&surface2, clipRect2, pos2, mirror2) == false) {
        return 0;
    } else {
		// Do nothing
	}

    return ColisionFunctions::PixelPerfectColision(surface1, clipRect1, pos1, mirror1, surface2,
                                                   clipRect2, pos2, mirror2);
	} else{
		//do nothing
	}
	}

/**
 * Objective: Check if points are in a colision ray.
 *
 * @param TileMap map - A map that contains all gameobjects positions in the stage. 
 * @param Vec2 pos1 - position of the object 1 in the tileMap. 
 * @param Vec2 pos2 - position of the object 2 in the tileMap. 
 * @return bool inRayCastColision - boolean that tell if is in ray cast colision. 
 */
bool ColisionFunctions::RayCastColision(TileMap *map, Vec2 pos1, Vec2 pos2) {
	if(map!=NULL){
		float const MINIMUN_COLISION_RAY = 50.0f;
		Vec2 blockSize = map->GetTileSize();
		SDL_Point p1 = {std::round(pos1.x / blockSize.x), std::round(pos1.y / blockSize.y)};
		SDL_Point p2 = {std::round(pos2.x / blockSize.x), std::round(pos2.y / blockSize.y)};
		SDL_Point m = {p2.x - p1.x, p2.y - p1.y};
		SDL_Point p;
		bool inRayCastColision = false;

		for (int i = 0; i < MINIMUN_COLISION_RAY; i++) {
			p.x = p1.x + (i / MINIMUN_COLISION_RAY) * m.x;
			p.y = p1.y + (i / MINIMUN_COLISION_RAY) * m.y;

			if (map->At(p.x, p.y, 0) != -1) {
				inRayCastColision = true;
			} else {
				inRayCastColision = false;
			}
		}
		return inRayCastColision;
	}
}

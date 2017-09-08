// Copyright 2013 Thomas Park.

#include <cmath>
#include "ColisionFunctions.h"
#ifndef clamp
#define clamp(N, L, U) N = std::max(L, std::min(N, U))
#endif

inline void ColisionFunctions::GetSurfaceData(SDL_Surface *surface, int &x, int &y, int &rowSize,
                                              Uint32 **pixels, SDL_PixelFormat **format) {
    SDL_LockSurface(surface);
    x = surface->w;
    y = surface->h;
    *pixels = (Uint32 *)surface->pixels;
    *format = surface->format;
    rowSize = surface->pitch/sizeof(unsigned int);
}

void ColisionFunctions::ConvertSurfaceColors(SDL_Surface *surface) {
    int x = 0;
    int y = 0;
    int rowSize = 0;
    Uint32* pixels;
    SDL_PixelFormat *format;

    ColisionFunctions::GetSurfaceData(surface, x, y, rowSize, &pixels, &format);

    Uint32 colorW = SDL_MapRGBA(format, 255, 0, 0, 255);
    Uint32 colorB = SDL_MapRGBA(format, 0, 0, 0, 0);

    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            Uint8 r;
            Uint8 g;
            Uint8 b;
            Uint8 a;
            int pixelPosition = j * rowSize + i;
            SDL_GetRGBA(pixels[pixelPosition], format, &r, &g, &b, &a);

            if (a > 100) {
                pixels[pixelPosition] = colorW;
            } else {
                pixels[pixelPosition] = colorB;
            }
        }
    }

    SDL_UnlockSurface(surface);
}

int ColisionFunctions::PixelPerfectColision(SDL_Surface *surface1, SDL_Rect clipRect1, Vec2 pos1,
                                            bool mirror1, SDL_Surface *surface2, SDL_Rect clipRect2,
                                            Vec2 pos2, bool mirror2) {
    int colision = 0;
    int xSize1 = 0;
    int ySize1 = 0;
    int rowSize1 = 0;
    Uint32* pixels1;
    SDL_PixelFormat *format1;
    ColisionFunctions::GetSurfaceData(surface1, xSize1, ySize1, rowSize1, &pixels1, &format1);

    int xSize2 = 0;
    int ySize2 = 0;
    int rowSize2 = 0;
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
    }

    if (j1Min > j1Max || j2Min > j2Max) {
        return 0;
    }

    int w1Size = i1Max + i1Min;
    int w2Size = i2Max + i2Min;

    for (int j1 = j1Min, j2 = j2Min; j1 <= j1Max ; j1 += rowSize1, j2 += rowSize2) {
        for (int i1 = i1Min, i2 = i2Min; i1 <= i1Max; i1++, i2++) {
            Uint8 r1;
            Uint8 g1;
            Uint8 b1;
            Uint8 a1;
            int pixelPosition1 = 0;
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
            int pixelPosition2 = 0;
            if (mirror2) {
                pixelPosition2 = j2 + w2Size - i2;
            } else {
                pixelPosition2 = j2 + i2;
            }
            SDL_GetRGBA(pixels2[pixelPosition2], format2, &r2, &g2, &b2, &a2);

            if (a1 > 200 && a2 > 200) {
                colision++;
            }
        }
    }

    SDL_UnlockSurface(surface1);
    SDL_UnlockSurface(surface2);

    return colision;
}


int ColisionFunctions::PixelPerfectColision(GameObject *object1, GameObject *object2) {
    SDL_Surface *surface1;
    SDL_Rect clipRect1;
    Vec2 pos1;
    bool mirror1 = false;

    if (object1->GetColisionData(&surface1, clipRect1, pos1, mirror1) == false) {
        return 0;
    }

    SDL_Surface *surface2;
    SDL_Rect clipRect2;
    Vec2 pos2;
    bool mirror2 = false;

    if (object2->GetColisionData(&surface2, clipRect2, pos2, mirror2) == false) {
        return 0;
    }

    return ColisionFunctions::PixelPerfectColision(surface1, clipRect1, pos1, mirror1, surface2,
                                                   clipRect2, pos2, mirror2);
}

bool ColisionFunctions::RayCastColision(TileMap *map, Vec2 pos1, Vec2 pos2) {
    Vec2 blockSize = map->GetTileSize();
    SDL_Point p1 = {std::round(pos1.x / blockSize.x), std::round(pos1.y / blockSize.y)};
    SDL_Point p2 = {std::round(pos2.x / blockSize.x), std::round(pos2.y / blockSize.y)};
    SDL_Point m = {p2.x - p1.x, p2.y - p1.y};
    SDL_Point p;

    for (int i = 0; i < 50; i++) {
        p.x = p1.x + (i / 50.0f) * m.x;
        p.y = p1.y + (i / 50.0f) * m.y;

        if (map->At(p.x, p.y, 0) != -1) {
            return true;
        }
    }
    return false;
}

#include <math.h>
#include "PixelPerfectColision.h"
#ifndef clamp
	#define clamp(N,L,U) N=std::max(L,std::min(N,U))
#endif

inline void PixelPerfectColision::GetSurfaceData(SDL_Surface *surface,int &x,int &y,
						   int &rowSize,Uint32 **pixels,SDL_PixelFormat **format)
{
	SDL_LockSurface(surface);
	x = surface->w;
	y = surface->h;
	*pixels = (Uint32*)surface->pixels;
	*format = surface->format;
	rowSize = surface->pitch/sizeof(unsigned int);
}

void PixelPerfectColision::ConvertSurfaceColors(SDL_Surface *surface)
{
	int x,y,rowSize;
	Uint32* pixels;
	SDL_PixelFormat *format;

	PixelPerfectColision::GetSurfaceData(surface,x,y,rowSize,&pixels,&format);

	Uint32 colorW = SDL_MapRGBA(format,255,0,0,255);
	Uint32 colorB = SDL_MapRGBA(format,0,0,0,0);

	for(int j=0; j<y; j++)
		for (int i=0; i<x; i++)
		{
			Uint8 r, g, b, a;
			int pixelPosition = j*rowSize+i;
			SDL_GetRGBA(pixels[pixelPosition],format,&r,&g,&b,&a);
			if (a>100)
				pixels[pixelPosition] = colorW;
			else
				pixels[pixelPosition] = colorB;
		}

	SDL_UnlockSurface(surface);
}

int PixelPerfectColision::CheckColision(SDL_Surface *surface1, SDL_Rect clipRect1, Vec2 pos1, bool mirror1,
				  SDL_Surface *surface2, SDL_Rect clipRect2, Vec2 pos2, bool mirror2)
{
	int colision = 0;

	int xSize1,ySize1,rowSize1;
	Uint32* pixels1;
	SDL_PixelFormat *format1;
	PixelPerfectColision::GetSurfaceData(surface1,xSize1,ySize1,rowSize1,&pixels1,&format1);

	int xSize2,ySize2,rowSize2;
	Uint32* pixels2;
	SDL_PixelFormat *format2;
	PixelPerfectColision::GetSurfaceData(surface2,xSize2,ySize2,rowSize2,&pixels2,&format2);

	int WA = clipRect1.w;
	int X0A = std::round(pos1.x);
	int X1A = X0A+WA;
	int HA = clipRect1.h;
	int Y0A = std::round(pos1.y);
	int Y1A = Y0A+HA;
	int WB = clipRect2.w;
	int X0B = std::round(pos2.x);
	int X1B = X0B+WB;
	int HB = clipRect2.h;
	int Y0B = std::round(pos2.y);
	int Y1B = Y0B+HB;
	int i1min,i2min,i1max,i2max;
	int j1min,j2min,j1max,j2max;

	if (X0A < X0B)
	{
		i1min = X0B-X0A+clipRect1.x;
		i2min = clipRect2.x;
	}
	else
	{
		i1min = clipRect1.x;
		i2min = X0A-X0B+clipRect2.x;
	}
	if (X1A < X1B)
	{
		i1max = WA-1+clipRect1.x;
		i2max = X1A-X0B-1+clipRect2.x;
	}
	else
	{
		i1max = X1B-X0A-1+clipRect1.x;
		i2max = WB-1+clipRect2.x;
	}

	if (Y0A < Y0B)
	{
		j1min = (Y0B-Y0A+clipRect1.y)*rowSize1;
		j2min = clipRect2.y*rowSize2;
	}
	else
	{
		j1min = clipRect1.y*rowSize1;
		j2min = (Y0A-Y0B+clipRect2.y)*rowSize2;
	}
	if (Y1A < Y1B)
	{
		j1max = (HA-1+clipRect1.y)*rowSize1;
		j2max = (Y1A-Y0B-1+clipRect2.y)*rowSize2;
	}
	else
	{
		j1max = (Y1B-Y0A-1+clipRect1.y)*rowSize1;;
		j2max = (HB-1+clipRect2.y)*rowSize2;
	}

	if (i1min>i1max || i2min>i2max)
		return 0;
	if (j1min>j1max || j2min>j2max)
		return 0;

	int w1size = i1max+i1min;
	int w2size = i2max+i2min;

	for(int j1=j1min,j2=j2min; j1<=j1max ; j1+=rowSize1,j2+=rowSize2)
	{
		for (int i1=i1min,i2=i2min; i1<=i1max ; i1++,i2++)
		{
			Uint8 r1, g1, b1, a1;
			int pixelPosition1;
			if (mirror1)
				pixelPosition1 = j1+w1size-i1;
			else
				pixelPosition1 = j1+i1;
			SDL_GetRGBA(pixels1[pixelPosition1],format1,&r1,&g1,&b1,&a1);

			Uint8 r2, g2, b2, a2;
			int pixelPosition2;
			if (mirror2)
				pixelPosition2 = j2+w2size-i2;
			else
				pixelPosition2 = j2+i2;
			SDL_GetRGBA(pixels2[pixelPosition2],format2,&r2,&g2,&b2,&a2);

			if (a1>200 && a2>200)
			{
				colision++;
			}
		}
	}

	SDL_UnlockSurface(surface1);
	SDL_UnlockSurface(surface2);

	return colision;
}


int PixelPerfectColision::CheckColision(GameObject *object1,GameObject *object2)
{
	SDL_Surface *surface1;
	SDL_Rect clipRect1;
	Vec2 pos1;
	bool mirror1;
	if (object1->GetColisionData(&surface1,clipRect1,pos1,mirror1)==false)
		return 0;

	SDL_Surface *surface2;
	SDL_Rect clipRect2;
	Vec2 pos2;
	bool mirror2;
	if (object2->GetColisionData(&surface2,clipRect2,pos2,mirror2)==false)
		return 0;

	return PixelPerfectColision::CheckColision(surface1,clipRect1,pos1,mirror1,surface2,clipRect2,pos2,mirror2);
}

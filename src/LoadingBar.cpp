#include "LoadingBar.h"

LoadingBar::LoadingBar(std::string image, int leftBorder_, int rightBorder_):
	discrete(false),
	percentage(1.0f),
	leftBorder(leftBorder_),
	rightBorder(rightBorder_),
	sp(image,2)
{

}

LoadingBar::LoadingBar(std::string image,int stateCount_):
	stateCount(stateCount_),
	blockSize(0),
	discrete(true),
	percentage(1.0f),
	leftBorder(0),
	sp(image,stateCount_)
{
	
}

LoadingBar::LoadingBar(std::string image, int leftBorder_, int blockSize_,int stateCount_):
	stateCount(stateCount_),
	blockSize(blockSize_),
	discrete(true),
	percentage(1.0f),
	leftBorder(leftBorder_),
	sp(image,2)
{

}

void LoadingBar::SetPercentage(float p)
{
	clamp(p,0.0f,1.0f);
	percentage = p;
}

void LoadingBar::Render(int x, int y)
{
	sp.SetFrameNormalized(0.0);
	sp.Render(x,y,0);
	sp.SetFrameNormalized(1.0);
	SDL_Rect r = sp.GetClip();
	if (discrete)
	{
		if (blockSize!=0)
		{
			int current = stateCount*percentage;
			r.w = leftBorder+blockSize*current;
			sp.SetClip(r.x,r.y,r.w,r.h);
			sp.Render(x,y,0);
		}
		else
		{
			sp.SetFrameNormalized(percentage);
			sp.Render(x,y,0);
		}
	}
	else
	{
		r.x += leftBorder;
		r.w = (r.w-rightBorder-leftBorder)*percentage+leftBorder;
		sp.SetClip(r.x,r.y,r.w,r.h);
		sp.Render(x+leftBorder,y,0);
	}

}

Vec2 LoadingBar::GetSize()
{
	return sp.GetSize();
}

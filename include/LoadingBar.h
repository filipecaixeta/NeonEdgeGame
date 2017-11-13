#ifndef LOADINGBAR_H
#define LOADINGBAR_H
#include <string>

#include "Sprite.h"
#include "Vec2.h"

#define INT_INITIAL_VALUE 0
#define FLOAT_INITIAL_VALUE 0.0f
#define ONE_PERCENT 1.0f
#define BAR_POSITION 2

class LoadingBar
{
	public:
		// Continua
		LoadingBar(std::string image, int leftBorder_, int rightBorder_);
		// Discreta
		LoadingBar(std::string image, int stateCount_);
		LoadingBar(std::string image, int leftBorder_, int blockSize_, int stateCount_);
		void SetPercentage(float p);
		void Render(int x, int y);
		Vec2 GetSize();
private:
		int stateCount;
		int blockSize;
		bool discrete;
		float percentage;
		int leftBorder;
		int rightBorder;
		Sprite sp;
};

#endif // LOADINGBAR_H

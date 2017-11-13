#include "LoadingBar.h"

LoadingBar::LoadingBar(std::string image, int leftBorder_, int rightBorder_):
    sp(image, BAR_POSITION) {
    discrete = false;
    percentage = ONE_PERCENT;
    leftBorder = leftBorder_;
    rightBorder = rightBorder_;
}

LoadingBar::LoadingBar(std::string image, int stateCount_):
    sp(image,stateCount_) {
    stateCount = stateCount_;
    blockSize = INT_INITIAL_VALUE;
    discrete = true;
    percentage = ONE_PERCENT;
    leftBorder = INT_INITIAL_VALUE;
}

LoadingBar::LoadingBar(std::string image, int leftBorder_, int blockSize_, int stateCount_):
    sp(image, BAR_POSITION) {
    stateCount = stateCount_;
    blockSize = blockSize_;
    discrete = true;
    percentage = ONE_PERCENT;
    leftBorder = leftBorder_;
}

void LoadingBar::SetPercentage(float p) {
    clamp(p, FLOAT_INITIAL_VALUE, ONE_PERCENT);
    percentage = p;
}

void LoadingBar::Render(int x, int y) {
    sp.SetFrameNormalized(FLOAT_INITIAL_VALUE);
    sp.Render(x, y, INT_INITIAL_VALUE);
    sp.SetFrameNormalized(ONE_PERCENT);
    SDL_Rect r = sp.GetClip();
    if (discrete) {
        if (blockSize != INT_INITIAL_VALUE) {
            int current = stateCount * percentage;
            r.w = leftBorder + blockSize * current;
            sp.SetClip(r.x, r.y, r.w, r.h);
            sp.Render(x, y, INT_INITIAL_VALUE);
        } else {
            sp.SetFrameNormalized(percentage);
            sp.Render(x, y, INT_INITIAL_VALUE);
        }
    } else {
        r.x += leftBorder;
        r.w = (r.w - rightBorder - leftBorder) * percentage + leftBorder;
        sp.SetClip(r.x, r.y, r.w, r.h);
        sp.Render(x + leftBorder, y, INT_INITIAL_VALUE);
    }
}

Vec2 LoadingBar::GetSize() {
    return sp.GetSize();
}

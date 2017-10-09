#ifndef INPUT_H
#define INPUT_H

#include "Vec2.h"
#include "LoadingBar.h"
#include <string>
#define INT_MIN_SIZE -32768
#define INT_MAX_SIZE 32767
#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f


class Input {
public:
    enum type: short int{BUTTON, TEXT, TEXTAREA, SLIDER, SELECTBOX};
    Input(type typeParam);
    void SetPosition(Vec2 position);
    void SetValue(float value);
    void SetOption(int option);
    void SetText(std::string text);
    float GetValue();
    int GetOption();
    Vec2 GetPosition();
    Vec2 GetSize();
    std::string GetText();
    void Render();
protected:
    LoadingBar *loadingBar;
    float value;
    int option;
    std::string text;
    Vec2 position;
    type typeObject;
};

#endif // INPUT_H

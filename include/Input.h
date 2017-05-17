#ifndef INPUT_H
#define INPUT_H
#include <Vec2.h>
#include <string>
#include <LoadingBar.h>

class Input
{
public:
	enum type: short int{BUTTON,TEXT,TEXTAREA,SLIDER,SELECTBOX};
	Input(type t);
	void SetPosition(Vec2 pos);
	void SetValue(float value_);
	void SetOption(int option_);
	void SetText(std::string text_);
	float GetValue();
	int GetOption();
	Vec2 GetPosition();
	Vec2 GetSize();
	std::string GetText();
	void Render();
protected:
	LoadingBar *lb;
	float value;
	int option;
	std::string text;
	Vec2 position;
	type type_;
};

#endif // INPUT_H

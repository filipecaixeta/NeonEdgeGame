#include "Input.h"

Input::Input(type t):
	type_(t)
{
	if (type_==type::SLIDER)
	{
		lb = new LoadingBar("sliderMenu.png",5,15,10);
	}
}

void Input::SetPosition(Vec2 pos)
{
	position = pos;
}

void Input::SetValue(float value_)
{
	value = value_;
	if (type_==type::SLIDER)
	{
		lb->SetPercentage(value);
	}
}

void Input::SetOption(int option_)
{
	option = option_;
}

void Input::SetText(std::string text_)
{
	text = text_;
}

float Input::GetValue()
{
	return value;
}

int Input::GetOption()
{
	return option;
}

Vec2 Input::GetPosition()
{
	return position;
}

Vec2 Input::GetSize()
{
	if (type_==type::SLIDER)
	{
		return lb->GetSize();
	}
	else
		return Vec2(1.0,1.0);
}

std::string Input::GetText()
{
	return text;
}

void Input::Render()
{
	if (type_==type::SLIDER)
	{
		lb->Render(position.x,position.y);
	}
}

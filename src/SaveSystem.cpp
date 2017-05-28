#include <fstream>

#include "SaveSystem.h"
#include "StageState.h"
  
void Save(std::string fileName)
{
	Write();
	std::fstream fs;
	fs.open(fileName, std::fstream::out | std::fstream::trunc);
	fs.write((char*)&data, sizeof(data));
	fs.close();
}

void Write()
{
	data.x = StageState::GetPlayer()->box.x;
	data.y = StageState::GetPlayer()->box.y;
}

void Load(std::string fileName)
{
	std::fstream fs;
	fs.open(fileName, std::fstream::in);
	fs.read((char*)&data, sizeof(data));
	fs.close();
	Read();
}

void Read()
{
	StageState::GetPlayer()->box.y = data.y;
	StageState::GetPlayer()->box.x = data.x;
}

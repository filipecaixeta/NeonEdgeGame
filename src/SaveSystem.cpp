#include "SaveSystem.h"
#include "Godofredo.h"
  
void Save(std::string fileName)
{
//  Update();
  std::fstream fs;
  fs.open(fileName, std::fstream::out | std::fstream::trunc);
  fs.write((char*)&data, sizeof(data));
  fs.close();
}

void Write()
{
  data.hp = Godofredo::player->hitpoints;
  data.x = Godofredo::player->box.x;
  data.y = Godofredo::player->box.y;
}

void Load(std::string fileName)
{
  std::fstream fs;
  fs.open(fileName, std::fstream::in);
  fs.read((char*)&data, sizeof(data));
  fs.close();
}

void Read()
{
  Godofredo::player->box.y = data.y;
  Godofredo::player->box.x = data.x;
  Godofredo::player->hitpoints = data.hp;
}

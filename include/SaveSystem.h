#ifndef SAVESYSTEM_H_
#define SAVESYSTEM_H_

#include "Resources.h"
#include <fstream>

struct Data 
{
	int hp = 0;
	float x = 0;
	float y = 0;
};
  
static Data data;

void Save(std::string fileName);
void Write();
void Load(std::string fileName);
void Read();

#endif

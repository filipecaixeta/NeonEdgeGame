#include <iostream>
#include <fstream>
#include <cstring>

#include "IOFunctions.h"

std::stringstream IOFunctions::Open(std::string fileName, bool crpt)
{

	std::ifstream file(fileName);
	std::stringstream buffer;
	if (file.is_open())
	{
		buffer << file.rdbuf();
		file.close();
	}

	if (crpt)
	{
		std::string password(PASSWORD);
		int passSize = password.size();
		std::string tmp = buffer.str();
		int buffSize = tmp.size();
		for (int i=0; i<buffSize; i++)
		{
			tmp[i] = tmp[i]^password[i%passSize];
		}
		std::stringstream bufferDecript;
		bufferDecript << tmp;
		return bufferDecript;
	}
	return buffer;
}

void IOFunctions::Save(std::string fileName, std::string data, bool crpt)
{
	IOFunctions::Save(fileName,(void*)data.c_str(),data.size(),crpt);
}

void IOFunctions::Save(std::string fileName, void* data, unsigned int buffSize, bool crpt)
{
	std::fstream file(fileName);

	if (crpt)
	{
		char* buff = (char*)data;
		std::string password(PASSWORD);
		int passSize = password.size();
		for (int i=0; i<buffSize; i++)
		{
			buff[i] = buff[i]^password[i%passSize];
		}
	}

	if (file.is_open())
	{
		file.write((const char*)data, buffSize);
		file.close();
	}
}

#ifndef IOFUNCTIONS_H
#define IOFUNCTIONS_H
#include <string>
#include <sstream>

#define PASSWORD "teste tesotoso"

namespace IOFunctions
{

	std::string Open(std::string fileName, bool crpt=false);
	void Save(std::string fileName, std::string data, bool crpt=false);
	void Save(std::string fileName, void* data, unsigned int buffSize, bool crpt);

}

#endif // IOFUNCTIONS_H

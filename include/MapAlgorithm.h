#ifndef MAPALGORITHM_H_
#define MAPALGORITHM_H_

#include <vector>
#include <ctime>
#include <cstdlib>
#include <SDL.h>

class MapAlgorithm{
public:
	MapAlgorithm();
	void RandomizeRoomOrder(std::vector<int>* roomOrder);
	void PopulateRoomArray(int** roomArray, std::vector<int>* roomOrder, std::pair<int, int>* aux,/*std::vector<std::pair<int, int>>* roomWay,*/ int sizeX, int sizeY);
private:
	bool CanGo(int** roomArray, std::pair<int, int> pos, int sizeX, int sizeY);
	bool IsBlocked(int** roomArray, std::pair<int, int> pos, int sizeX, int sizeY);
	void CleanMap(int** roomArray, std::pair<int, int>* aux, int sizeX, int sizeY);
	void PopulateBranch(int** roomArray, std::vector<int>* roomOrder, std::pair<int, int> aux, int sizeX, int sizeY);
};

#endif
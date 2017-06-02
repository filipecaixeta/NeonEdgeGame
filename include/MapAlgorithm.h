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
	void PopulateBranch(int** roomArray, std::vector<int>* roomOrder, std::pair<int, int> aux, int sizeX, int sizeY);
};

#endif
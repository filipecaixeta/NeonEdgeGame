#include "MapAlgorithm.h"
#include <iostream>

MapAlgorithm::MapAlgorithm(){

}

void MapAlgorithm::RandomizeRoomOrder(std::vector<int>* roomOrder){
	int random;

	srand(time(NULL));

	for(int i = 0; i < 10; i++){
		random = rand() % 3 + 2;
		if(i == 0){
			roomOrder->emplace_back(0);
		}
		else if(i == 5){
			roomOrder->emplace_back(1);
		}
		else{
			roomOrder->emplace_back(random);
		}
	}
}

void MapAlgorithm::PopulateRoomArray(int** roomArray, std::vector<int>* roomOrder, std::pair<int, int>* aux, int sizeX, int sizeY){
	int random;
	bool endRandom;

	srand(time(NULL));

	for(int i = 0; i < roomOrder->size(); i++){
		endRandom = false;
		if(i == 0){
			roomArray[aux->first][aux->second] = roomOrder->at(i);
		}
		else{
			while(endRandom == false){
				random = rand() % 4;
				if(random == 0 && aux->first + 1 < sizeX){
					if(roomArray[aux->first + 1][aux->second] == -1){
						aux->first += 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						endRandom = true;
					}
				}
				else if(random == 1 && aux->first - 1 > 0){
					if(roomArray[aux->first - 1][aux->second] == -1){
						aux->first -= 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						endRandom = true;
					}
				}
				else if(random == 2 && aux->second + 1 < sizeY){
					if(roomArray[aux->first][aux->second + 1] == -1){
						aux->second += 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						endRandom = true;
					}
				}
				else if(random == 3 && aux->second - 1 > 0){
					if(roomArray[aux->first][aux->second - 1] == -1){
						aux->second -= 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						endRandom = true;
					}
				}
			}
		}
	}
}
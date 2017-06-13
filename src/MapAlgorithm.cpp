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

bool MapAlgorithm::CanGo(int** roomArray, std::pair<int, int> pos, int sizeX, int sizeY){
	if(pos.first < 0 || pos.second < 0){
		return false;
	}
	if(pos.first >= sizeX || pos.second >= sizeY){
		return false;
	}
	if(roomArray[pos.first][pos.second] != -1){
		return false;
	}
	return true;
}

bool MapAlgorithm::IsBlocked(int** roomArray, std::pair<int, int> pos, int sizeX, int sizeY){
	bool t = false;
	t = t || CanGo(roomArray, std::make_pair(pos.first + 1, pos.second), sizeX, sizeY);
	t = t || CanGo(roomArray, std::make_pair(pos.first - 1, pos.second), sizeX, sizeY);
	t = t || CanGo(roomArray, std::make_pair(pos.first, pos.second + 1), sizeX, sizeY);
	t = t || CanGo(roomArray, std::make_pair(pos.first, pos.second - 1), sizeX, sizeY);
	return !t;
}

/*bool MapAlgorithm::CheckSurroudings(int** roomArray, std::pair<int, int>* aux, int sizeX, int sizeY){
	bool t;
	t = t || IsBlocked()
}*/

void MapAlgorithm::CleanMap(int** roomArray, std::pair<int, int>* aux, int sizeX, int sizeY){
	for(int i = 0; i < sizeX; i++){
		for(int j = 0; j < sizeY; j++){
			roomArray[i][j] = -1;
		}
	}
	aux->first = 0;
	aux->second = 0;
}

void MapAlgorithm::PopulateRoomArray(int** roomArray, std::vector<int>* roomOrder, std::pair<int, int>* aux, /*std::vector<std::pair<int, int>>* roomWay,*/ int sizeX, int sizeY){
	int random;
	bool endRandom;

	srand(time(NULL));

	for(int i = 0; i < roomOrder->size(); i++){
		endRandom = false;
		if(i == 0){
			roomArray[aux->first][aux->second] = roomOrder->at(i);
		}
		else{
			// if(aux->first + 1 < sizeX && aux->second + 1 < sizeY && aux->first - 1 > 0 && aux->second - 1 > 0){
			// 	if(roomArray[aux->first + 1][aux->second] > -1 && roomArray[aux->first - 1][aux->second] > -1 &&
			// 		roomArray[aux->first][aux->second + 1] > -1 && roomArray[aux->first][aux->second - 1] > -1){
			// 		for(int i = 0; i < sizeX; i++){
			// 			for(int j = 0; j < sizeY; j++){
			// 				roomArray[i][j] = -1;
			// 			}
			// 		}

			// 		aux->first = 0;
			// 		aux->second = 3;
					
			// 		//roomWay->clear();
			// 		this->PopulateRoomArray(roomArray, roomOrder, aux, /*roomWay,*/ sizeX, sizeY);
			// 		break;
			// 	}
			// }
			// if(aux->second + 1 < sizeY && aux->first - 1 > 0 && aux->second - 1 > 0){
			// 	if(roomArray[aux->first - 1][aux->second] > -1 && roomArray[aux->first][aux->second + 1] > -1 && roomArray[aux->first][aux->second - 1] > -1){
			// 		for(int i = 0; i < sizeX; i++){
			// 			for(int j = 0; j < sizeY; j++){
			// 				roomArray[i][j] = -1;
			// 			}
			// 		}

			// 		aux->first = 0;
			// 		aux->second = 3;
					
			// 		//roomWay->clear();
			// 		this->PopulateRoomArray(roomArray, roomOrder, aux, /*roomWay,*/ sizeX, sizeY);
			// 		break;
			// 	}
			// }
			// if(aux->first + 1 < sizeX && aux->first - 1 > 0 && aux->second - 1 > 0){
			// 	if(roomArray[aux->first + 1][aux->second] > -1 && roomArray[aux->first - 1][aux->second] > -1 && roomArray[aux->first][aux->second - 1] > -1){
			// 		for(int i = 0; i < sizeX; i++){
			// 			for(int j = 0; j < sizeY; j++){
			// 				roomArray[i][j] = -1;
			// 			}
			// 		}

			// 		aux->first = 0;
			// 		aux->second = 3;
					
			// 		//roomWay->clear();
			// 		this->PopulateRoomArray(roomArray, roomOrder, aux, /*roomWay,*/ sizeX, sizeY);
			// 		break;
			// 	}
			// }
			// if(aux->first + 1 < sizeX && aux->second + 1 < sizeY && aux->second - 1 > 0){
			// 	if(roomArray[aux->first + 1][aux->second] > -1 && roomArray[aux->first][aux->second + 1] > -1 && roomArray[aux->first][aux->second - 1] > -1){
			// 		for(int i = 0; i < sizeX; i++){
			// 			for(int j = 0; j < sizeY; j++){
			// 				roomArray[i][j] = -1;
			// 			}
			// 		}

			// 		aux->first = 0;
			// 		aux->second = 3;

			// 		//roomWay->clear();
			// 		this->PopulateRoomArray(roomArray, roomOrder, aux, /*roomWay,*/ sizeX, sizeY);
			// 		break;
			// 	}
			// }
			// if(aux->first + 1 < sizeX && aux->second + 1 < sizeY && aux->first - 1 > 0){
			// 	if(roomArray[aux->first + 1][aux->second] > -1 && roomArray[aux->first - 1][aux->second] > -1 && roomArray[aux->first][aux->second + 1] > -1){
			// 		for(int i = 0; i < sizeX; i++){
			// 			for(int j = 0; j < sizeY; j++){
			// 				roomArray[i][j] = -1;
			// 			}
			// 		}

			// 		aux->first = 0;
			// 		aux->second = 3;

			// 		//roomWay->clear();
			// 		this->PopulateRoomArray(roomArray, roomOrder, aux, /*roomWay,*/ sizeX, sizeY);
			// 		break;
			// 	}
			// }
			if(IsBlocked(roomArray, std::make_pair(aux->first, aux->second), sizeX, sizeY)){
				CleanMap(roomArray, aux, sizeX, sizeY);
				this->PopulateRoomArray(roomArray, roomOrder, aux, sizeX, sizeY);
				break;
			}
			while(endRandom == false){
				random = rand() % 4;
				if(random == 0 && aux->first + 1 < sizeX){
					if(roomArray[aux->first + 1][aux->second] == -1){
						aux->first += 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						//roomWay->emplace_back(aux);
						endRandom = true;
					}
				}
				else if(random == 1 && aux->first - 1 > 0){
					if(roomArray[aux->first - 1][aux->second] == -1){
						aux->first -= 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						//roomWay->emplace_back(aux);
						endRandom = true;
					}
				}
				else if(random == 2 && aux->second + 1 < sizeY){
					if(roomArray[aux->first][aux->second + 1] == -1){
						aux->second += 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						//roomWay->emplace_back(aux);
						endRandom = true;
					}
				}
				else if(random == 3 && aux->second - 1 > 0){
					if(roomArray[aux->first][aux->second - 1] == -1){
						aux->second -= 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						//roomWay->emplace_back(aux);
						endRandom = true;
					}
				}
			}
		}
	}
}

void MapAlgorithm::PopulateBranch(int** roomArray, std::vector<int>* roomOrder, std::pair<int, int> aux, int sizeX, int sizeY){

}
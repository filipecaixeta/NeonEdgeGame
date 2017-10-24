#include "MapAlgorithm.h"
#include <iostream>

#include <assert.h>

MapAlgorithm::MapAlgorithm(int numberOfRooms){
	this->numberOfRooms = numberOfRooms;
}

void MapAlgorithm::RandomizeRoomOrder(std::vector<int>* roomOrder) {
	srand(time(NULL));

    int random = 0;

    for(int i = 0; i < numberOfRooms; i++){
		random = rand() % 3 + 2;
		if(i == 0){
			roomOrder->emplace_back(0);
		}
		else if (i == 5){
			roomOrder->emplace_back(1);
		}
		else {
			roomOrder->emplace_back(random);
		}
        assert(random >= INT_MIN_SIZE && random <= INT_MAX_SIZE);
	}
}

bool MapAlgorithm::CanGo(int** roomArray, std::pair<int, int> pos, int sizeX, int sizeY){
    assert(sizeX >= INT_MIN_SIZE && sizeX <= INT_MAX_SIZE);
    assert(sizeY >= INT_MIN_SIZE && sizeY <= INT_MAX_SIZE);

	if (pos.first < 0 || pos.second < 0) {
		return false;
	} else {
        // It does nothing.
    }
	if (pos.first >= sizeX || pos.second >= sizeY) {
		return false;
	} else {
        // It does nothing.
    }
	if(roomArray[pos.first][pos.second] != -1){
		return false;
	} else {
        // It does nothing.
    }
	return true;
}

bool MapAlgorithm::IsBlocked(int** roomArray, std::pair<int, int> pos, int sizeX, int sizeY) {
    assert(sizeX >= INT_MIN_SIZE && sizeX <= INT_MAX_SIZE);
    assert(sizeY >= INT_MIN_SIZE && sizeY <= INT_MAX_SIZE);

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

void MapAlgorithm::CleanMap(int** roomArray, std::pair<int, int>* aux, int sizeX, int sizeY) {
    assert(sizeX >= INT_MIN_SIZE && sizeX <= INT_MAX_SIZE);
    assert(sizeY >= INT_MIN_SIZE && sizeY <= INT_MAX_SIZE);

	for (int i = 0; i < sizeX; i++) {
		for(int j = 0; j < sizeY; j++) {
			roomArray[i][j] = -1;
		}
	}
	aux->first = 0;
	aux->second = 0;
}

void MapAlgorithm::PopulateRoomArray(int** roomArray, std::vector<int>* roomOrder, std::pair<int, int>* aux, /*std::vector<std::pair<int, int>>* roomWay,*/ int sizeX, int sizeY){
	srand(time(NULL));

    int random = 0;
    bool endRandom = false;
	for (int i = 0; i < roomOrder->size(); i++) {
		endRandom = false;
		if (i == 0) {
			roomArray[aux->first][aux->second] = roomOrder->at(i);
		} else {
			if (IsBlocked(roomArray, std::make_pair(aux->first, aux->second), sizeX, sizeY)) {
				CleanMap(roomArray, aux, sizeX, sizeY);
				this->PopulateRoomArray(roomArray, roomOrder, aux, sizeX, sizeY);
				break;
			}
			while (endRandom == false) {
				random = rand() % 4;
				if (random == 0 && aux->first + 1 < sizeX) {
					if (roomArray[aux->first + 1][aux->second] == -1) {
						aux->first += 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						//roomWay->emplace_back(aux);
						endRandom = true;
					} else {
                        // It does nothing.
                    }
				}
				else if (random == 1 && aux->first - 1 > 0){
					if (roomArray[aux->first - 1][aux->second] == -1){
						aux->first -= 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						//roomWay->emplace_back(aux);
						endRandom = true;
					} else {
                        // It does nothing.
                    }
				}
				else if (random == 2 && aux->second + 1 < sizeY) {
					if (roomArray[aux->first][aux->second + 1] == -1) {
						aux->second += 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						//roomWay->emplace_back(aux);
						endRandom = true;
					} else {
                        // It does nothing.
                    }
				}
				else if (random == 3 && aux->second - 1 > 0) {
					if (roomArray[aux->first][aux->second - 1] == -1) {
						aux->second -= 1;
						roomArray[aux->first][aux->second] = roomOrder->at(i);
						//roomWay->emplace_back(aux);
						endRandom = true;
					} else {
                        // It does nothing
                    }
				}
			}
		}
	}
}

void MapAlgorithm::PopulateBranch(int** roomArray, std::vector<int>* roomOrder, std::pair<int, int> aux, int sizeX, int sizeY){

}

#include "MapAlgorithm.h"
#include <iostream>

#include <assert.h>

MapAlgorithm::MapAlgorithm(int numberOfRooms) {
    assert(numberOfRooms >= INT_MIN_SIZE && numberOfRooms <= INT_MAX_SIZE);
    this->numberOfRooms = numberOfRooms;
}

void MapAlgorithm::RandomizeRoomOrder(std::vector<int>* roomOrder) {
    srand(time(NULL));

    int random = INITIAL_INT_VALUE;

    for (int i = INITIAL_INT_VALUE; i < numberOfRooms; i++) {
        random = rand() % MODULE_FOR_RANDOM_INT + SUM_FOR_RANDOM_INT;
        if (i == INITIAL_INT_VALUE) {
            roomOrder->emplace_back(INITIAL_INT_VALUE);
			  } else if (i == FIFTH_ROOM) {
            roomOrder->emplace_back(FIRST_ROOM);
        } else {
            roomOrder->emplace_back(random);
        }
    }
}

bool MapAlgorithm::CanGo(int** roomArray, std::pair<int, int> pos, int sizeX, int sizeY) {
    assert(sizeX >= INT_MIN_SIZE && sizeX <= INT_MAX_SIZE);
    assert(sizeY >= INT_MIN_SIZE && sizeY <= INT_MAX_SIZE);

    if (pos.first < INITIAL_INT_VALUE || pos.second < INITIAL_INT_VALUE) {
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

    for (int i = INITIAL_INT_VALUE; i < sizeX; i++) {
        for(int j = INITIAL_INT_VALUE; j < sizeY; j++) {
            roomArray[i][j] = -1;
        }
    }
    aux->first = INITIAL_INT_VALUE;
    aux->second = INITIAL_INT_VALUE;
}

void MapAlgorithm::PopulateRoomArray(int** roomArray, std::vector<int>* roomOrder, std::pair<int, int>* aux, /*std::vector<std::pair<int, int>>* roomWay,*/ int sizeX, int sizeY){
    srand(time(NULL));

    int random = INITIAL_INT_VALUE;
    bool endRandom = false;
    for (int i = INITIAL_INT_VALUE; i < roomOrder->size(); i++) {
        endRandom = false;
	      if (i == INITIAL_INT_VALUE) {
            roomArray[aux->first][aux->second] = roomOrder->at(i);
        } else {
            if (IsBlocked(roomArray, std::make_pair(aux->first, aux->second), sizeX, sizeY)) {
                CleanMap(roomArray, aux, sizeX, sizeY);
                this->PopulateRoomArray(roomArray, roomOrder, aux, sizeX, sizeY);
                break;
        }

        while (endRandom == false) {
				random = rand() % 4;
				if (random == INITIAL_INT_VALUE && aux->first + 1 < sizeX) {
            if (roomArray[aux->first + 1][aux->second] == -1) {
                aux->first += 1;
                roomArray[aux->first][aux->second] = roomOrder->at(i);
						    //roomWay->emplace_back(aux);
                endRandom = true;
            } else {
                // It does nothing.
            }
				} else if (random == 1 && aux->first - 1 > INITIAL_INT_VALUE){
				    if (roomArray[aux->first - 1][aux->second] == -1) {
                aux->first -= 1;
                roomArray[aux->first][aux->second] = roomOrder->at(i);
                //roomWay->emplace_back(aux);
						endRandom = true;
            } else {
                // It does nothing.
            }
        } else if (random == 2 && aux->second + 1 < sizeY) {
            if (roomArray[aux->first][aux->second + 1] == -1) {
                aux->second += 1;
                roomArray[aux->first][aux->second] = roomOrder->at(i);
                //roomWay->emplace_back(aux);
                endRandom = true;
            } else {
                // It does nothing.
            }
				} else if (random == 3 && aux->second - 1 > INITIAL_INT_VALUE) {
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

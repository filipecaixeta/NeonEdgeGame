/**
    Copyright 2017 Neon Edge Game
    @File Name: Room.cpp
    @Header File Name: Room.h
    @Class Name: Room
    @Objective: manages the rooms.

*/

#include <sstream>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Room.h"
#include "Camera.h"
#include "StageState.h"
#include "ColisionFunctions.h"
#include "Item.h"

#include "Character.h"
#include "Player.h"
#include "Lancelot.h"
#include "Gallahad.h"
#include "Drone.h"
#include "Notfredo.h"
#include "CeilingEnemy.h"
#include "Turret.h"
#include "TurretBoss.h"
#include "Arthur.h"

#include "Interactive.h"
#include "Door.h"
#include "PressurePlate.h"
#include "PressurePlateOneTime.h"
#include "HandScanner.h"
#include "Box.h"
#include "BoxSpawner.h"

/**
 * Objective: Constructor of the Room.
 * @param TileSet* tileset - load tile to room.
 * @param int index - .
 * @param Vec2 position - .
 * @param TileSet* background - background of room.
 * @param string mapName.
 * @return: Return a instance of Room.
 */
Room::Room(TileSet* tileSet, int index, Vec2 position, TileSet* background, std::string mapName):
    sceneObjects("resources/map/objs/"+
                 mapName+
                 "sceneObjects.txt") {
    Room::index = index; // Beginning of the room.
    std::stringstream ss; // This sequence of characters can be accessed directly as a string.
    Room::position = position; // Position in which the object will be inserted in the room.
    ss << index;
    // load map
    map = new TileMap("resources/map/room0"+
                       ss.str()+
                       ".txt", tileSet, {0, 0});
    std::cerr << map->GetSize() << std::endl;
    // set background
    backgroundMap = new TileMap("resources/map/bg.txt", background, {0, map->GetSize().y}, true);
    objectArray = std::vector<GameObject*>();
    LoadObjects("resources/map/objs/room0"+
                ss.str()+
                ".txt");
    CreateObjects();
    std::cout << ss.str() << "\t";
}
 
/**
 * Objective: Destroct the class Room, delocalizing some memory used in the class and shutdown dependent libraries.
 * @param None.
 * @return: Return free memory to the system.	
 */
Room::~Room() {
    delete map;
    // Clear all objects in room
    for(unsigned i = 0; i < objectArray.size(); i++) {
        delete objectArray[i];
    }
    objectArray.clear();
}

/*
 * Objective: adds the object to the end of the room list.
 * @param: GameObject* ptr - pointer to GameObject wich will be inserted.
 * @return: None.
 */
 
void Room::AddObject(GameObject* ptr) {
    objectArray.emplace_back(ptr);
}

/*
 * Objective: Add object at the beginning room list.
 * @param: GameObject* ptr - pointer to GameObject wich will be inserted.
 * @return: none.
 */
 
void Room::AddObjectAsFirst(GameObject* ptr) {
    objectArray.emplace(objectArray.begin(), ptr);
}

/*
 * Objective: remove object at room.
 * @param: GameObject* ptr - pointer to GameObject wich will be removed.
 * @return: None.
 */
 
void Room::RemoveObject(GameObject* ptr) {
    for(unsigned i = 0; i < objectArray.size(); i++) {
        // Search the list object.
        if (ptr == objectArray[i]) {
            if (!objectArray[i]->Is("Item")) {
                delete objectArray[i];
            } else {
                // It does nothing
            }
            objectArray.erase(objectArray.begin()+i);
            break;
        } else {
            // It does nothing
        }
    }
}

/*
 * Objective: Remove player from ObjectArray at room.
 * @param: None.
 * @return: None.
 */
 
void Room::RemovePlayer() {
    for(unsigned i = 0; i < objectArray.size(); i++) {
        // Check if the object is a player and remove him.
        if (objectArray[i] == StageState::GetPlayer()) {
            objectArray.erase(objectArray.begin()+i);
            break;
       } else {
           // It does nothing
       }
   }
}

/*
 * Objective: get first object at room.
 * @param: none.
 * @return: none.
 */
 
GameObject* Room::GetFirst() {
    return objectArray[0];
}

/*
 * Objective: get position from room.
 * @param: none.
 * @return: none.
 */
 
Vec2 Room::GetPos() {
    return position;
}

/*
 * Objective: get map from room.
 * @param: none.
 * @return: none.
 */
 
TileMap* Room::GetMap() {
    return map;
}

/*
 * Objective: update room object.
 * @param: none.
 * @return: none.
 */
 
void Room::ObjectUpdate(float dt) {
    for(unsigned i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(map, dt);
    }
}

/*
 * Objective: Checks object collision in room
 * @param: none.
 * @return: none.
 */
 
void Room::ObjectCollision() {
    for(unsigned i = 0; i < objectArray.size(); i++) {
        for(unsigned j = i+1; j < objectArray.size(); j++) {
            // Check if collision in x axis or y axis.
            if(objectArray[i]->Is("Animation") || objectArray[j]->Is("Animation")) {

            } else if (objectArray[i]->box.OverlapsWith(objectArray[j]->box)) {
                objectArray[i]->NotifyObjectCollision(objectArray[j]);
                objectArray[j]->NotifyObjectCollision(objectArray[i]);
                // Check colision between player and object.
                if (objectArray[i]->Is("Item") && objectArray[j]->IsPlayer()) {
                    dynamic_cast<Item*>(objectArray[i])->Eval(dynamic_cast<Player*>(objectArray[j]));
                } else {
                    // It does nothing
                }
            } else if (objectArray[j]->Is("Item") && objectArray[i]->IsPlayer()) {
                    dynamic_cast<Item*>(objectArray[j])->Eval(dynamic_cast<Player*>(objectArray[i]));
            }
        }
    }
}


/*
 * Objective: Clean objects in room
 * @param: none.
 * @return: none.
 */

void Room::ObjectCleanup() {
    for(unsigned i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) { // Check if Object is dead.
            // Unfocus the object.
            if (objectArray[i] == Camera::CheckInstance().GetFocus()) {
                Camera::CheckInstance().StopFocus();
            } else {
                // It does nothing
            }
            // Kill player if he leave the screem
            if (objectArray[i] == StageState::GetPlayer()) {
                StageState::KillPlayer();
            } else {
                // It does nothing
            }
            sceneObjects.AddObjectAfter(objectArray[i]->name, objectArray[i]->box.GetXY()+Vec2(0, objectArray[i]->box.h));
            delete objectArray[i];
            objectArray.erase(objectArray.begin()+i);
        } else {
            // It does nothing
        }
    }
}

/*
 * Function Objective: update states in room cleaning objects and colisions.
 * @param: none.
 * @return: none.
 */
 
void Room::Update(float dt) {
    ObjectUpdate(dt);
    sceneObjects.Update();
    ObjectCollision();
    ObjectCleanup();
}

/*
 * Function Objective: render room screen position.
 * @param: none.
 * @return: none.
 */
 
void Room::Render() {
    backgroundMap->RenderLayer(0, Camera::CheckInstance().screenPosition.x, Camera::CheckInstance().screenPosition.y);
    sceneObjects.Render();
    map->RenderLayer(0, Camera::CheckInstance().screenPosition.x, Camera::CheckInstance().screenPosition.y);
    sceneObjects.RenderAfter();
    for(unsigned i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
    //map->RenderLayer(0, Camera::GetInstance().pos.x, Camera::GetInstance().pos.y);
}

/*
 * Function Objective: create items and objects in room.
 * @param: none.
 * @return: none.
 */
 
void Room::CreateObjects() {
    for(unsigned int i = 0; i < objectData.size(); i++) {
        // Add items for Lancelot
        if (objectData.at(i).id == 0) {
            // Lancelot
            ItemsManager* itemsManager = new ItemsManager();
            AddObjectAsFirst(new Lancelot(itemsManager, objectData.at(i).x +
                             position.x * map->GetWidth() * map->GetTileWidth(),
                             objectData.at(i).y +
                             position.y * map->GetHeight() * map->GetTileHeight()));
            Player* p = (Player*) objectArray[0];
            StageState::SetPlayer(p);
        }
        // Add items for Gallahad
        else if (objectData.at(i).id == 1) {
            // Gallahad
            ItemsManager* itemsManager = new ItemsManager();
            AddObject(new Drone(itemsManager, objectData.at(i).x +
                                position.x * map->GetWidth() * map->GetTileWidth(),
                                objectData.at(i).y +
                                position.y * map->GetHeight() * map->GetTileHeight()));
            AddObjectAsFirst(new Gallahad(itemsManager, objectData.at(i).x +
                                          position.x * map->GetWidth() * map->GetTileWidth(),
                                             objectData.at(i).y +
                                             position.y * map->GetHeight() * map->GetTileHeight(),
                                             objectArray.at(objectArray.size()-1)));
            Player* p = (Player*) objectArray[0];
            StageState::SetPlayer(p);
        }
        // Add items for Arthur
        else if (objectData.at(i).id == 2) {
            // Arthur
            AddObject(new Arthur(objectData.at(i).x +
                                 position.x * map->GetWidth() * map->GetTileWidth(),
                                 objectData.at(i).y +
                                 position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for TurretBoss
        else if (objectData.at(i).id == 3) {
            AddObject(new TurretBoss(objectData.at(i).x +
                                     position.x * map->GetWidth() * map->GetTileWidth(),
                                     objectData.at(i).y +
                                     position.y * map->GetHeight() * map->GetTileHeight()));
            TurretBoss* t = nullptr;            
            t = (TurretBoss*) objectArray.at(objectArray.size()-1);
            AddObject(new TurretPiece(t, -60, -53, 4));
           
            TurretPiece* p = nullptr;            
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddTurret(p);
           
            AddObject(new TurretPiece(t, -60, -163, 4));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddTurret(p);
           
            AddObject(new TurretPiece(t, -60, -273, 4));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddTurret(p);
           
            AddObject(new TurretPiece(t, 0, -55, 2));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddPiece(p);
           
            AddObject(new TurretPiece(t, 0, -165, 2));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddPiece(p);
            
            AddObject(new TurretPiece(t, 0, -275, 2));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddPiece(p);
            
            AddObject(new TurretPiece(t, 0, 0, 1));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddPiece(p);
            
            AddObject(new TurretPiece(t, 0, -110, 1));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddPiece(p);
            
            AddObject(new TurretPiece(t, 0, -220, 1));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddPiece(p);
            
            AddObject(new TurretPiece(t, -5, -358, 0));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddPiece(p);
            
            AddObject(new TurretPiece(t, 25, -51, 3));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddTurret(p);
            
            AddObject(new TurretPiece(t, 25, -161, 3));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddTurret(p);
            
            AddObject(new TurretPiece(t, 25, -271, 3));
            p = (TurretPiece*) objectArray.at(objectArray.size()-1);
            t->AddTurret(p);
        }
        // Add items for Nofredo
        else if (objectData.at(i).id == 12) {
            // Notfredo
            AddObject(new Notfredo(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight(),
                      GROUND));
        }
        // Add items for CeilingEnemy
        else if (objectData.at(i).id == 14) {
            // CeilingEnemy
            AddObject(new CeilingEnemy(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for Turret
        else if (objectData.at(i).id == 16) {
            // Turret
            AddObject(new Turret(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for Door
        else if (objectData.at(i).id == 21) {
            // Door
            AddObject(new Door(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for PressurePlate
        else if (objectData.at(i).id == 22) {
            // PressurePlate
            Interactive* in = (Interactive*) objectArray.at(objectArray.size()-1);
            AddObjectAsFirst(new PressurePlate(objectData.at(i).x +
                             position.x * map->GetWidth() * map->GetTileWidth(),
                             objectData.at(i).y +
                             position.y * map->GetHeight() * map->GetTileHeight(), in));
        }
        // Add items for HandScanner
        else if (objectData.at(i).id == 23) {
            // HandScanner
            Interactive* in = (Interactive*) objectArray.at(objectArray.size()-1);
            AddObjectAsFirst(new HandScanner(objectData.at(i).x +
                             position.x * map->GetWidth() * map->GetTileWidth(),
                             objectData.at(i).y +
                             position.y * map->GetHeight() * map->GetTileHeight(), in));
        }
        // Add items for Box
        else if (objectData.at(i).id == 24) {
            // Box
            AddObject(new Box(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for BoxSpawner
        else if (objectData.at(i).id == 25) {
            // BoxSpawner
            AddObject(new BoxSpawner(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for PreassurePlateOneTime
        else if (objectData.at(i).id == 26) {
            // PressurePlateOneTime
            Interactive* in = (Interactive*) objectArray.at(objectArray.size()-1);
            AddObjectAsFirst(new PressurePlateOneTime(objectData.at(i).x +
                                                      position.x * map->GetWidth() * map->GetTileWidth(),
                                                      objectData.at(i).y +
                                                      position.y * map->GetHeight() * map->GetTileHeight(), in));
        }
        // Add items for Item
        else if (objectData.at(i).id > 100) {
            // Item
            AddObject(new Item(objectData[i].id, objectData[i].x, objectData[i].y));
        } else {
            // It does nothing
        }
    }
}

/*
   Function Objective: load objects from file in room
   @param: String file - this file lists the objects that will be inserted in this room.
   @return: none.
*/

void Room::LoadObjects(std::string file) {
    std::ifstream f;
    f.open(file.c_str(), std::ios::in);
    // Check if archive is open
    if (!f.is_open()) {
        std::cerr<< "f.open: unable to open file: " << file.c_str();
        return;
    } else {
        // It does nothing
    }
    for(std::string line; std::getline(f, line); ) {
        ObjectData data;
        std::stringstream ss(line);
        ss >> data.id;

        char delimiter =' ';
        ss >> delimiter;
        ss >> data.x;
        ss >> delimiter;
        ss >> data.y;
        ss >> delimiter;

        int n = 0;        
        ss >> n;
        ss >> delimiter;
        if (n > 20) {
            ObjectData newData;
            newData.id = n;
            ss >> newData.x;
            ss >> delimiter;
            ss >> newData.y;
            ss >> delimiter;
            objectData.push_back(newData);
        } else {
            // It does nothing
        }
        objectData.push_back(data);
    }
}


/**
 * Copyright 2017 Neon Edge Game
 * @File Name: Room.cpp
 * @Header File Name: Room.h
 * @Class Name: Room
 * @Objective: manages the rooms.

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
#include "Logger.h"
#include <assert.h>

/**
 * Objective: Constructor of the Room.
 *
 * @param TileSet* tileset - load tile to room.
 * @param int index - .
 * @param Vec2 position - .
 * @param TileSet* background - background of room.
 * @param string mapName.
 * @return: Return a instance of Room.
 */
Room::Room(TileSet* tileSet, int index, Vec2 roomPosition, TileSet* background, std::string mapName):
    sceneObjects("resources/map/objs/"+
                 mapName+
                 "sceneObjects.txt") {
    if (index >= INT_MIN_SIZE && index <= INT_MAX_SIZE) {
        Log::instance.info("Initing Room");
        Room::index = index; // Beginning of the room.
        std::stringstream roomId; // This sequence of characters can be accessed directly as a string.
        Room::position = roomPosition; // Position in which the object will be inserted in the room.
        roomId << index;
        // load map
        Log::instance.info("Loading map");        
        map = new TileMap("resources/map/room0"+
        roomId.str()+
                           ".txt", tileSet, {0, 0});
        std::cerr << map->GetSize() << std::endl;
        // set background
        Log::instance.info("Setting background");
        backgroundMap = new TileMap("resources/map/bg.txt", background, {0, map->GetSize().y}, true);
        objectArray = std::vector<GameObject*>();
        // load objects
        Log::instance.info("Loading objects");
        LoadObjects("resources/map/objs/room0"+
                    roomId.str()+
                    ".txt");
        CreateObjects();
        std::cout << roomId.str() << "\t";
    } else {
        Log::instance.error("Tested value of index is higher or lower than allowed!");
    }
}

/**
 * Objective: Destroct the class Room, delocalizing some memory used in the class and shutdown dependent libraries.
 *
 * @param None.
 * @return: Return free memory to the system.
 */
Room::~Room() {
    Log::instance.info("Destroy Room");
    delete map;
    // Clear all objects in room
    for(unsigned i = 0; i < objectArray.size(); i++) {
        delete objectArray[i];
    }
    objectArray.clear();
}

/*
 * Objective: adds the object to the end of the room list.
 *
 * @param: GameObject* ptr - pointer to GameObject wich will be inserted.
 * @return: None.
 */

void Room::AddObject(GameObject* ptr) {
    Log::instance.info("Initing Room");
    objectArray.emplace_back(ptr);
}

/*
 * Objective: Add object at the beginning room list.
 *
 * @param: GameObject* ptr - pointer to GameObject wich will be inserted.
 * @return: none.
 */

void Room::AddObjectAsFirst(GameObject* ptr) {
    objectArray.emplace(objectArray.begin(), ptr);
}

/*
 * Objective: remove object at room.
 *
 * @param: GameObject* ptr - pointer to GameObject wich will be removed.
 * @return: None.
 */

void Room::RemoveObject(GameObject* ptr) {
    Log::instance.info("Removing objects");
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
 *
 * @param: None.
 * @return: None.
 */

void Room::RemovePlayer() {
    Log::instance.info("Player removed from room");
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
 *
 * @param: none.
 * @return: none.
 */
 
GameObject* Room::GetFirstObject() {
    assert(&objectArray != NULL);
    return objectArray[0];
}

/*
 * Objective: get position from room.
 *
 * @param: none.
 * @return: none.
 */
 
Vec2 Room::GetRoomPosition() {
    assert(&position != NULL);
    return position;
}

/*
 * Objective: get map from room.
 *
 * @param: none.
 * @return: none.
 */

TileMap* Room::GetMap() {
    assert(&map != NULL);
    return map;
}

/*
 * Objective: update room object.
 *
 * @param: none.
 * @return: none.
 */

void Room::ObjectUpdate(float dt) {
    Log::instance.info("Updating objects");
    if (dt >= FLOAT_MIN_SIZE && dt <= FLOAT_MAX_SIZE) {
        for (unsigned i = 0; i < objectArray.size(); i++) {
            objectArray[i]->Update(map, dt);
        }
    } else {
        Log::instance.error("Tested value of dt is higher or lower than allowed!");
    }
}

/*
 * Objective: Checks object collision in room
 *
 * @param: none.
 * @return: none.
 */

void Room::ObjectCollision() {
    for(unsigned i = 0; i < objectArray.size(); i++) {
        for(unsigned j = i+1; j < objectArray.size(); j++) {
            // Check if collision in x axis or y axis.
            if(!objectArray[i]->Is("Animation") ||
               !objectArray[j]->Is("Animation")) {
                if (objectArray[i]->box.OverlapsWith(objectArray[j]->box)) {
                    objectArray[i]->NotifyObjectCollision(objectArray[j]);
                    objectArray[j]->NotifyObjectCollision(objectArray[i]);
                    // Check colision between player and object.
                    if (objectArray[i]->Is("Item") && objectArray[j]->IsPlayer()) {
                        dynamic_cast<Item*>(objectArray[i])->Eval(dynamic_cast<Player*>(objectArray[j]));
                        Log::instance.info("Collision with player");                        
                    }
                        
                    else if (objectArray[j]->Is("Item") && objectArray[i]->IsPlayer()) {
                        Log::instance.info("Collision with player");
                        dynamic_cast<Item*>(objectArray[j])->Eval(dynamic_cast<Player*>(objectArray[i]));
                    } else {
                        Log::instance.info("collision between objects");
                        // It does nothing.
                    }
                }
            }
        }
    }
}


/*
 * Objective: Clean objects in room
 *
 * @param: none.
 * @return: none.
 */

void Room::ObjectCleanup() {
    Log::instance.info("Cleaning objects");
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
 * Objective: update states in room cleaning objects and colisions.
 *
 * @param: none.
 * @return: none.
 */

void Room::Update(float dt) {
    if (dt >= FLOAT_MIN_SIZE && dt <= FLOAT_MAX_SIZE) {
        ObjectUpdate(dt);
    } else {
        Log::instance.error("Tested value of dt is higher or lower than allowed!");
    }
    sceneObjects.Update();
    ObjectCollision();
    ObjectCleanup();
}

/*
 * Objective: render room screen position.
 *
 * @param: none.
 * @return: none.
 */

void Room::Render() {
    Log::instance.info("Render Room");
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
 * Objective: create items and objects in room.
 *
 * @param: none.
 * @return: none.
 */

void Room::CreateObjects() {
    Log::instance.info("Creating objects in room");
    for(unsigned int i = 0; i < objectData.size(); i++) {
        // Add items for Lancelot
        if (objectData.at(i).id == 0) {
            // Lancelot
            Log::instance.info("Creating objects in room for Lancelot");
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
            Log::instance.info("Creating objects in room for Gallahad");
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
            Log::instance.info("Creating objects in room for Arthur");
            AddObject(new Arthur(objectData.at(i).x +
                                 position.x * map->GetWidth() * map->GetTileWidth(),
                                 objectData.at(i).y +
                                 position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for TurretBoss
        else if (objectData.at(i).id == 3) {
            Log::instance.info("Creating objects in room for TurretBoss");
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
            Log::instance.info("Creating objects in room for Nofredo");
            AddObject(new Notfredo(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight(),
                      GROUND));
        }
        // Add items for CeilingEnemy
        else if (objectData.at(i).id == 14) {
            // CeilingEnemy
            Log::instance.info("Creating objects in room for CeilingEnemy");
            AddObject(new CeilingEnemy(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for Turret
        else if (objectData.at(i).id == 16) {
            // Turret
            Log::instance.info("Creating objects in room for Turret");
            AddObject(new Turret(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for Door
        else if (objectData.at(i).id == 21) {
            // Door
            Log::instance.info("Creating objects in room for Door");
            AddObject(new Door(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for PressurePlate
        else if (objectData.at(i).id == 22) {
            // PressurePlate
            Log::instance.info("Creating objects in room for PressurePlate");
            Interactive* in = (Interactive*) objectArray.at(objectArray.size()-1);
            AddObjectAsFirst(new PressurePlate(objectData.at(i).x +
                             position.x * map->GetWidth() * map->GetTileWidth(),
                             objectData.at(i).y +
                             position.y * map->GetHeight() * map->GetTileHeight(), in));
        }
        // Add items for HandScanner
        else if (objectData.at(i).id == 23) {
            // HandScanner
            Log::instance.info("Creating objects in room for HandScanner");
            Interactive* in = (Interactive*) objectArray.at(objectArray.size()-1);
            AddObjectAsFirst(new HandScanner(objectData.at(i).x +
                             position.x * map->GetWidth() * map->GetTileWidth(),
                             objectData.at(i).y +
                             position.y * map->GetHeight() * map->GetTileHeight(), in));
        }
        // Add items for Box
        else if (objectData.at(i).id == 24) {
            // Box
            Log::instance.info("Creating objects in room for Box");
            AddObject(new Box(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for BoxSpawner
        else if (objectData.at(i).id == 25) {
            // BoxSpawner
            Log::instance.info("Creating objects in room for BoxSpawner");
            AddObject(new BoxSpawner(objectData.at(i).x +
                      position.x * map->GetWidth() * map->GetTileWidth(),
                      objectData.at(i).y +
                      position.y * map->GetHeight() * map->GetTileHeight()));
        }
        // Add items for PreassurePlateOneTime
        else if (objectData.at(i).id == 26) {
            // PressurePlateOneTime
            Log::instance.info("Creating objects in room for PreassurePlateOneTime");
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
 * Objective: load objects from file in room
 *
 * @param: String file - this file lists the objects that will be inserted in this room.
 * @return: none.
*/

void Room::LoadObjects(std::string file) {
    std::ifstream f;
    Log::instance.info("Loading Objects");
    f.open(file.c_str(), std::ios::in);
    // Check if archive is open
    if (!f.is_open()) {
        Log::instance.error("f.open: unable to open file" + file);
    } else {
        Log::instance.info("Loading Objects successfully");
    }
    for(std::string line; std::getline(f, line);) {
        char delimiter;
        int id;
        ObjectData data;
        std::stringstream dataLine(line);
        dataLine >> data.id;
        dataLine >> delimiter;
        dataLine >> data.x;
        dataLine >> delimiter;
        dataLine >> data.y;
        dataLine >> delimiter;
        dataLine >> id;
        dataLine >> delimiter;
        if (id > 20) {
            ObjectData newData;
            newData.id = id;
            dataLine >> newData.x;
            dataLine >> delimiter;
            dataLine >> newData.y;
            dataLine >> delimiter;
            objectData.push_back(newData);
        } else {
            // It does nothing
        }
        objectData.push_back(data);        
    }
}

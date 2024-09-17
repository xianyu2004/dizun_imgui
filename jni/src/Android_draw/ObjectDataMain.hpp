#ifndef OBJECTDATAMAIN_HPP
#define OBJECTDATAMAIN_HPP

#include <iostream>
#include <vector>
#include <cstring>
#include "DataStruct.h"
#include "diRW/kernelRW.h"
#include "BoneGet.hpp"

using namespace std;

class OffsetData
{
public:
    int Health_offset = 0xDC0;
    int Component_offset = 0x1b0;
    int RelativeLocation_offest = 0x1c0;
    int Team_offset = 0x938;
    int State_offset = 0xf88;
    int Filter_offset = 0x2860;
    int Name_offset = 0x8f0;
    int Bot_offset = 0x9e9;
    int Mesh_offest = 0x498;
    int HuMan_offset = 0x1b0;
    int Bone_offest = 0x878;
};

class ObjectData
{
public:
    ObjectData(
        uintptr_t addr, Vector3D location, int health, int healthMax, int teamID, int state, const char *name);
    ObjectData(uintptr_t addr);
    ObjectData();

    // get
    uintptr_t getObjectAddr() const;
    Vector3D getRelativeLocation() const;
    int getHealth() const;
    int getHealthMax() const;
    int getTeamID() const;
    int getState() const;
    int getBot() const;
    string getPlayerName() const;
    Vector3D *getBoneRelativeLocation_p();

    // set
    void setObjectAddr(uintptr_t addr);
    void setRelativeLocation(Vector3D location);
    void setHealth(int health);
    void setHealthMax(int healthMax);
    void setTeamID(int teamID);
    void setState(int state);
    void setBot(int isbot);
    void setPlayerName(const char *name);
    void setBoneRelativeLocation(Vector3D boneRelativeLocation[17]);

    // data
    uintptr_t ObjectAddr;
    Vector3D RelativeLocation;
    int Health;
    int HealthMax;
    int TeamID;
    int State;
    int IsBot;
    char PlayerName[32];
    Vector3D BoneRelativeLocation[17];
};

class ObjectDataManager
{
public:
    // rw
    mainRW *rw;
    OffsetData offsetData;

    // init
    void InitObjectDataManager(int pid);
    bool IsInit();

    // set
    void addObjectData(uintptr_t addr);
    void removeObjectData(uintptr_t addr);
    void setSelfData(uintptr_t addr);
    void upDateObjectData();
    void upDateSelfData();
    void upDateImportantObjectData();
    void upDateUnmportantObjectData();
    void upDateBasicObjectData(ObjectData* object);

    // get
    ObjectData *getObjectData(int index);
    ObjectData *getObjectData(uintptr_t addr);
    ObjectData *getSelfData();
    std::vector<ObjectData> *getObjectData();

private:
    // data
    int pid;
    bool isInit = false;
    BoneGet boneGet;
    std::vector<ObjectData> ObjectDataList;
    ObjectData SelfData;

    // find
    std::vector<ObjectData>::iterator findObjectDataIterator(uintptr_t addr);
};

#endif
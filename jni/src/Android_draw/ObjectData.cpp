#include "ObjectDataMain.hpp"

// init
ObjectData::ObjectData(
	uintptr_t addr, Vector3D location, int health, int healthMax, int teamID, int state, const char *name)
{
	this->ObjectAddr = addr;
	this->RelativeLocation = location;
	this->Health = health;
	this->HealthMax = healthMax;
	this->TeamID = teamID;
	this->State = state;
	strcpy(this->PlayerName, name);
}

ObjectData::ObjectData(uintptr_t addr)
{
	this->ObjectAddr = addr;
}

ObjectData::ObjectData() {}

// get
uintptr_t ObjectData::getObjectAddr() const
{
	return this->ObjectAddr;
}

Vector3D ObjectData::getRelativeLocation() const
{
	return this->RelativeLocation;
}

int ObjectData::getHealth() const
{
	return this->Health;
}

int ObjectData::getHealthMax() const
{
	return this->HealthMax;
}

int ObjectData::getTeamID() const
{
	return this->TeamID;
}

int ObjectData::getState() const
{
	return this->State;
}

int ObjectData::getBot() const
{
	return this->IsBot;
}

string ObjectData::getPlayerName() const
{
	return this->PlayerName;
}

Vector3D *ObjectData::getBoneRelativeLocation_p()
{
	return this->BoneRelativeLocation;
}

// set
void ObjectData::setObjectAddr(uintptr_t addr)
{
	this->ObjectAddr = addr;
}

void ObjectData::setRelativeLocation(Vector3D location)
{
	this->RelativeLocation = location;
}

void ObjectData::setHealth(int health)
{
	this->Health = health;
}

void ObjectData::setHealthMax(int healthMax)
{
	this->HealthMax = healthMax;
}

void ObjectData::setTeamID(int teamID)
{
	this->TeamID = teamID;
}

void ObjectData::setState(int state)
{
	this->State = state;
}

void ObjectData::setBot(int isbot)
{
	this->IsBot = isbot;
}

void ObjectData::setPlayerName(const char *name)
{
	strcpy(this->PlayerName, name);
}

void ObjectData::setBoneRelativeLocation(Vector3D boneRelativeLocation[17])
{
	memcpy(this->BoneRelativeLocation, boneRelativeLocation, sizeof(Vector3D) * 17);
}

#include "ObjectDataMain.hpp"

// init
void ObjectDataManager::InitObjectDataManager(int Pid)
{
	this->pid = Pid;
	rw = new kernelRW(Pid); // 初始化读写
	boneGet.initRW(rw);
	this->isInit = true;
}

bool ObjectDataManager::IsInit()
{
	return this->isInit;
}

// set
void ObjectDataManager::addObjectData(uintptr_t addr)
{
	if (findObjectDataIterator(addr) != ObjectDataList.end())
		return; // 数据已存在
	ObjectData newData(addr);
	upDateBasicObjectData(&newData);
	ObjectDataList.push_back(newData);
}

void ObjectDataManager::removeObjectData(uintptr_t addr)
{
	auto vec = findObjectDataIterator(addr);
	if (vec != ObjectDataList.end())
	{
		ObjectDataList.erase(vec);
	}
}

void ObjectDataManager::setSelfData(uintptr_t addr)
{
	SelfData.setObjectAddr(addr);
}

// 完全更新数据，并且删除无用对象
void ObjectDataManager::upDateObjectData()
{
	// updata object
	for (int i = 0; i < ObjectDataList.size(); i++)
	{
		ObjectData *object = &ObjectDataList[i];
		uintptr_t ObjectAddr = object->getObjectAddr(); // 对象地址
		if (rw->getFloat(ObjectAddr + offsetData.Filter_offset) != 479.5 || object->getState() == 262144 || object->getState() == 262152)
		{
			removeObjectData(ObjectAddr); // 删除无用对象
			i--;
			continue;
		}
		else
		{
			// 更新数据
			static Vector3D RelativeLocation_temp;
			uintptr_t Locat_addr = rw->getPtr64(ObjectAddr + offsetData.Component_offset);
			rw->readv(Locat_addr + offsetData.RelativeLocation_offest, &RelativeLocation_temp, sizeof(RelativeLocation_temp)); // 坐标
			object->setRelativeLocation(RelativeLocation_temp);
			object->setHealth((int)rw->getFloat(ObjectAddr + offsetData.Health_offset));
			object->setHealthMax((int)rw->getFloat(ObjectAddr + offsetData.Health_offset + 0x4));
			object->setTeamID(rw->getDword(ObjectAddr + offsetData.Team_offset));
			object->setState(rw->getDword(ObjectAddr + offsetData.State_offset));
			object->setBot(rw->getBool(ObjectAddr + offsetData.Bot_offset));
			object->setPlayerName(rw->getUTF8(rw->getPtr64(ObjectAddr + offsetData.Name_offset)));
			uintptr_t MeshAddr = rw->getPtr64(ObjectAddr + offsetData.Mesh_offest);
			boneGet.更新骨骼数据(MeshAddr + offsetData.HuMan_offset, rw->getPtr64(MeshAddr + offsetData.Bone_offest) + 0x30, object->getBoneRelativeLocation_p());
		}
	}
}

void ObjectDataManager::upDateSelfData()
{
	uintptr_t ObjectAddr = SelfData.getObjectAddr();			   // 对象地址
	ObjectData *object = &SelfData; // 结构指针

	static Vector3D RelativeLocation_temp;
	uintptr_t Locat_addr = rw->getPtr64(ObjectAddr + offsetData.Component_offset);
	rw->readv(Locat_addr + offsetData.RelativeLocation_offest, &RelativeLocation_temp, sizeof(RelativeLocation_temp)); // 坐标
	object->setRelativeLocation(RelativeLocation_temp);
	object->setHealth((int)rw->getFloat(ObjectAddr + offsetData.Health_offset));
	object->setHealthMax((int)rw->getFloat(ObjectAddr + offsetData.Health_offset + 0x4));
	object->setTeamID(rw->getDword(ObjectAddr + offsetData.Team_offset));
	object->setState(rw->getDword(ObjectAddr + offsetData.State_offset));
}

void ObjectDataManager::upDateImportantObjectData()
{

	// updata object
	for (int i = 0; i < ObjectDataList.size(); i++)
	{
		ObjectData *object = &ObjectDataList[i];
		uintptr_t ObjectAddr = object->getObjectAddr(); // 对象地址

		// 更新数据
		static Vector3D RelativeLocation_temp;
		uintptr_t Locat_addr = rw->getPtr64(ObjectAddr + offsetData.Component_offset);
		rw->readv(Locat_addr + offsetData.RelativeLocation_offest, &RelativeLocation_temp, sizeof(RelativeLocation_temp)); // 坐标
		object->setRelativeLocation(RelativeLocation_temp);
		object->setHealth((int)rw->getFloat(ObjectAddr + offsetData.Health_offset));
		object->setState(rw->getDword(ObjectAddr + offsetData.State_offset));
		uintptr_t MeshAddr = rw->getPtr64(ObjectAddr + offsetData.Mesh_offest);
		boneGet.更新骨骼数据(MeshAddr + offsetData.HuMan_offset, rw->getPtr64(MeshAddr + offsetData.Bone_offest) + 0x30, object->getBoneRelativeLocation_p());
	}
}

void ObjectDataManager::upDateUnmportantObjectData()
{
	// 以后再说,好像没什么必要，想加自己加
}


void ObjectDataManager::upDateBasicObjectData(ObjectData* object)
{
	uintptr_t ObjectAddr = object->getObjectAddr(); // 对象地址

	static Vector3D RelativeLocation_temp;
			uintptr_t Locat_addr = rw->getPtr64(ObjectAddr + offsetData.Component_offset);
			rw->readv(Locat_addr + offsetData.RelativeLocation_offest, &RelativeLocation_temp, sizeof(RelativeLocation_temp)); // 坐标
			object->setRelativeLocation(RelativeLocation_temp);
			object->setHealth(rw->getDword(ObjectAddr + offsetData.Health_offset));
			object->setHealthMax(rw->getDword(ObjectAddr + offsetData.Health_offset + 0x4));
			object->setTeamID(rw->getDword(ObjectAddr + offsetData.Team_offset));
			object->setState(rw->getDword(ObjectAddr + offsetData.State_offset));
			object->setBot(rw->getDword(ObjectAddr + offsetData.Bot_offset));
			object->setPlayerName(rw->getUTF8(rw->getPtr64(ObjectAddr + offsetData.Name_offset)));
			uintptr_t MeshAddr = rw->getPtr64(ObjectAddr + offsetData.Mesh_offest);
			boneGet.更新骨骼数据(MeshAddr + offsetData.HuMan_offset, rw->getPtr64(MeshAddr + offsetData.Bone_offest) + 0x30, object->getBoneRelativeLocation_p());
}


// get
ObjectData *ObjectDataManager::getObjectData(int index)
{
	if (index >= 0 && index < ObjectDataList.size())
	{
		return &ObjectDataList[index];
	}
	return nullptr;
}

ObjectData *ObjectDataManager::getObjectData(uintptr_t addr)
{
	auto vec = findObjectDataIterator(addr);
	if (vec != ObjectDataList.end())
	{
		return &(*vec);
	}
	return nullptr;
}

ObjectData *ObjectDataManager::getSelfData()
{
	return &SelfData;
}

std::vector<ObjectData> *ObjectDataManager::getObjectData()
{
	return &ObjectDataList;
}

// find
std::vector<ObjectData>::iterator ObjectDataManager::findObjectDataIterator(uintptr_t addr)
{
	for (auto vec = ObjectDataList.begin(); vec != ObjectDataList.end(); vec++)
	{
		if (vec->getObjectAddr() == addr)
		{
			return vec;
		}
	}
	// not found,return ObjectDataList.end()
	return ObjectDataList.end();
}
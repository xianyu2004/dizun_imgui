#include "main_hack.hpp"
#include "ObjectDataMain.hpp"
#include "tool.h"
#include "DrawObject.hpp"



ObjectDataManager objectDataManager;
static mainRW *rw;
uintptr_t libue4;

// 矩阵
float maritx[16];

// 临时数据
int NowCount = 0;
int Count = 0;
uintptr_t Uworld_addr, Maritx_addr, Self_addr, Uleve_addr, Array_addr = 0;

void init_esp(float px, float py)
{
	initDraw(px, py);
	int pid = getPID("com.tencent.ig");
	objectDataManager.InitObjectDataManager(pid);
	rw = objectDataManager.rw;
	libue4 = get_module_base(pid, "libUE4.so");
	printf("pid: %d rw: %lx ue4:%lx \n", pid, rw, libue4);
}

void draw_esp()
{
	if (!objectDataManager.IsInit() || rw == nullptr)
		return;

	if (Count < 10 || Uleve_addr < 0xffff || Self_addr < 0xffff || Array_addr < 0xffff)
	{
		Uworld_addr = rw->getPtr64(rw->getPtr64(rw->getPtr64(libue4 + 0xCF14F60) + 0x20) + 0x20);
		Maritx_addr = rw->getPtr64(rw->getPtr64(libue4 + 0xCE8D4A0) + 0x20) + 0x270;
		Self_addr = rw->getPtr64(rw->getPtr64(rw->getPtr64(rw->getPtr64(libue4 + 0xCF14c98) + 0x8) + 0x48) + 0x20);
		Uleve_addr = rw->getPtr64(Uworld_addr + 0x30);
		objectDataManager.setSelfData(Self_addr);
	}

	Array_addr = rw->getPtr64(Uleve_addr + 0xA0);
	rw->readv(Maritx_addr, &maritx, sizeof(maritx));
	Count = rw->getDword(Uleve_addr + 0xA8);

	// 遍历添加人物
	for (int i = 0; i < MaxCount; i++)
	{
		if (NowCount > Count)
		{
			NowCount = 0;
			objectDataManager.upDateObjectData();
			break;
		}
		uintptr_t ObjectAddr = rw->getPtr64(Array_addr + 0x8 * NowCount);
		NowCount++;

		if (ObjectAddr < 0xFFFF)
			continue;

		int state = rw->getDword(ObjectAddr + objectDataManager.offsetData.State_offset);
		if (state == 262152 || state == 262144)
			continue;

		if (rw->getFloat(ObjectAddr + objectDataManager.offsetData.Filter_offset) == 479.5)
		{
			// 添加人物
			objectDataManager.addObjectData(ObjectAddr);
		}
	}

	objectDataManager.upDateImportantObjectData();
	objectDataManager.upDateSelfData();
	DrawObject(objectDataManager.getObjectData(), objectDataManager.getSelfData(), maritx);
}
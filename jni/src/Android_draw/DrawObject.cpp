#include "DrawObject.hpp"
#include "绘图.h"
#include "计算.h"

绘图 draw;

void initDraw(float Px, float Py)
{
	draw.初始化绘图(Px, Py);
}

void DrawObject(std::vector<ObjectData> *objectData, ObjectData *selfData, float matrix[16])
{
	if (objectData == nullptr)
		return;

	int sum = objectData->size();
	draw.绘制人数(sum);
	for (int i = 0; i < sum; i++)
	{
		ObjectData *Object = &((*objectData)[i]);
		
		if (Object->getTeamID() == selfData->getTeamID())
			continue;
		Vector4D 屏幕坐标 = 计算屏幕坐标(matrix, Object->getRelativeLocation(), draw.px, draw.py);
		if (屏幕坐标.W > 0)
		{
			draw.绘制方框(屏幕坐标, Object->getBot());
			draw.绘制血量(屏幕坐标, Object->getHealthMax(), Object->getHealth(), Object->getBot());
			draw.绘制射线(屏幕坐标, Object->getBot());
			draw.绘制距离(屏幕坐标, 计算距离(selfData->getRelativeLocation(), Object->getRelativeLocation()));
			draw.绘制名字(屏幕坐标, Object->getTeamID(), Object->getPlayerName(), Object->getBot());
			draw.绘制骨骼(计算骨骼(matrix, Object->getBoneRelativeLocation_p(), draw.px, draw.py), 屏幕坐标);
		}
	}
}
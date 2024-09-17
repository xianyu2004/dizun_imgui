#include <iostream>
#include <imgui.h>
#include <cstring>
#include "DataStruct.h"
#include "计算.h"
using namespace std;

class 绘图{
struct 颜色{
ImColor 红色 = ImColor(255,0,0,255);
ImColor 白色 = ImColor(255,255,255,255);
ImColor 蓝色 = ImColor(0,0,255,255);
ImColor 绿色 = ImColor(0,255,0,255);
ImColor 黄色 = ImColor(255,255,0,255);
};
float 骨骼粗细 = 0.4f;

public:
颜色 颜色;
float px,py;
void 初始化绘图(int x,int y);
void 绘制方框(Vector4D &屏幕坐标,bool isboot);
void 绘制人数(int &人数);
void 绘制距离(Vector4D &屏幕坐标,int 距离);
void 绘制射线(Vector4D &屏幕坐标,bool isboot);
void 绘制血量(Vector4D &屏幕坐标,float 最大血量,float 当前血量,bool isboot);
void 绘制名字(Vector4D &屏幕坐标,int 队伍,const string 名字,bool isboot);
void 绘制骨骼(BoneData 骨骼,Vector4D &屏幕坐标);
};

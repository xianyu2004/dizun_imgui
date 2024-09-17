#include <iostream>
#include <cmath>
#include "DataStruct.h"
using namespace std;

int 计算距离(Vector3D 自身坐标,Vector3D 对方坐标);
Vector4D 计算屏幕坐标(float 矩阵[16],Vector3D 人物坐标,float px,float py);
Vector2D 计算屏幕坐标2(float 矩阵[16],Vector3D 人物坐标,float px,float py);
float 计算屏幕距离(Vector2D &坐标,float px,float py);
BoneData 计算骨骼(const float 矩阵[16],const Vector3D 骨骼[17],float px,float py);

#include "计算.h"

int 计算距离(Vector3D 自身坐标,Vector3D 对方坐标){
	return (int)sqrt(pow(自身坐标.X-对方坐标.X,2)
		+pow(自身坐标.Y-对方坐标.Y,2)
		+pow(自身坐标.Z-对方坐标.Z,2))*0.01;
}


Vector4D 计算屏幕坐标(float 矩阵[16],Vector3D 人物坐标,float px,float py){
	Vector4D 屏幕坐标;
	float camear_r = 矩阵[3] * 人物坐标.X + 矩阵[7] * 人物坐标.Y + 矩阵[11] * 人物坐标.Z + 矩阵[15];
	float r_x = px + (矩阵[0] * 人物坐标.X + 矩阵[4] * 人物坐标.Y + 矩阵[8] * 人物坐标.Z +矩阵[12]) / camear_r * px;
	float r_y = py - (矩阵[1] * 人物坐标.X + 矩阵[5] * 人物坐标.Y + 矩阵[9] * (人物坐标.Z - 5) +矩阵[13]) / camear_r * py;
	float r_z = py - (矩阵[1] * 人物坐标.X + 矩阵[5] * 人物坐标.Y + 矩阵[9] * (人物坐标.Z + 205) +矩阵[13]) / camear_r * py;
	屏幕坐标.X = r_x-(r_y-r_z)/4;
	屏幕坐标.Y = r_y;
	屏幕坐标.Z = (r_y-r_z)/2;
	屏幕坐标.W = r_y-r_z;
	return 屏幕坐标;
}

Vector2D 计算屏幕坐标2(const float 矩阵[16],Vector3D 人物坐标,float px,float py){
	Vector2D 屏幕坐标;
	float camear_r = 矩阵[3] * 人物坐标.X + 矩阵[7] * 人物坐标.Y + 矩阵[11] * 人物坐标.Z + 矩阵[15];
	屏幕坐标.X = px + (矩阵[0] * 人物坐标.X + 矩阵[4] * 人物坐标.Y + 矩阵[8] * 人物坐标.Z + 矩阵[12]) / camear_r * px;
    屏幕坐标.Y = py - (矩阵[1] * 人物坐标.X + 矩阵[5] * 人物坐标.Y + 矩阵[9] * 人物坐标.Z + 矩阵[13]) / camear_r * py;
	return 屏幕坐标;
}


float 计算屏幕距离(Vector2D &坐标,float px,float py){
return sqrt(pow(px - 坐标.X, 2) + pow(py - 坐标.Y, 2));
}


BoneData 计算骨骼(const float 矩阵[16],const Vector3D 骨骼[17],float px,float py){
BoneData temp=
{计算屏幕坐标2(矩阵,骨骼[0],px,py)
,计算屏幕坐标2(矩阵,骨骼[1],px,py)
,计算屏幕坐标2(矩阵,骨骼[2],px,py)
,计算屏幕坐标2(矩阵,骨骼[3],px,py)
,计算屏幕坐标2(矩阵,骨骼[4],px,py)
,计算屏幕坐标2(矩阵,骨骼[5],px,py)
,计算屏幕坐标2(矩阵,骨骼[6],px,py)
,计算屏幕坐标2(矩阵,骨骼[7],px,py)
,计算屏幕坐标2(矩阵,骨骼[8],px,py)
,计算屏幕坐标2(矩阵,骨骼[9],px,py)
,计算屏幕坐标2(矩阵,骨骼[10],px,py)
,计算屏幕坐标2(矩阵,骨骼[11],px,py)
,计算屏幕坐标2(矩阵,骨骼[12],px,py)
,计算屏幕坐标2(矩阵,骨骼[13],px,py)
,计算屏幕坐标2(矩阵,骨骼[14],px,py)};
return temp;
}
